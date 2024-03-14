
```js
/** @typedef {"Up" | "Down" | "Left" | "Right"} Direction */
/** @type {Record<Direction, Direction>} */
const Direction = {
  Up: "Up",
  Down: "Down",
  Left: "Left",
  Right: "Right",
}

class Position {
  /** @type {number} */
  x

  /** @type {number} */
  y

  /**
   * @param {number} x
   * @param {number} y
   */
  constructor(x, y) {
    this.x = x
    this.y = y
  }

  /**
   * alternative constructor
   * @returns {Position}
   */
  static origin() {
    return new Position(0, 0)
  }
}

class Entity {
  /** @type {string} */
  name

  /** @type {Position} */
  position

  /** @type {number} */
  static step

  /**
   * @param {string} name
   * @param {Position} position
   */
  constructor(name, position) {
    this.name = name
    this.position = position
  }

  /** this block runs, when a static member is accessed for the first time */
  static {
    Entity.step = 10
  }

  /**
   * @param {keyof typeof Direction} direction
   * @returns {void}
   */
  move(direction) {
    switch (direction) {
      case "Up":
        this.position.y += Entity.step
        break

      case "Down":
        this.position.y -= Entity.step
        break

      case "Left":
        this.position.x -= Entity.step
        break

      case "Right":
        this.position.x += Entity.step
        break
    }
  }

  /**
   * @returns {string}
   */
  toString() {
    return `${this.name} as position (${this.position.x}, ${this.position.y})`
  }
}

/** @returns {void} */
function main() {
  const e = new Entity("Entity one", Position.origin())
  e.move(Direction.Right)
  e.move(Direction.Right)

  console.log(e.toString())
}
```