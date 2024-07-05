```
src/
	main.rs
	position.rs
	direction.rs
	entity.rs
```

```rust
// file: main.rs
mod direction;
mod entity;
mod position;

use direction::Direction;
use entity::Entity;

fn main() {
    let mut e = Entity::new("Entity One");
    e.update_position(Direction::Down);
    e.update_position(Direction::Right);

    println!("{}", e);
}
```

- The root module is called `crate`. 
- `mod` keyword is used to declare a sub-module, thereby creating a hierarchy of modules.
- `use` keyword is used to bring a symbol into the scope of the current module. This way we don't have yo type the entire symbol path every time.

```rust
// file: direction.mjs
pub enum Direction {
    Up,
    Down,
    Left,
    Right,
}
```

```rust
// file: position.mjs
use std::fmt;

pub struct Position {
    pub x: i32,
    pub y: i32,
}

impl Position {
    pub fn origin() -> Self {
        Position { x: 0, y: 0 }
    }
}

impl fmt::Display for Position {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Position (x={}, y={})", self.x, self.y)
    }
}
```

```rust
// file: entity.rs
use std::fmt;

// access modules by their position in the module hierarchy
use crate::position::Position;
use crate::Direction;

pub struct Entity<'a> {
    pub name: &'a str,
    pub position: Position,
}

impl<'a> Entity<'a> {
    pub fn new(name: &'a str) -> Self {
        Entity {
            name,
            position: Position::origin(),
        }
    }

    pub fn update_position(&mut self, d: Direction) {
        match d {
            Direction::Up => self.position.y += 1,
            Direction::Down => self.position.y -= 1,
            Direction::Left => self.position.x -= 1,
            Direction::Right => self.position.x += 1,
        }
    }
}

impl<'a> fmt::Display for Entity<'a> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Entity (name={}, position={})", self.name, self.position)
    }
}
```
