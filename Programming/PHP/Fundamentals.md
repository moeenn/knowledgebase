
#### Functions

```php
namespace Moeen\Sandbox;

enum UserRole {
    case ADMIN;
    case CUSTOMER;
}

class User 
{
    public function __construct(
        private string $name,
        private string $email,
        private UserRole $role,
    ) {}

    #[\Override]
    public function __toString(): string
    {
        $role = $this->role->name;
        return "User(name={$this->name}, email={$this->email}, age={$role})";
    }
}

class App
{
    public static function main(): void
    {
        /**
         * pass method / function arguments as named arguments
         * 
         */ 
        $user = new User(
            name: "admin",
            email: "admin@sit.com",
            role: UserRole::ADMIN,
        );

        echo $user . PHP_EOL;
    }
}

App::main();
```


---

#### References

```php
readonly class User
{
    public function __construct(
        public string $name,
        public string $email,
    ) {}
}

class UserManager
{
    /**
     * pass user object by reference.
     * 
     */
    public function processUser(User &$user): void
    {
        echo "Processing user: {$user->email}\n";
    }
}

class App
{
    public static function main(): void
    {
        $userManager = new UserManager();
        $users = [
            new User("Mr. Admin", "admin@site.com"),
            new User("Customer", "customer@site.com"),
        ];

        /**
         * loop using references instead of creating copies
         *
         */
        foreach ($users as &$user) {
            $userManager->processUser($user);
        }
    }
}

App::main();
```


---

