
#### Configure linting

```bash
$ composer require --dev phpstan/phpstan nunomaduro/larastan
```

Create the `phpstan.neon` file at the root of the project and add the following content

```yaml
includes:
    - ./vendor/nunomaduro/larastan/extension.neon

parameters:
    paths:
        - app
        - database
        - tests
    level: max
```

Add the following line to the scripts inside `composer.json` file

```json
{
  "scripts": {
    "check": "vendor/bin/phpstan analyse"
  }
}
```

