
```bash
# create project
$ npm create vite@latest

# install dev dependencies
$ npm i -D @types/node
```

#### Setting up Tailwind

```bash
$ npm install -D tailwindcss postcss autoprefixer
$ npx tailwindcss init -p
```

Open up the `tailwind.config.js` file and add the content

```js
/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html",
    "./src/**/*.{js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {},
  },
  plugins: [],
}
```

Add the following directives to the main `css` file

```css
@tailwind base;
@tailwind components;
@tailwind utilities;
```


#### Setting up absolute imports

Add the following to the `vite.config.ts`

```ts
import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import path from "node:path"
import process from "node:process"

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [vue()],
  server: {
    port: 3000,
  },
  resolve: {
    alias: {
      "@": path.resolve(process.cwd(), "src"),
    },
  },
})
```

Add the following to the `tsconfig.json` file

```json
{
  "compilerOptions": {
    "baseUrl": "./src",
    "paths": {
      "@/*": ["./*"]
    }
  }
}
```


#### Loading environment variables

```ts
// file: vite.config.ts
import { defineConfig, loadEnv } from 'vite'
import react from '@vitejs/plugin-react'
import path from "node:path"
import process from "node:process"

// https://vitejs.dev/config/
export default ({ mode }) => {
  process.env = {...process.env, ...loadEnv(mode, process.cwd())}

  return defineConfig({
    plugins: [react()],
    server: {
      port: 5000,
    },
    resolve: {
      alias: {
        "@": path.resolve(process.cwd(), "src"),
      },
    },
  })  
}
```

**Note**: Following rules apply for environment files
- `.env.development` will be loaded in development mode
- `.env.production` will be loaded in production mode
- `.env` will be loaded in all cases

All environment variables must be prefixed with `VITE_` for them be accessible inside front-end code. Example `.env.development` file may look something like this.

```
VITE_API_URL=http://localhost:3000
```

In order to access the environment variables inside the code, we can access them through the special `import.meta.env` object.

```js
console.log(import.meta.env.VITE_API_URL)
```

**Note**: The `.env.*` files will be not be included in the production output build. The environment variables will be inlined during build process.

Read more about `vite` environment variables [Link](https://vitejs.dev/guide/env-and-mode.html#env-variables).


