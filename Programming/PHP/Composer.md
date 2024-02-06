
```bash
# instantiate a project
$ composer init

# run scripts defined inside composer.json
$ composer run-script script_name

# install packages listed inside composer.lock file
# if file does not exist, looks for packages listed inside composer.json file
$ composer install

# add package to project (prod dependency)
$ composer require vendor/package

# add package to project (dev dependency)
$ composer require vendor/package --dev

# remove package from project
$ composer remove vendor/package

# list all outdated packages
$ composer outdated --direct

# update proect dependencies
$ composer update --with-dependencies

# update a specific dependency
$ composer update vendor/package

# update composer.lock without updating packages
$ composer update --lock

# generate optimized autoload dump
$ composer dumpautoload -o
```


#### `composer.json` Scripts

```json
{
	"scripts": {
        "dev": "@php src/index.php"
    }
}
```

```json
{
    "scripts": {
        "test": [
            "@clearCache",
            "phpunit"
        ],
        "clearCache": "rm -rf cache/*"
    }
}
```

**Note**: Scripts defined inside the `composer.json` file can be invoked in two ways

```bash
$ composer run-script <script-name>
# OR
$ composer <script-name>
```