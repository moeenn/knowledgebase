
#### Comprehensive example

```php
<?php

declare (strict_types = 1);

namespace Moeen\Sandbox;

interface Serializable
{
    public function serialize(): string;
}

class Position implements Serializable
{
    public function __construct(
        public int $x = 0,
        public int $y = 0
    ) {
        $this->x = $x;
        $this->y = $y;
    }

    public static function origin(): self
    {
        return new Position(0, 0);
    }

    #[\Override]
    public function serialize(): string
    {
        return "Position(x={$this->x}, y={$this->y})";
    }
}

enum Direction {
    case LEFT;
    case RIGHT;
    case UP;
    case DOWN;
}

interface Movable
{
    public function move(Direction $direction): void;
}

class Entity implements Movable, Serializable
{
    public readonly string $name;
    public Position $position;
    private const int STEP = 10;

    public function __construct(string $name, Position $position)
    {
        $this->name = $name;
        $this->position = $position;
    }

    #[\Override]
    public function move(Direction $d): void
    {
        switch ($d) {
            case Direction::UP:
                $this->position->y += self::STEP;
                break;

            case Direction::DOWN:
                $this->position->y -= self::STEP;
                break;

            case Direction::LEFT:
                $this->position->x -= self::STEP;
                break;

            case Direction::RIGHT:
                $this->position->x += self::STEP;
                break;

            default:
                throw new \Exception("invalid direction");
        }
    }

    #[\Override]
    public function serialize(): string
    {
        $pos = $this->position->serialize();
        return "Entity(name={$this->name}, position={$pos})";
    }
}

class App
{
    public static function main(): void
    {
        $entity = new Entity("Entity one", Position::origin());
        echo $entity->serialize() . PHP_EOL;
    }
}

App::main();
```


### TODO: Traits
