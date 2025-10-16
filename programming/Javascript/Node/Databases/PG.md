```bash
$ npm i pg
$ npm i -D @types/pg node-pg-migrate dotenv
```

**Note**: `dotenv` is an indirect dependency of `node-pg-migrate`. It is required because we will be loading database URL from `.env` file

```.env
# dont change name; this is automatically picked up by node-pg-migrate
DATABASE_URL=postgres://devuser:devpass@localhost:5432/dev
```

```json
{
  "scripts": {
    "db:migrate": "node-pg-migrate --envPath=.env up",
    "db:migration": "node-pg-migrate create -j sql"
  }
}
```

**Note**: By default, all migrations will be placed inside `migrations` directory.

```bash
# create file for a new migration
npm run db:migration <migration_name>
```

```sql
-- Up Migration
create type user_role as enum('admin', 'user');

create table
  users (
    user_id uuid,
    email text unique not null,
    password text not null,
    role user_role not null default 'user',
    is_active boolean not null default true,
    created_at timestamp not null default now(),
    deleted_at timestamp null,
    primary key (user_id)
  )

-- Down Migration
drop table users;
drop type user_role;
```

```bash
# apply the migration
npm run db:migrate
```


---

#### Elaborate example

```ts
import { Pool, type PoolClient, DatabaseError } from "pg"
import pino from "pino"
import { z } from "zod"

const Logger = pino()

class DatabaseConfig {
    user = "devuser"
    host = "localhost"
    port = 5432
    password = "devpass"
    database = "dev"
}

class Database {
    #pool: Pool

    constructor(config: DatabaseConfig) {
        this.#pool = new Pool({
            user: config.user,
            host: config.host,
            port: config.port,
            password: config.password,
            database: config.database,
        })
    }

    async ping(): Promise<boolean> {
        const result = await this.#pool.query("select 1")
        return result.rowCount == 1
    }

    get conn() {
        return this.#pool
    }

    async tx(): Promise<Transaction> {
        return await Transaction.begin(this)
    }

    async [Symbol.asyncDispose]() {
        Logger.info("disconnecting db")
        await this.#pool.end()
    }
}

class Transaction {
    tx: PoolClient | null

    private constructor() {
        this.tx = null
    }

    static async begin(db: Database) {
        const newTx = new Transaction()
        newTx.tx = await db.conn.connect()
        await newTx.tx.query("begin")
        return newTx
    }

    async [Symbol.asyncDispose]() {
        if (!this.tx) return
        try {
            await this.tx.query("commit")
        } catch (err) {
            await this.tx.query("rollback")
            throw err
        } finally {
            this.tx.release()
        }
    }
}

class UserEntity {
    id: string
    email: string
    password: string
    role: "ADMIN" | "CLIENT"
    createdAt: Date
    deletedAt: Date | null | undefined

    #schema = z.object({
        id: z.uuid(),
        email: z.email(),
        password: z.string().min(8),
        role: z.enum(["ADMIN", "CLIENT"]),
        created_at: z.coerce.date(),
        deleted_at: z.coerce.date().nullable().optional(),
    })

    constructor(raw: unknown) {
        const v = this.#schema.parse(raw)
        this.id = v.id
        this.email = v.email
        this.password = v.password
        this.role = v.role
        this.createdAt = v.created_at
        this.deletedAt = v.deleted_at
    }

    static fromObject(v: Omit<UserEntity, "id" | "createdAt" | "deletedAt">) {
        return new UserEntity({
            id: crypto.randomUUID(),
            email: v.email,
            password: v.password,
            role: v.role,
            created_at: new Date(),
            deleted_at: undefined,
        })
    }
}

type ListUserArgs = {
    limit: number
    offset: number
}

type ListUsersQueryResult = UserEntity & {
    count: number
}

type ListUsersResult = {
    users: UserEntity[]
    totalCount: number
}

class UserRepo {
    db: Database

    constructor(db: Database) {
        this.db = db
    }

    static listUsersQuery = `
        select *, count(*) over() as count from "user"
        where deleted_at is null
        limit $1
        offset $2        
    `

    async listUsers(args: ListUserArgs): Promise<ListUsersResult> {
        const rows = await this.db.conn.query<ListUsersQueryResult>(
            UserRepo.listUsersQuery,
            [args.limit, args.offset],
        )

        const result: ListUsersResult = {
            users: [],
            totalCount: 0,
        }

        if (rows.rows.length == 0) {
            return result
        }

        result.totalCount = rows.rows[0].count
        result.users = rows.rows.map((row) => new UserEntity(row))
        return result
    }

    static createUserQuery = `
        insert into "user" (id, email, password, role, created_at)
        values ($1, $2, $3, $4, $5)
    `

    async crateUser(user: UserEntity): Promise<void> {
        try {
            await this.db.conn.query(UserRepo.createUserQuery, [
                user.id,
                user.email,
                user.password,
                user.role,
                user.createdAt.toUTCString(),
            ])
        } catch (err) {
            if (err instanceof DatabaseError) {
                switch (err.constraint) {
                    case "email_unique":
                        throw new Error("email address already in use")
                }
            }
            throw err
        }
    }
}

async function main() {
    const config = new DatabaseConfig()
    await using db = new Database(config)
    const isConnected = await db.ping()
    if (!isConnected) {
        throw new Error("failed to connect to db")
    }

    const repo = new UserRepo(db)
    const clientTwo = UserEntity.fromObject({
        email: "client-two@site.com",
        password: "another-password",
        role: "CLIENT",
    })
    await repo.crateUser(clientTwo)

    const users = await repo.listUsers({ limit: 10, offset: 0 })
    Logger.info({ count: users.totalCount }, "total users")
    for (const user of users.users) {
        console.log(user)
    }
}

main().catch(console.error)
```


---

#### Named Arguments

```ts
type NamedArgs = Record<string, Stringable | Date>
type NamedResult = [string, string[]]

interface Stringable {
    toString(): string
}

export function named(query: string, args: NamedArgs): NamedResult {
    const params = [...query.matchAll(/:([a-zA-Z_][a-zA-Z0-9_]*)/g)].map(
        (match) => match[0].slice(1),
    )

    const paramsSet = new Set(params)
    const paramArray: string[] = []
    let idx = 1

    for (const param of paramsSet) {
        const paramValue = args[param]
        if (!paramValue) {
            throw new MissingArgumentError(param)
        }

        query = query.replaceAll(":" + param, "$" + idx)
        if (paramValue instanceof Date) {
            paramArray.push(paramValue.toISOString())
        } else {
            paramArray.push(paramValue.toString())
        }

        idx++
    }

    return [query.trim(), paramArray]
}

export class MissingArgumentError extends Error {
    public readonly arg: string

    constructor(arg: string) {
        super("missing sql query argument: " + arg)
        this.arg = arg
    }
}
```

```ts
import test from "node:test"
import assert from "node:assert/strict"
import { MissingArgumentError, named } from "./named.js"

test("basic scenario", () => {
    const input = `
	    insert into "user" (id, email, password, role, created_at)
	    values (:id, :email, :password, :role, :created_at)
	`

    const expectedQuery = `
	    insert into "user" (id, email, password, role, created_at)
	    values ($1, $2, $3, $4, $5)
	`.trim()

    const inputParams = {
        id: crypto.randomUUID(),
        email: "admin@site.com",
        password: "1knclskcnlc",
        role: "ADMIN",
        created_at: new Date(),
    }

    const expectedParams = [
        inputParams.id,
        inputParams.email,
        inputParams.password,
        inputParams.role,
        inputParams.created_at.toISOString(),
    ]

    const got = named(input, inputParams)
    assert.deepEqual(got, [expectedQuery, expectedParams])
})

test("repeated params", () => {
    const input = `
        insert into record (id, name, created_at, updated_at)
        values (:id, :name, :created_at, :created_at)
    `

    const expectedQuery = `
        insert into record (id, name, created_at, updated_at)
        values ($1, $2, $3, $3)
    `.trim()

    const inputParams = {
        id: 300,
        name: "admin",
        created_at: new Date(),
    }

    const expectedParams = [
        inputParams.id.toString(),
        inputParams.name,
        inputParams.created_at.toISOString(),
    ]

    const got = named(input, inputParams)
    assert.deepEqual(got, [expectedQuery, expectedParams])
})

test("missing argument", () => {
    const input = `
        select * from entity
        limit :limit
        offset :offset
    `

    const inputParms = {
        limit: 20,
    }

    let missingErr: MissingArgumentError | null = null
    try {
        named(input, inputParms)
    } catch (err) {
        assert(err instanceof MissingArgumentError)
        missingErr = err
    }

    assert(missingErr != null)
    assert(missingErr.arg == "offset")
})

class Entity {
    constructor(
        public id: number,
        public fullName: string,
    ) {}
}

test("camelCase args", () => {
    const inputQuery = `
        insert into entity (id, full_name)
        values (:id, :fullName)
    `

    const expectedQuery = `
        insert into entity (id, full_name)
        values ($1, $2)
    `.trim()

    const inputEntity = new Entity(300, "Something Random")
    const expectedParams = [inputEntity.id.toString(), inputEntity.fullName]

    const got = named(inputQuery, { ...inputEntity })
    assert.deepEqual(got, [expectedQuery, expectedParams])
})
```

