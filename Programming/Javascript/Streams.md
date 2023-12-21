#### Readable Streams

```ts
import process from "node:process"
import path from "node:path"
import fs, {ReadStream} from "node:fs"

export async function main(): Promise<void> {
  const filepath = path.join(process.cwd(), "sample.txt")
  const rs: ReadStream = fs.createReadStream(filepath, { 
	encoding: "utf-8", highWaterMark: 10 
  })

  rs.on("error", () => console.log("Failed to open file"))

  /** option 1: read using callback */
  rs.on("data", (chunk) => console.log(chunk, "\n\n"))

  /** option 2: read using async iterables */
  for await (const chunk of rs) {
    console.log(chunk)
  }
}
```