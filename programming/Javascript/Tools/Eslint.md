
#### Installation

```bash
$ npm install -D eslint typescript-eslint
```


#### Configuration 

**Typescript project** config inside `package.json` file.
`eslint.config.js` file:

```js
import tseslint from "typescript-eslint"

export default [
    { files: ["**/*.{ts,tsx}"] },
    ...tseslint.configs.recommended,
    {
        rules: {
			"no-warning-comments": [
                "warn",
                { terms: ["TODO", "FIXME"], location: "anywhere" },
            ],
            "no-console": "warn",
            quotes: [
                "warn",
                "double",
                {
                    allowTemplateLiterals: true,
                    avoidEscape: true,
                },
            ],
            semi: ["warn", "never"],
            "no-unused-vars": "warn",
        },
    },
]
```

```json
{
	"lint": "npx eslint --fix ./src/ --ext .ts"
}
```

**Plain JS project** config entry inside `package.json` file.

```json
{
  "scripts": {
    "lint": "npx eslint --fix ./src/ --ext .mjs"
  },
  "eslintConfig": {
    "root": true,
    "extends": "eslint:recommended",
    "env": {
      "node": true,
      "es6": true
    },
    "parserOptions": {
      "sourceType": "module",
      "ecmaVersion": "latest"
    },
    "rules": {
      "no-console": "warn",
      "quotes": [
        "warn",
        "double",
        {
          "allowTemplateLiterals": true,
          "avoidEscape": true
        }
      ],
      "semi": ["warn", "never"],
      "no-unused-vars": "warn"
    }
  },
  ...
}
```
