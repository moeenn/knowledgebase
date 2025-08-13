
#### Installation

```bash
$ npm install -D eslint typescript-eslint
```


---

#### Configuration 

**Typescript project** config inside  `eslint.config.js` file.

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

**Plain Javascript project** config.

```json
{
  "scripts": {
    "lint": "npx eslint --fix ./src/ --ext .mjs"
  },
  ...
}
```

```js
import jsdoc from "eslint-plugin-jsdoc"

export default [
  {
    plugins: {
      jsdoc: jsdoc
    },
    rules: {
      "jsdoc/check-values": "error",
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
  }
]
```