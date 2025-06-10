```bash
$ npm i pm2
```


---

#### Basic Express application
```js
/** file: src/index.mjs */
import express from "express"
import process from "node:process"

const PORT = 5000
const app = express()

app.get("/task", (req, res) => {
  let total = 0
  for (let i = 0; i < 5_000_000; i++) {
    total += i
  }

  res.json({ total })
})

app.listen(PORT, () => {
  console.log(`Starting app: PID ${process.pid}`)
}) 
```


---

#### Basic `pm2` Commands

```bash
# list all running processes
$ npx pm2 ls

# start a new cluster, -i 0 means create according to num cpus
$ npx pm2 start ./src/index.mjs -i 0

# stop a running cluster
$ npx pm2 delete ./src/index.mjs

# see logs of running clusters
$ npx pm2 logs
```


---

#### Usage with config file
The cluster configuration for `pm2` is named `ecosystem.config.js`. 

```js
/** file: ecosystem.config.js */
module.exports = {
  apps: [
    {
      name: "sample-express",
      instances: 0,
      exec_mode: "cluster",
      script: "./src/index.mjs"
    }
  ]
}
```

```bash
# starting the cluster
$ npx pm2 start --no-daemon

# starting the cluster explicitly providing the config file
$ npx pm2 start ecosystem.config.cjs

# stop the cluster using name defined in the config
$ npx pm2 delete <cluster_name>
```


---

#### Schedule periodic jobs

```js
/* file: ecosystem.config.js */
module.exports = {
  apps: [
    {
      name: "project-name",
      instances: 0,
      exec_mode: "cluster",
      script: "./build/index.js"
    },
    {
      name: "cron",
      script: "./build/app/jobs/backgroundTask.js",
      instances: 1,
      exec_mode: "fork",
      cron_restart: "0 * * * *", // "0 */3 * * *" mean every three hours    
      watch: false,
      autorestart: false
    }
  ]
}
```

