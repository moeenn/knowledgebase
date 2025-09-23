```bash
$ npm i pg
$ npm i -D @types/pg
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

#### Migrations

```ts
interface Migration {
    up(): string
    down(): string
}

class UserMigration implements Migration {
    up(): string {
        return `
            create type user_role as enum('ADMIN', 'CLIENT');
        
            create table "user" (
                id uuid not null
                , email text not null
                , password text not null
                , role user_role default 'CLIENT'::user_role
                , created_at timestamp default now()
                , deleted_at timestamp null
                , primary key (id)
                , constraint email_unique unique(email)
            );             
        `
    }

    down(): string {
        return `
            drop table "user";
            drop type user_role;                
            `
    }
}

class MigrationManager {
    db: Database
    migrations: Migration[]

    constructor(db: Database, migrations: Migration[]) {
        this.db = db
        this.migrations = migrations
    }

    async migrate() {
        Logger.info("starting migrations")
        await using tx = await this.db.tx()
        for (const migration of this.migrations) {
            Logger.info("running migration: " + migration.constructor.name)
            await tx.tx!.query(migration.up())
        }
        Logger.info("migrations successful")
    }

    async rollback() {
        Logger.info("starting rollback")
        await using tx = await Transaction.begin(this.db)
        for (let i = this.migrations.length - 1; i >= 0; i--) {
            Logger.info(
                "running migration: " + this.migrations[i].constructor.name,
            )
            await tx.tx!.query(this.migrations[i].down())
        }
        Logger.info("rollback successful")
    }
}
```

```ts
const migrationManager = new MigrationManager(db, [new UserMigration()])
await migrationManager.migrate()
```