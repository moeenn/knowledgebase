
```js
/**
 * A helper function for making network requests nicer
 * @param {string | URL | Request} url
 * @param {RequestInit & { timeout: number }} options
 * @returns {Promise<Response>}
 */
async function safeFetch(url, options) {
  const abortController = new AbortController()
  const timeoutId = setTimeout(() => abortController.abort(), options.timeout)

  /** automatically add default headers, if required */
  const headers = new Headers(options.headers)
  if (!headers.has("Content-Type")) {
    headers.set("Content-Type", "application/json")
  }

  /** @type {Response} */
  let res
  try {
    res = await fetch(url, {
      ...options,
      headers,
      signal: abortController.signal,
    })

    /** handle >=400 status code related errors */
    if (!res.ok) {
      throw new Error(`${res.status} ${res.statusText}`)
    }
  } catch (err) {
    clearTimeout(timeoutId)
    throw err
  }

  /** prevent leaking memory */
  clearTimeout(timeoutId)
  return res
}
```