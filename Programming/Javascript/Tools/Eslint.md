
#### Installation

```bash
$ npm install -D eslint

# install with typescript parsing
$ npm install -D eslint @typescript-eslint/eslint-plugin @typescript-eslint/parser
```


#### Configuration 

Plain JS project config entry inside `package.json` file.

```json
{
  ...
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

Typescript project config inside `package.json` file.

```json
{
  ...
  "eslintConfig": {
    "root": true,
    "parser": "@typescript-eslint/parser",
    "plugins": [
      "@typescript-eslint"
    ],
    "extends": [
      "eslint:recommended",
      "plugin:@typescript-eslint/recommended"
    ],
    "rules": {
      "no-console": "error",
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


#### Running `eslint`

```bash
# for plain javascript projects
$ npx eslint ./src/ --ext .mjs

# for typescript projects
$ npx eslint ./src/ --ext .ts
```