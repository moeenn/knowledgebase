```bash
$ npm i -D jest @types/jest ts-jest
```


Add the following section to the `package.json` file

```json
{
  "scripts": {
    "test": "jest"
  },
  "jest": {
    "preset": "ts-jest",
    "testEnvironment": "node",
    "modulePathIgnorePatterns": ["<rootDir>/build/"],
    "moduleNameMapper": {
      "@/(.*)": "<rootDir>/src/$1"
    }
  }
}
```