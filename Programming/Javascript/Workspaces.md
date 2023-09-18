`workspaces` is a features provided by `npm` to create `monorepos` and share code between different projects.


---

#### Example

```
monorepo-project
	package.json
	tsconfig.json
	backend/
		package.json
		src/
			index.ts
	frontend/
		package.json
		src/
			index.ts
```

We can initialize top level package by running the following familiar command

```bash
$ npm init -y
```

Next, we can initialize the sub-packages using the following commands

```bash
$ npm init -y -w frontend
$ npm init -y -w backend
```


---

#### Configurations
After creating new work-spaces using the above command, you will notice the following section in the top-level `package.json`. This will help us import symbols between the `frontend` and `backend` packages.

```json
{
  ...
  "workspaces": [
    "frontend",
    "backend"
  ],
  ...
}
```

We must also configure `typescript` to look for code files inside `src` folders inside the sub-package directories. Add the following section to the top-level `tsconfig.json`.

```json
{
  "compilerOptions": {
    ...
    "baseUrl": ".",
    "paths": {
      "frontend/*": [
        "frontend/src/*"
      ],
      "backend/*": [
        "backend/src/*"
      ]
    }
  }
}
```


---

#### Importing types between sub-packages

```ts
// file: backend/src/index.ts
export type User = {
  id: number
  email: string
  isActive: boolean
}
```

The above type defined inside the `backend` package can be imported inside the `frontend` package as follows

```ts
// file: frontend/src/index.ts
import { User } from "backend/index"
```
