`workspaces` is a features provided by `npm` to create `monorepos` and share code between different projects.


##### Creating workspaces

```bash
# create root package.json
$ npm init -y

# create a workspace named "common"
$ npm init -y -w common

# create a workspace named "module-one"
$ npm init -y -w module-one
```

The above commands will result in the following project structure.

```
monorepo/
    common/
        package.json
    module-one/
        package.json
```

Ideally, we should have `src` directories inside all our workspaces.

```bash
$ mkdir ./common/src ./module-one/src
```

We will likely be building our projects using `typescript` and `swc`. We can add their configuration globally.

```json
{
  "compilerOptions": {
    "target": "es2020",
    "module": "es2020",
    "allowJs": true,
    "removeComments": true,
    "resolveJsonModule": true,
    "typeRoots": ["./node_modules/@types"],
    "sourceMap": true,
    "outDir": "dist",
    "strict": true,
    "lib": ["es2020"],
    "forceConsistentCasingInFileNames": true,
    "esModuleInterop": true,
    "experimentalDecorators": true,
    "emitDecoratorMetadata": true,
    "moduleResolution": "Node",
    "skipLibCheck": true,
    "baseUrl": ".",
    "paths": {
      "@common/*": ["./common/src/*"],
      "@module-one/*": ["./module-one/src/*"],
    }
  },
  "include": ["*/src/**/*"],
  "exclude": ["node_modules", "**/node_modules/**"]
}
```

```json
{
  "jsc": {
    "parser": {
      "syntax": "typescript",
      "tsx": false,
      "decorators": false,
      "dynamicImport": true
    },
    "target": "es2020",
    "baseUrl": ".",
    "paths": {
      "@common/*": ["./common/src/*"],
      "@module-one/*": ["./module-one/src/*"]
    }
  },
  "module": {
    "type": "commonjs"
  }
}
```

```gitignore
node_modules
build
.DS_Store
```

**Note**: Configurations for `jest`, `eslint` and `prettier` can also be added globally i.e. to the root `package.json`.

For reference, `jest` config entry inside root `package.json` will look like this.

```json
{
  "jest": {
    "transform": {
      "^.+\\.(t|j)sx?$": "@swc/jest"
    },
    "testEnvironment": "node",
    "modulePathIgnorePatterns": [
      "<rootDir>/build/"
    ],
    "moduleNameMapper": {
      "@common/(.*)": "<rootDir>/common/src/$1",
      "@module-one/(.*)": "<rootDir>/module-one/src/$1"
    }
  },
}
```


##### Root level scripts

```json
{
  "scripts": {
    "build": "npm run type-check && swc ./*/src --out-dir build",
    "type-check": "tsc --noEmit",
    "test": "jest",
    "fmt": "npx prettier --write ./*/src/",
    "lint": "npx eslint --fix ./*/src/ --ext .ts",
    "clean": "rm -rvf ./build"
  },
}
```

##### Usage example

```ts
// file: common/src/entities.ts
import crypto from "node:crypto"

class Password {
  private value: string

  constructor(clearText: string) {
    this.value = clearText
  }
}

export class User {
  public id: string
  public password: Password

  constructor(
    public email: string,
    password: string,
  ) {
    this.id = crypto.randomUUID()
    this.password = new Password(password)    
  }
}
```

```ts
// file: module-one/src/main.ts
import { User } from "@common/user"

async function main() {
  const user = new User("admin@site.com", "abc123123123")
  console.log(user)
}

main().catch(console.error)
```

For references, `module-one` `package.json` will have the following script.

```json
{
  "scripts": {
    "start": "NODE_ENV=production node ../build/module-one/src/main.js"
  },
}
```

```bash
# build using root command
$ npm run build

# execute module one entry-point
$ npm run start -w module-one
```

