
```ts
import { DatabaseSync } from "node:sqlite"
import { z } from "zod"

class DatabaseConfig {
    constructor(public readonly path: string = "site.db") {}
}

class Database {
    conn: DatabaseSync

    constructor(config: DatabaseConfig) {
        this.conn = new DatabaseSync(config.path)
    }
}

type Entity = {
    schema(): string
}

type UserRole = "ADMIN" | "CUSTOMER"

class User {
    id: string
    email: string
    password: string
    role: UserRole
    createdAt: Date
    deletedAt: Date | undefined

    #schema = z.object({
        id: z.uuid(),
        email: z.email(),
        password: z.string(),
        role: z.enum(["ADMIN", "CUSTOMER"]),
        createdAt: z.coerce.date(),
        deletedAt: z.coerce.date().optional(),
    })

    constructor(raw: unknown) {
        const v = this.#schema.parse(raw)
        this.id = v.id
        this.email = v.email
        this.password = v.password
        this.role = v.role
        this.createdAt = v.createdAt
        this.deletedAt = v.deletedAt
    }

    static make(email: string, password: string, role: UserRole): User {
        const id = crypto.randomUUID().toString()
        const now = new Date()
        return new User({ id, email, password, role, createdAt: now })
    }

    static schema(): string {
        return `
            create table if not exists users (
                id varchar(40)
                , email varchar(100) not null
                , password varchar(255) not null
                , role varchar(20) not null
                , createdAt timestamp not null default current_timestamp
                , deletedAt timestamp
                , primary key (id)
                , constraint email_unique unique (email)               
            );
        `
    }
}

class MigrationManager {
    db: Database
    entities: Entity[]

    constructor(db: Database, entities: Entity[]) {
        this.db = db
        this.entities = entities
    }

    async migrate() {
        for (const entity of this.entities) {
            const ddl = entity.schema()
            this.db.conn.exec(ddl)
        }
    }
}

class UserRepo {
    db: Database

    constructor(db: Database) {
        this.db = db
    }

    list(limit: number = 10, offset: number = 0): User[] {
        const statement = this.db.conn.prepare(`
            select * from users
            where deletedAt is null
            limit ?
            offset ?
        `)

        const result = statement.all(limit, offset)
        return result.map((u) => new User(u))
    }

    insert(user: User) {
        const statement = this.db.conn.prepare(`
            insert into users (id, email, password, role, createdAt)
            values (?, ?, ?, ?, ?)
        `)

        statement.run(
            user.id,
            user.email,
            user.password,
            user.role,
            user.createdAt.toUTCString(),
        )
    }

    findById(id: string): User | null {
        const statement = this.db.conn.prepare(`
            select * from users
            where id = ?
            and deletedAt is null
            limit 1;
        `)

        const result = statement.all(id)
        if (!result.length) {
            return null
        }

        return new User(result[0])
    }
}

function main(): void {
    const config = new DatabaseConfig()
    const db = new Database(config)
    const migrations = new MigrationManager(db, [User])

    console.log("running migrations...")
    migrations.migrate()

    const userRepo = new UserRepo(db)
    const dummyUsers = [
        User.make("admin@site.com", "akscnalskcna", "ADMIN"),
        User.make("customer@site.com", "kasnclaksncla", "CUSTOMER"),
    ]
    dummyUsers.forEach((user) => userRepo.insert(user))

    const users = userRepo.list()
    console.log(users)
}

main()
```