
```ts
import process from "node:process"

export function env(
  key: string,
  fallback: string | undefined = undefined,
): string {
  const value = process.env[key]
  if (!value) {
    if (!fallback) {
      throw new Error(`value for environment variable '${key}' not found`)
    }
    return fallback
  }

  return value
}
```

