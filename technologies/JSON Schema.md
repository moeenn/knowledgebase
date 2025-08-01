
#### Basic types

- `integer`
- `number`
- `string`
- `boolean`
- `object`
- `array`


#### Basic nested objects

```json
{
  "type": "object",
  "additionalProperties": false,
  "required": ["name", "address"],
  "properties": {
    "name": {
      "type": "string"
    },
    "address": {
      "type": "object",
      "required": ["country", "city"],
      "properties": {
        "country": { "type": "string" },
        "city": { "type": "string" }
      }
    }
  }
}
```


#### Enumerated values

```json
{
  "type": "object",
  "required": ["name", "status"],
  "properties": {
    "name": {
      "type": "string"
    },
    "status": {
      "enum": ["active", "inactive", "pending-approval"]
    }
  }
}
```

```json
{
  "type": "object",
  "required": ["rating"],
  "properties": {
    "rating": {
      "enum": [1,2,3,4,5]
    }
  }
}
```


#### Array of objects

```json
{
  "type": "array",
  "items": {
    "type": "object",
    "required": ["name", "level"],
    "properties": {
      "name": { "type": "string" },
      "level": {
        "enum": ["beginner", "intermediate", "advanced"]
      }
    }
  }
}
```


#### String constraints

`string` type supports `minLength`, `maxLength`, `pattern` constraints.

```json
{
  "type": "object",
  "required": ["name"],
  "properties": {
    "name": {
      "type": "string",
      "minLength": 3,
      "maxLength": 20
    }
  }
}
```

```json
{
  "type": "object",
  "required": ["phone"],
  "properties": {
    "phone": {
      "type": "string",
      "pattern": "^[0-9]{10}$"
    }
  }
}
```

**Note**: `pattern` takes in a regular expression as value.


#### Number constraints

`number` / `integer` type supports `minimum`, `maximum`, `exclusiveMinimum`, `exclusiveMaximum`, `multipleOf` constraints.

```json
{
  "type": "object",
  "required": ["year", "month", "day"],
  "properties": {
    "year": { "type": "integer", "minimum": 1964, "maximum": 2024 },
    "month": { "type": "integer", "minimum": 1, "maximum": 12 },
    "day": { "type": "integer", "minimum": 1, "maximum": 31 }
  }
}
```

**Note**: `minimum` and `maximum` are inclusive constraints.


#### Array constraints

`array` type supports `minItems`, `maxItems`, `unique` constraints.