
#### Installation

```bash
$ npm install -D prettier
```


#### Config
Configuration inside `package.json` file.

```json
{
  ...
  "prettier": {
    "singleQuote": false,
    "semi": false,
    "tabWidth": 2,
    "trailingComma": "all"
  },
  ...
}
```


#### Running `prettier`

```bash
$ npx prettier --write ./src/
```