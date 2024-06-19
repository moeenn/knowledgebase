```bash
# add useful components
$ composer require symfony/orm-pack symfony/uid 
$ composer require --dev symfony/maker-bundle
```


```bash
# start dev server
$ symfony server:start --no-tls

# make entity (with repository)
$ symfony console make:entity <entity-name>

# make migration
$ symfony console make:migration

# run migrations
$ symfony console doctrine:migrations:migrate

# make controller (with view related files)
$ symfony console make:controller <controller-name>
```

