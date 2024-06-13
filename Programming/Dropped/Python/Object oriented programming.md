```python
from __future__ import annotations
from enum import Enum, auto


# inherit from Enum class
class Direction(Enum):
    LEFT = auto()
    RIGHT = auto()
    UP = auto()
    DOWN = auto()


class Entity:
    # __ means private member
    __x: int
    __y: int
    __protected_step: int = 10

    # constructor
    def __init__(self, x: int, y: int) -> None:
        self.__x = x
        self.__y = y

    # allow printing to console
    def __repr__(self) -> str:
        return f"Entity(x={self.__x}, y={self.__y})"

    # computed property
    @property
    def position(self) -> tuple[int, int]:
        return (self.__x, self.__y)

    # class method, returning self allows method chaining
    def move(self, direction: Direction) -> Entity:
        match direction:
            case Direction.LEFT:
                self.__x -= self.__protected_step
            case Direction.RIGHT:
                self.__x += self.__protected_step
            case Direction.UP:
                self.__y += self.__protected_step
            case Direction.DOWN:
                self.__y -= self.__protected_step

        return self


# inherit from base class
class Player(Entity):
    name: str

    def __init__(self, name: str, x: int, y: int) -> None:
        # initialize base class
        super().__init__(x, y)
        self.name = name


def main() -> None:
    player = Player("Player One", 10, 20)
    player.move(Direction.RIGHT).move(Direction.UP)
    print(player.position)
```


---

#### Operator overloading

```python
from __future__ import annotations
from dataclasses import dataclass


@dataclass
class Complex:
    real: float
    imag: float

    def __add__(self, other: Complex) -> Complex:
        return Complex(
            real=self.real + other.real,
            imag=self.imag + other.imag,
        )

    def __mul__(self, other: Complex) -> Complex:
        return Complex(
            real=self.real * other.real,
            imag=self.imag * other.imag,
        )


def main() -> None:
    c_one = Complex(5, 3)
    c_two = Complex(4, 2)
    print(c_one * c_two)
```

| Operator | Method name            |
| -------: | :--------------------- |
|      `+` | `__add__(self, other)` |
|      `-` | `__sub__(self, other)` |
|      `*` | `__mul__(self, other)` |
|      `/` | `__div__(self, other)` |
|      `<` | `__lt__(self, other)`  |
|      `>` | `__gt__(self, other)`  |
|     `<=` | `__le__(self, other)`  |
|     `>=` | `__ge__(self, other)`  |


---

#### Abstract classes

```python
from abc import ABC, abstractmethod

class Entity(ABC):
    @abstractmethod
    def move(self, x: int, y: int) -> None:
        pass

    @abstractmethod
    def display(self) -> str:
        pass


class Player(Entity):
    x: int
    y: int

    def __init__(self) -> None:
        self.x = 0
        self.y = 0

    def move(self, x: int, y: int) -> None:
        self.x = x
        self.y = y

    def display(self) -> str:
        return f"({self.x}, {self.y})"


def display_entity(e: Entity) -> None:
    print(e.display())



def main() -> None:
    p = Player()
    p.move(10, 20)
    display_entity(p)
```


---

#### Slots

```python
from enum import Enum, auto


class IPKind(Enum):
    V4 = auto()
    V6 = auto()


class IP:
    kind: IPKind
    address: str

    def __init__(self, kind: IPKind, address: str) -> None:
        self.kind = kind
        self.address = address

    def __str__(self) -> str:
        return f"IP(kind={self.kind}, address={self.address})"


def main() -> None:
    ip = IP(IPKind.V4, "208.67.222.222")
    print(ip.__dict__)

# {'kind': <IPKind.V4: 1>, 'address': '208.67.222.222'}
```

Python stores all instance variables as a dictionary. This dictionary can also be accessed using the class dunder property `__dict__`.  This presents two problems

- Dictionaries in python are implemented through Hash-maps and there is a performance penalty due to that. 
- New arbitrary properties can be added to these class instances and Python will not raise any warnings.

```python
ip = IP(IPKind.V4, "208.67.222.222")

# this doesn't raise any runtime errors (but mypy does!)
ip.test = "test"
```

We can add slots to our Class and it will fix both the above problems

```python
class IP:
    __slots__ = "kind", "address"

    def __init__(self, kind: IPKind, address: str) -> None:
        self.kind = kind
        self.address = address

    def __str__(self) -> str:
        return f"IP(kind={self.kind}, address={self.address})"


def main() -> None:
    ip = IP(IPKind.V4, "208.67.222.222")

    # this is now a runtime error as well as a mypy error
    ip.test = "test"
```


---

#### Dataclasses

```python
class Entity:
    x: int
    y: int

    def __init__(self, x: int, y: int) -> None:
        self.x = x
        self.y = y

    def __str__(self) -> str:
        return f"({self.x}, {self.y})"



def main() -> None:
    e_one: Entity = Entity(10, 20)
    print(e_one == e_two)
```

**Note**: An ordinary class is not printable by default (we must define the `__str__` or `__repr__` method). It is also not possible to compare simple class instances.

```python
from dataclasses import dataclass



@dataclass
class Entity:
    x: int
    y: int



def main() -> None:
    e_one: Entity = Entity(10, 20)
    e_two: Entity = Entity(10, 20)

    print(e_one == e_two)
```


---

##### Sorting & Comparing

```python
from dataclasses import dataclass, field



@dataclass(order=True)
class Person:
    sort_order: int = field(init=False, repr=False)
    name: str
    age: int

    def __post_init__(self) -> None:
        self.sort_order = self.age



"""
    program entry-point
"""
def main() -> None:
    p_one = Person("User One", 20)
    p_two = Person("User Two", 24)

    print(p_one > p_two)
    print(p_two)
```

- `init=False` means the class can be instantiated without providing value for this member field
- `repr=False` means the field will not shown when class instance is printed 


---

##### Default values

```python
@dataclass
class Person:
    name: str
    age: int = 100
```


---

##### Frozen objects

```python
from dataclasses import dataclass, field


@dataclass(order=True, frozen=True)
class Person:
    sort_order: int = field(init=False, repr=False)
    name: str
    age: int = 100

    def __post_init__(self) -> None:
        object.__setattr__(self, "sort_order", self.age)
```

**Note**: If an object is frozen, we cannot set the `sort_order` property in the `__post_init__` method. The code above provides a work-around.


---

##### Performance improvement through Slots

```python
from enum import Enum, auto
from dataclasses import dataclass


class IPKind(Enum):
    V4 = auto()
    V6 = auto()


@dataclass(slots=True)
class IP:
    kind: IPKind
    address: str


def main() -> None:
    ip = IP(IPKind.V4, "208.67.222.222")
    print(ip)
```

**Note**: Slots is not a `dataclass` specific feature, it can also be used with regular classes. Slots can be used with `dataclasses` in **Python 3.10** and above.
