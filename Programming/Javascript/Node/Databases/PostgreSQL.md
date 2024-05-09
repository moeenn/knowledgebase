
#### Migrations

```bash
npm i node-pg-migrate postgres dotenv-cli
```

**Note**: Newer version of NodeJS support loading `.env` files without the `dotenv-cli` package. `package.json` scripts may be adjusted to remove the need for `dotenv-cli` which is an external package.

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

#### CRUD

```ts
export type UserRole = "admin" | "user"

export type User = {
  user_id: string
  email: string
  password: string
  role: UserRole
  is_active: boolean
  created_at: Date
  deleted_at: Date | null
}

export type UserInsert = Omit<User, "created_at" | "deleted_at">
```

```js
import postgres from "postgres"
import { env } from "./env.mjs"

const connectionString = env("DATABASE_URL")
const sql = postgres(connectionString)

/**
 * @typedef {import("./schemas/schema").User} User
 * @typedef {import("./schemas/schema").UserInsert} UserInsert
 */

const UserRepo = {
  /**
   * @returns {Promise<User[]>}
   */
  async all() {
    /** @type {User[]} */
    const result = await sql`
    select * from users
    where deleted_at is null;
    `

    return result
  },

  /**
   * 
   * @param {string} id 
   * @returns {Promise<User | undefined>}
   */
  async findById(id) {
    /** @type {User[]} */
    const result = await sql`
    select * from users
    where deleted_at is null
    and user_id = ${id}
    limit 1
    `

    if (!result.length) return undefined
    return result[0]
  },

  /**
   * 
   * @param {UserInsert} user 
   * @returns {Promise<User>}
   */
  async create(user) {
    /** @type {User[]} */
    const result = await sql`
    insert into users (user_id, email, password, role, is_active)
    values (${user.user_id}, ${user.email}, ${user.password}, ${user.role}::user_role, ${user.is_active})
    returning *
    `  

    return result[0]
  },

  /**
   * 
   * @param {User} user 
   * @returns {Promise<User>}
   */
  async update(user) {
    /** @type {User[]} */
    const result = await sql`
    update users
    set 
      email = ${user.email},
      password = ${user.password},
      role = ${user.role},
      is_active = ${user.is_active}
    where user_id = ${user.user_id}
    and deleted_at is null
    returning *
    `

    return result[0]
  },

  /**
   * 
   * @param {User} user 
   */
  async remove(user) {
    await sql`
    update users
    set deleted_at = now()
    where user_id = ${user.user_id}
    and deleted_at is null
    `
  },
}

/** 
 * 
 * @returns {Promise<void>} 
 */
async function main() {
  /** @type {UserInsert} */
  const data = {
    user_id: crypto.randomUUID(),
    email: "admin@site.com",
    password: "123_Password",
    role: "admin",
    is_active: true,
  }

  const foundUser = await UserRepo.findById("...")
  if (!foundUser) {
    console.log("user not found")
    return
  }

  foundUser.email = "user@site.com"
  foundUser.is_active = false

  const user = await UserRepo.update(foundUser)
  console.log(user)
}

main()
  .then(async () => await sql.end())
  .catch(console.error)
```

