##### Configuration
File `package.json`

```json
{
  "name": "sandbox",
  "version": "1.0.0",
  "main": "src/index.mjs",
  "license": "MIT",
  "scripts": {
    "start": "node ./src/index.mjs",
    "check": "tsc --project jsconfig.json"
  },
  "imports": {
    "#src/*": "./src/*"
  },
  "devDependencies": {
    "@types/node": "^18.14.5",
    "typescript": "^4.9.5"
  }
}
```

File `jsconfig.json`

```json
{
  "compilerOptions": {
    "checkJs": true,
    "strict": true,
    "strictNullChecks": true,
    "strictFunctionTypes": true,
    "strictPropertyInitialization": true,
    "alwaysStrict": true,
    "target": "ES2015",
    "moduleResolution": "node",
    "noImplicitOverride": false,
    "paths": {
      "#src/*": [
        "./src/*"
      ]
    }
  },
  "include": [
    "src"
  ],
  "exclude": [
    "node_modules",
    "**/node_modules/*"
  ]
}
```


---

#### Usage
```javascript
/** @type {string} */
const str = "Lorem ipsum"

/** @type {number} */
const num = 300

/** @type {boolean} */
const isTrue = true

/** @type {number|string} */
const numOrStr = "union type"

/** @type {number[]} */
const numbers = [10, 20, 30]

/** @type {{name: string, email: string}} */
const params = {
  name: "sample",
  email: "sample@site.com",
}  

/** @type {Map<string, string>} */
const capitals = new Map([
  ["China", "Beijing"],
  ["England", "London"],
])

/** @type {function (string): void } */
const greeter = name => console.log("Hello, %s", name)
```


##### Classes
```javascript
class Point {
  /** @type {number} */
  x

  /** @type {number} */
  y

  /**
   * @param {number} x
   * @param {number} y
  */
   constructor(x, y) {
    this.x = x
    this.y = y
  }  
}

class Entity {
  /**
   * @readonly
   * @type {string}
  */
  name

  /** @type {Point} */
  position

  /** @type {number} */
  #area

  /**
   * @param {string} name
   * @param {number} x
   * @param {number} y
  */
  constructor(name, x, y) {
    this.name = name
    this.position = new Point(x, y)
    this.#area = x * y
  }

  /**
   * @public
   * @returns {number} 
  */
  get area() {
    return this.#area
  }
}
```

**Note**: Access modifiers i.e. `@public`,  `@private`,  `@protected` can be used with properties and methods. 


##### Extends and Implements
```js
/**
 * @template T
 * @extends {Set<T>}
 */
class SortableSet extends Set {
  // ...
}
```

```js
/** @implements {Print} */
class TextBook {
  print() {
    // TODO
  }
}
```


---

#### Example
```javascript
/* file: index.d.mjs */
/**
 * @typedef User
 * @property {number} id
 * @property {string} name
 * @property {string} email
 * @property {string} password
*/

export {}
```

```javascript
/* file: index.mjs */

/* eslint-ignore-next-line no-unused-vars */
import * as t from "index.d.mjs"

/** @type {function (t.User): void}*/
function greetUser(user) {
  console.log("Hello, %s", user.name)
}

/** @type {function(): Promise<void>} */
async function main() {
  /** @type {t.User} */
  const user = {
    id: 1,
    name: "Sample",
    email: "sample@site.com",
    password: "123123123",
  }

  greetUser(user)
}

main().catch(console.error)
```


---

#### Generics
```js
/**
 * @template T
 * @param {T} x - A generic parameter that flows through to the return type
 * @returns {T}
 */
function id(x) {
  return x
}
 
const a = id("string")
const b = id(123)
const c = id({})
```

**Note**: Generic classes can also be defined this way.

---

#### Cast to specific Data type
```javascript
/** @type {unknown} */
const rawData = {
  id: 1,
  name: "user",
  email: "user@site.com"
}

const data = /** @type {{ id: number, name: string, email: string}} */ (rawData)
```

**Note**: The comment style and the placement of the parentheses during casting is important.


---

#### Cast as const

```javascript
const schema = /** @type {const} */ (anotherVariable)
```

**Note**: The parenthesis around the value are required for this to work.


---

#### Usage with `Ajv`

```javascript
import Ajv from "ajv"

const schema = /** @type {const} */ ({
  type: "object",
  properties: {
    id: { type: "number" },
    name: { type: "string" },
    email: { type: "string" },
  },
  required: ["id", "name", "email"],
  additionalProperties: false,
})

/** @typedef {import(""json-schema-to-ts"").FromSchema<typeof schema>} Schema */

/** @returns {Promise<void>} */
export async function main() {

  const validator = new Ajv()

  /** @type {unknown} */
  const rawData = {
    id: 1,
    name: "sample",
    email: "sample@site.com",
  }

  const isValid = validator.validate(schema, rawData)
  if (!isValid) {
    return console.log({ isValid })
  }

  const body = /** @type {Schema} */ (rawData)
  console.log(body)
}

main().catch(console.error)
```

