
#### Migrations

```bash
npm i node-pg-migrate pg dotenv-cli
```

**Note**: Newer version of NodeJS support loading `.env` files without the `dotenv-cli` package. `package.json` scripts may be adjusted to remove the need for `dotenv-cli` which is an external package.

```.env
DATABASE_URL=postgres://devuser:devpass@localhost:5432/dev
```

```json
{
    "scripts": {
        "migrate:up": "dotenv -- node-pg-migrate up",
        "migrate:down": "dotenv -- node-pg-migrate down",
        "migrate:redo": "dotenv -- node-pg-migrate redo",
        "migrate:create": "node-pg-migrate create -j sql"
    }
}
```

**Note**: By default, all migrations will be placed inside `migrations` directory.

```bash
# create file for a new migration
npm run migrate:create <migration_name>
```

```sql
-- Up Migration
CREATE TYPE user_role AS ENUM ('ADMIN', 'CUSTOMER');

CREATE TABLE users (
  user_id SERIAL,
  email VARCHAR (255) UNIQUE NOT NULL,
  password VARCHAR (255),
  role user_role,
  PRIMARY KEY (user_id)
);

-- Down Migration
DROP TABLE users;

DROP TYPE user_role;
```

```sql
-- Up Migration
CREATE FUNCTION
  get_user_by_id (id INT) RETURNS users as $$
SELECT
  *
FROM
  users
WHERE
  user_id = id
LIMIT
  1 $$ LANGUAGE SQL;

-- Down Migration
DROP FUNCTION get_user_by_id (id INT);
```

```bash
# apply the migration
npm run migrate:up
```


---

#### Queries

```js
class User {
  /** @type {number} */
  id

  /** @type {string} */
  email

  /** @type {string} */
  password

  /** @type {"ADMIN" | "CUSTOMER"} */
  role

  /**
   *
   * @param {any} data
   */
  constructor(data) {
    // TODO: validate data and types
    this.id = data.id
    this.email = data.email
    this.password = data.password
    this.role = data.role
  }
}
```

```js
class UserRepo {
  /** @type {import("pg").Pool} */
  #db

  /**
   *
   * @param {import("pg").Pool} pool
   */
  constructor(pool) {
    this.#db = pool
  }

  /**
   * @param {number} userId
   * @returns {Promise<User | null>}
   */
  async getUserById(userId) {
    const result = await this.#db.query("SELECT * FROM get_user_by_id($1)", [
      userId,
    ])
    
    if (result.rowCount == 0) return null
    return new User(result.rows[0])
  }
}
```

```sql
import pg from "pg"

/** @returns {Promise<void>} */
async function main() {
  const db = new pg.Pool()
  const userRepo = new UserRepo(db)

  const user = await userRepo.getUserById(1)
  console.log(user)

  await db.end()
}

main().catch(console.error)
```