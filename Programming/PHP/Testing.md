
```bash
$ composer require --dev phpunit/phpunit
```


#### Configuration file

`phpunit` configurations are placed inside the `phpunit.xml` file located at the root of the project.

```xml
<phpunit colors="true" bootstrap="vendor/autoload.php">
    <testsuites>
        <testsuite name="Project Tests">
            <directory>tests</directory>
        </testsuite>
    </testsuites>
</phpunit>
```


#### Running tests

```bash
# run tests
$ vendor/bin/phpunit

# debug issues with autoloading files
$ composer dump-autoload -o
```


#### Basic example

```php
// file: src/App.php
<?php declare(strict_types=1);

namespace App;

class App
{
    public static function main(): void
    {
        echo 'Hello world' . PHP_EOL;
    }

    public function customAction(int $n): int
    {
        return $n * 2;
    }
}

App::main();
```

```php
// file: tests/AppTest.php
<?php declare(strict_types=1);

use App\App;
use PHPUnit\Framework\TestCase;

final class AppTest extends TestCase
{
    public function testResult()
    {
        $app = new App();
        $this->assertEquals($app->customAction(10), 20);
    }
}

```