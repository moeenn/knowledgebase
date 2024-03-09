
#### Installation

```bash
$ sudo apt-get install -y php php-mbstring php-zip php-yaml php-xml php-uuid php-sqlite3 php-gd php-json php-curl composer 
```

#### Static Analysis (i.e. linting)

```bash
# add linter to current project
$ composer require --dev phpstan/phpstan

# run with max strictness
$ vendor/bin/phpstan analyse --level=max src
```

**Note**: PHPStan can be also be configured using a config file named `phpstan.neon` located at the root of the project. Sample contents look like this.

```yaml
parameters:
    paths:
        - src
    level: max
    ignoreErrors:
    excludePaths:
```

**Note**: The `max` level for PHPStan has the numeric value of `9`,


#### VS-Code Extensions

```
- [ ] PHP Intelephense
- [ ] phpfmt - PHP formatter
```