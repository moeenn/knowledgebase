
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
    "tabWidth": 4,
    "trailingComma": "all",
	"printWidth": 120
  },
  ...
}
```


#### Running `prettier`

```json
{
  "scripts": {
    "fmt": "npx prettier --write ./src/"
  }
}
```
