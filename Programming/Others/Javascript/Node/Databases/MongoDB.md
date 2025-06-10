
#### Todo
- [ ] Mongo-sh
- [ ] CRUD
- [ ] Indexes
- [ ] `$lookup`
- [ ] Aggregate
- [ ] Embedded documents


---

#### Run using Docker

```yml
version: '3.8'
services:
  mongodb:
    image: mongo:7.0-jammy
    ports:
      - '27017:27017'
    environment:
      - MONGO_INITDB_ROOT_USERNAME=devuser
      - MONGO_INITDB_ROOT_PASSWORD=devpass
      - MONGO_INITDB_DATABASE=dev
    volumes:
      - ./docker-volume:/data/db
```

**Note**: Currently there is no `alpine` variant of the MongoDB docker image.


---

#### Basic Usage

```bash
$ npm i mongodb
```

```js
import { MongoClient } from "mongodb"

const config = {
  uri: "mongodb://devuser:devpass@localhost:27017",
  dbName: "dev",
}

/** 
 * @typedef User
 * @property {string} email
 * @property {string} password
 */
class UserCollection {
  #name = "user"

  /** @type {import("mongodb").Collection<User>} */
  documents

  /** 
   * @param {import("mongodb").Db} db
   */
  constructor(db) {
    this.documents = db.collection(this.#name)
  }
}

/** @returns {Promise<void>} */
async function main() {
  const client = new MongoClient(config.uri)
  await client.connect()
  console.log("connection established")

  /** @type {import("mongodb").Db} */
  const db = client.db(config.dbName)

  const users = new UserCollection(db)

  const result = await users.documents.insertOne({
    email: "admin@site.com",
    password: "password",
  })

  if (!result.acknowledged) {
    throw new Error("failed to insert user")
  }

  const allUsers = await users.documents.find({}).toArray()
  console.log(allUsers)

  await client.close()
}

main().catch(console.error)
```


---

#### Implementing models with schema

```js
/**
 * @typedef User
 * @property {string} email
 * @property {string} password
 */
class UserCollection {
  static collectionName = "users"

  /** @type {import("mongodb").Collection<User>} */
  documents

  /** 
   * @param {import("mongodb").Db} db
   */
  constructor(db) {
    this.documents = db.collection(UserCollection.collectionName)
  }

  /** 
   * create the collection in mongodb. This function can be executed safely even
   * if the collection already exists. However, if we update the schema, this 
   * function will throw an error regarding schema mis-match.
   * 
   * @param {import("mongodb").Db} db
   */
  static async migrate(db) {
    await db.createCollection(UserCollection.collectionName, {
      validator: {
        $jsonSchema: {
          type: "object",
          properties: {
            email: { type: "string" },
            password: { type: "string" },
          },
          required: ["email", "password"],
        },
      }
    })
  }
}
```

**Note**: This schema as a slightly different syntax than standard JSON schema. We cannot use `json-schema-to-ts` to infer the type from this schema.


---

#### Running migrations

##### Create all required collections

```js
/**
 * @typedef {import("mongodb").Db} Db
 * @param {Db} db 
 */
async function migrateAllCollections(db) {
  /** @type {{ migrate: (db: Db) => Promise<void>}[]} */
  const collections = [
    UserCollection,
  ]

  for (const collection of collections) {
    await collection.migrate(db)
  }
}
```

