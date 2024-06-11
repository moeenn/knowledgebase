
```ts
import process from "node:process"

/** read env variables with optional fallback values */
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

  return value.trim()
}
```


#### Environment validation using `zod`

```ts
import { z } from "zod"
import process from "node:process"

/* define shape of the env variables here */
const envSchema = z.object({
  DATABASE_URI: z.string().url(),
  JWT_SECRET: z.string().min(32)
})

type Environment = z.infer<typeof envSchema>

class Env {
  static validateEnv() {
    try {
      envSchema.parse(process.env)
    } catch (err) {
      if (err instanceof z.ZodError) {
        const { fieldErrors } = err.flatten()
        const errorMessage = Object.entries(fieldErrors)
          .map(([field, errors]) =>
            errors ? `${field}: ${errors.join(", ")}` : field,
          )
          .join("\n  ")
        throw new Error(
          `Missing environment variables:\n  ${errorMessage}`,
        )
      }
      throw err
    }
  }

  static read(
    key: keyof Environment,
    fallback: string | undefined = undefined,
  ): string {
    const value = process.env[key]
    if (!value) {
      if (!fallback) {
        throw new Error(`value for environment variable '${key}' not found`)
      }
      return fallback
    }
  
    return value.trim()
  }
}
```

```ts
/** ensure environment is validated on application startup */
Env.validateEnv()

/** access variables safely with auto-complete on variable names */
const value = Env.read("DATABASE_URI")
console.log(`'${value}'`)
```