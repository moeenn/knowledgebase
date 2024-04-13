```js
/**
 * Throw failed assertions as errors
 * @param {boolean} assertion
 * @param {string} errorMessage
 * @returns {asserts assertion}
 */
function invariant(assertion, errorMessage) {
  if (!assertion) {
    throw new Error(errorMessage)
  }
}
```

```js
class Email {
  /** @type {string} */
  #input

  /**
   * @param {string} email
   * @throws {Error}
   */
  constructor(email) {
    invariant(email.includes("@"), "Invalid email address")
    this.#input = email
  }

  /** @returns {string} */
  asString() {
    return this.#input
  }
}

class Password {
  /** @type {string} */
  #input

  /**
   * @param {string} password
   * @throws {Error}
   */
  constructor(password) {
    invariant(password.length >= 8, "Stronger password required")
    this.#input = password
  }

  /** @returns {string} */
  asString() {
    return this.#input
  }
}

class LoginRequest {
  /** @type {Email} */
  #email

  /** @type {Password} */
  #password

  /**
   * @param {any} input
   * @throws {Error}
   */
  constructor(input) {
    invariant("email" in input, "Email field is required")
    invariant("password" in input, "Password field is required")

    /**
     * Note: destructuring is done here because typescript DOES NOT perform 
     * type-narrowing when doing it as follows
     * 
     * invariant(typeof input.email === "string", "Email must be a valid string")
     * <-- input.email is still 'any' at this point
    */
    const { email, password } = input
    invariant(typeof email === "string", "Email must be a valid string")
    invariant(typeof password === "string", "Password must be a valid string")

    this.#email = new Email(email)
    this.#password = new Password(password)
  }

  /**
   * @typedef LoginRequestObject
   * @property {string} email
   * @property {string} password
   *
   * @returns {LoginRequestObject}
   */
  asObject() {
    return {
      email: this.#email.asString(),
      password: this.#password.asString(),
    }
  }
}

/**
 * @throws {Error}
 * @returns {Promise<void>}
 */
async function main() {
  const raw = { email: "admin@site.com", password: "q1w2e3r4" }
  const form = new LoginRequest(raw)
  console.log(form.asObject())
}

main().catch(console.error)
```


###### Note
In the context of the server, this mechanism can work really well. However, it must **always** be combined with client-side input validations.

In normal scenario, the inputs will be validated in client-side and any errors will be displayed therein. When the request reaches the server, data is validated once again when the server constructs the related objects. The error messages are not going to be aggregated, but these can be displayed on the front-end as generic input errors (i.e. errors not associated with any specific input field).

In a scenario where is request is submitted to the server without performing client-side validations, all errors will be returned (one by one) as generic errors. This will force the client to actually implement proper user input validation.


---

#### Type-safe Objects using `zod`

```js
import { z } from "zod"

class Direction {
  #schema = z.enum(["Up", "Down", "Left", "Right"])

  /**
   *
   * @param {unknown} data
   */
  constructor(data) {
    const v = this.#schema.parse(data)
    this.value = v
  }
}

class Position {
  #schema = z.object({
    x: z.number(),
    y: z.number(),
  })

  /**
   *
   * @param {unknown} data
   */
  constructor(data) {
    const v = this.#schema.parse(data)
    this.x = v.x
    this.y = v.y
  }
}

class Entity {
  #step = 10

  #schema = z.object({
    name: z.string(),
    position: z.any(),
  })

  /**
   * @param {unknown} data
   */
  constructor(data) {
    const v = this.#schema.parse(data)
    this.name = v.name
    this.position = new Position(v.position)
  }

  /**
   *
   * @param {Direction} d
   */
  move(d) {
    switch (d.value) {
      case "Up":
        this.position.y += this.#step
        break

      case "Down":
        this.position.y -= this.#step
        break

      case "Left":
        this.position.x -= this.#step
        break

      case "Right":
        this.position.x += this.#step
        break
    }
  }
}

/** @returns {Promise<void>} */
async function main() {
  const e = new Entity({ name: "Entity one", position: { x: 0, y: 0 } })
  e.move(new Direction("Right"))
  e.move(new Direction("Right"))
  e.move(new Direction("Downs"))

  console.log(e)
}

main().catch(console.error)
```