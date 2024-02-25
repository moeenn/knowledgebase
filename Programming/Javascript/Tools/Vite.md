
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