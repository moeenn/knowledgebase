```js
/* file: validator.mjs */
import Ajv from "ajv"

export const Validator = {
  /** @typedef {import('ajv').ValidateFunction} ValidateFunction */
  /** @typedef {import('ajv').ErrorObject} ErrorObject */

  /** @type {Ajv} */
  V: new Ajv({ allErrors: true }),

  /** @type {function (Record<string, unknown>): ValidateFunction } */
  createValidator(definition) {
    return this.V.compile(definition)
  },

  /** @type {function (ValidateFunction, Record<string, unknown>): Promise<ErrorObject[]>} */
  async validate(validator, data) {
    const result = await validator(data)
    if (!result) {
      return validator.errors
    }
    return []
  },
}
```

```js
/* file: validator.test.mjs */
import { test, expect } from "vitest"
import { Validator } from "./validator.mjs"

test("valid schema basic", async () => {
  const schema = Validator.createValidator({
    type: "object",
    required: ["id", "name", "email"],
    properties: {
      id: {
        type: "number",
      },
      name: {
        type: "string",
      },
      email: {
        type: "string",
      },
    },
  })

  const data = {
    id: 10,
    name: "sample",
    email: "sample@site.com",
  }

  const result = await Validator.validate(schema, data)
  expect(result).toStrictEqual([])
})

test("schema optional field", async () => {
  const schema = Validator.createValidator({
    type: "object",
    required: ["id", "email"],
    properties: {
      id: {
        type: "number",
      },
      name: {
        type: "string",
      },
      email: {
        type: "string",
      },
    },
  })

  const data = {
    id: 10,
    email: "sample@site.com",
  }

  const result = await Validator.validate(schema, data)
  expect(result).toStrictEqual([])
})

test("array of objects", async () => {
  const schema = Validator.createValidator({
    type: "object",
    required: ["users"],
    properties: {
      users: {
        type: "array",
        items: {
          type: "object",
          required: ["id", "email"],
          properties: {
            id: {
              type: "number",
            },
            email: {
              type: "string",
            },
          },
        },
      },
    },
  })

  const data = {
    users: [
      { id: 10, email: "sample@site.com" },
      { id: 20, email: "example@site.com" },
    ],
  }

  const result = await Validator.validate(schema, data)
  expect(result).toStrictEqual([])
})

test("invalid field type", async () => {
  const schema = Validator.createValidator({
    type: "object",
    required: ["id"],
    properties: {
      id: {
        type: "number",
      },
    },
  })

  const data = {
    id: "abc123",
  }

  const result = await Validator.validate(schema, data)
  expect(result[0].keyword).toBe("type")
})

test("missing field", async () => {
  const schema = Validator.createValidator({
    type: "object",
    required: ["id", "email"],
    properties: {
      id: {
        type: "number",
      },
      email: {
        type: "string",
      },
    },
  })

  const data = {
    id: 10,
  }

  const result = await Validator.validate(schema, data)
  expect(result[0].keyword).toBe("required")
})

test("multiple errors", async () => {
  const schema = Validator.createValidator({
    type: "object",
    required: ["id", "name", "email"],
    properties: {
      id: {
        type: "number",
      },
      name: {
        type: "string",
      },
      email: {
        type: "string",
      },
    },
  })

  const data = {
    id: "abc123",
    email: "sample@site.com",
  }

  const result = await Validator.validate(schema, data)
  expect(result.length).toBe(2)
})
```