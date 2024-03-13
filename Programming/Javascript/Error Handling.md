
```js
/**
 * @template T
 * @typedef {{ result: T, error: null }} ok
 */

/** @typedef {{ result: null, error: Error }} error */

/**
 * @template T
 * @param {T} result
 * @returns {ok<T>}
 */
const ok = (result) => ({ result, error: null })

/**
 * @param {Error} error
 * @returns {error}
 */
const error = (error) => ({ result: null, error })

/**
 * @template T
 * @param {() => T} cb
 * @returns {ok<T> | error}
 */
export function recover(cb) {
  /** @var {T} */
  let result

  try {
    result = cb()
  } catch (err) {
    if (err instanceof Error) {
      return error(err)
    }
    return error(new Error("Unknown error occured"))
  }

  return ok(result)
}

/**
 * @template T
 * @param {() => Promise<T>} cb
 * @returns {Promise<ok<T> | error>}
 */
export async function recoverAsync(cb) {
  /** @var {T} */
  let result

  try {
    result = await cb()
  } catch (err) {
    if (err instanceof Error) {
      return error(err)
    }
    return error(new Error("Unknown error occured"))
  }

  return ok(result)
}
```

```js
import test from "node:test"
import assert from "node:assert/strict"
import { recover, recoverAsync } from "./recover.mjs"

/**
 * @param {number} arg
 * @returns {number}
 */
function syncAction(arg) {
  if (arg == -1) {
    throw new Error("Cannot process negative number")
  }

  return arg * 100
}

test("recover sync function: no error", () => {
  const result = recover(() => syncAction(30))
  assert.strictEqual(result.error, null)
  assert.equal(result.result, 3000)
})

test("recover sync function: error returned", () => {
  const result = recover(() => syncAction(-1))
  assert.strictEqual(result.result, null)
  assert.equal(result.error.message, "Cannot process negative number")
})

/**
 * @param {number} arg
 * @returns {Promise<number>}
 */
async function asyncAction(arg) {
  return new Promise((resolve, reject) => {
    if (arg == -1) {
      reject(new Error("Cannot process negative number"))
      return
    }

    resolve(arg * 100)
  })
}

test("recover async function: not error", async () => {
  const result = await recoverAsync(() => asyncAction(10))
  assert.strictEqual(result.error, null)
  assert.equal(result.result, 1000)
})

test("recover async function: error returned", async () => {
  const result = await recoverAsync(() => asyncAction(-1))
  assert.strictEqual(result.result, null)
  assert.equal(true, result.error instanceof Error)
})
```