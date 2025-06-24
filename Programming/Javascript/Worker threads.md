
```js
// file: src/index.mjs
import os from "node:os"
import { Worker } from "node:worker_threads"

/**
 * @param {number} nCPUs
 * @returns {number[][]}
 */
function createJobChunks(nCPUs) {
  /** @type {number[][]} */
  const jobs = []

  for (let i = 0; i < nCPUs; i++) {
    jobs.push(Array.from({ length: 100 / nCPUs }, () => 1e8))
  }

  return jobs
}

/**
 * @param {number} nCPUs
 * @param {number[][]} jobs
 * @returns {Promise<void>}
 */
function spawnWorkers(nCPUs, jobs) {
  return new Promise((resolve) => {
    let completeCount = 0

    for (const chunk of jobs) {
      const worker = new Worker("./src/worker.mjs")
      worker.on("message", (status) => {
        console.log(status)
        completeCount++

        if (completeCount === nCPUs) {
          resolve()
        }
      })

      // start the worker thread
      worker.postMessage(chunk)
    }
  })
}

/** @returns {Promise<void>} */
export async function main() {
  const numCPUs = os.cpus()
  const jobs = createJobChunks(numCPUs.length)

  const start = performance.now()
  await spawnWorkers(numCPUs.length, jobs)

  const end = performance.now()
  console.log(`Elapsed: ${end - start} ms`)
}

main().catch(console.error)
```

```js
// file: src/worker.mjs
import { parentPort } from "node:worker_threads"

/**
 * @param {number[]} jobs
 * @returns {void}
 */
function cpuIntensiveTask(jobs) {
  for (const job of jobs) {
    let count = 0
    for (let i = 0; i < job; i++) {
      count++
    }
  }
}

/**
 * @returns {void}
 */
function main() {
  if (!parentPort) return

  parentPort.on("message", (jobs) => {
    cpuIntensiveTask(jobs)

    // report back to parent thread
    if (parentPort) {
      parentPort.postMessage("done")
      parentPort.close()
    }
  })
}

main()
```