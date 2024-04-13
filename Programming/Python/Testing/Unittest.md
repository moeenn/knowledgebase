```python
# file: operations.py
def add(a: int, b: int) -> int:
    return a + b


def div(a: int, b: int) -> float:
    if b == 0:
        raise Exception("cannot divide by zero")

    return a / b
```

```python
# file: operations_test.py
from unittest import TestCase
from .operations import add, div
from dataclasses import dataclass


@dataclass
class Scenario:
    input: list[int]
    expected: float


class TestOperations(TestCase):
    def test_add(self) -> None:
        scenarios: list[Scenario] = [
            Scenario([10, 30], 40),
            Scenario([10, 0], 10),
        ]

        for scenario in scenarios:
            got = add(*scenario.input)
            self.assertEqual(got, scenario.expected)

    def test_mul(self) -> None:
        scenarios: list[Scenario] = [
            Scenario([100, 10], 10.0),
            Scenario([10, 4], 2.5),
        ]

        for scenario in scenarios:
            got = div(*scenario.input)
            self.assertEqual(got, scenario.expected)

    # test if error is thrown
    def test_mul_throws(self) -> None:
        with self.assertRaises(Exception):
            div(100, 0)
```


##### Running the tests
```bash
$ python -m unittest ./src/**/*_test.py
```


#### Assertions
| Type | Meaning |  
| -------: | :------ |  
| assertEqual(a, b) | a == b |
| assertNotEqual(a, b) | a != b | 
| assertTrue(x) | bool(x) is True |
| assertFalse(x) | bool(x) is False |
| assertIs(a, b) | a is b |
| assertIsNot(a, b) | a is not b |
| assertIsNone(x) | x is None  |
| assertIsNotNone(x) | x is not None |
| assertIn(a, b) | a in b  |
| assertNotIn(a, b) | a not in b  |
| assertIsInstance(a, b) | isinstance(a, b)  |
| assertNotIsInstance(a, b) | not isinstance(a, b)  |

