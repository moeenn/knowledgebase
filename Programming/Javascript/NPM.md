
#### Set global install location

```bash
$ npm config set prefix ~/.npm
```


---

#### Login

```bash
$ npm login
```

**Note**: The above command will open the web browser and allow you to login. Note that login tokens will be saved to the file `~/.npmrc`, so ensure that file is not in version control.


#### Publishing NPM packages

**Step one**: Setup a new JavaScript project. Typescript is recommended for this. One simple way is the following.

```bash
$ npx moeenn-tsinit
```

The above command will ask for the project name. A directory of the provided name will be created in the current directory (i.e. `pwd`).

**Step two**: Install and configure `tsup`

```bash
$ npm i -D tsup

# create the config file
$ touch tsup.config.ts
```

```ts
import { defineConfig } from "tsup"

export default defineConfig({
  entry: ["src/index.ts"],
  format: ["cjs", "esm"],
  dts: true,
  splitting: false,
  sourcemap: true,
  clean: true,
})
```

We can add the following scripts to the `package.json` file.

```json
{
  "scripts": {
    "build-package": "tsup",
	"pub": "npm publish --access=public"
  }
}
```

Aside from the above scripts, ensure that the following keys are set in the `package.json` file.

- `name`
- `version`
- `author`
- `license`. Use the value `ISC`
- `description`
- `keywords`. This is an array of strings
- `main`. Path to `CJS` build
- `module`. Path to `ESM` build
- `types`. Path to the build `d.ts` file.
- `files`. Directory containing the `tsup` output.

```json
{
  "name": "@moeenn/recover",
  "version": "2.0.0",
  "author": "moeenn",
  "license": "ISC",
  "description": "Easy type-safe error handling without try-catch",
  "keywords": [
    "error",
    "handling",
    "error-handling",
    "try-catch",
    "typescript"
  ],
  "main": "./dist/index.js",
  "module": "./dist/index.mjs",
  "types": "./dist/index.d.ts",
  "files": [
    "dist"
  ]
}
```


---

