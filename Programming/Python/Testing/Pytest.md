```bash
# installation 
$ pip3 install pytest
```

```python
# file: utilities.py
def add(x: int, y: int) -> int:
  return x + y 

def multiply(x: int, y: int) -> int:
  return x * y
```

```python
# file: test_utilities.py
import utilities

def test_add() -> None:
  assert utilities.add(10, 20) == 30
  assert utilities.add(10, -10) == 0
  assert utilities.add(100, 0) == 100

def test_multiply() -> None:
  assert utilities.multiply(10, 20) == 200
  assert utilities.multiply(200, -1) == -200
  assert utilities.multiply(0, 20) == 0
```

**Note**: The name of the test functions is important. If we don’t use the format `test_`, `pytest` will not recognize it as a unit test.

```bash
$ pytest -v ./test_utilities.py
```


---

#### Testing classes

```python
# file: student.py
class Student:
  name: str
  marks: int

  def __init__(self, name: str) -> None:
    self.name = name
    self.marks = 0

  def set_marks(self, marks: int) -> None:
    self.marks = marks

  def grade(self) -> str:
    if self.marks < 40:
      return "F"
    elif self.marks < 80:
      return "B"
    elif self.marks < 100:
      return "A"
    else:
      return "A+"
```

```python
# file: test_student.py
from student import Student

def test_grade_f() -> None:
  student = Student("Mr. Example")
  student.set_marks(30)
  assert student.grade() == "F"

def test_grade_b() -> None:
  student = Student("Mr. Example")
  student.set_marks(50)
  assert student.grade() == "B"

def test_grade_a() -> None:
  student = Student("Mr. Example")
  student.set_marks(85)
  assert student.grade() == "A"

def test_grade_ap() -> None:
  student = Student("Mr. Example")
  student.set_marks(110)
  assert student.grade() == "A+"
```


---

#### Setup and teardown

```python
# file: test_student.py
from student import Student

def setup_module(module) -> None:
  global student
  student = Student("Mr. Example")

def teardown_module(module) -> None:
  global student
  del student

def test_grade_f() -> None:
  student.set_marks(30)
  assert student.grade() == "F"

def test_grade_b() -> None:
  student.set_marks(50)
  assert student.grade() == "B"

def test_grade_a() -> None:
  student.set_marks(85)
  assert student.grade() == "A"

def test_grade_ap() -> None:
  student.set_marks(110)
  assert student.grade() == "A+"
```


---

#### Testing for specific error

```python
# file: test_project.py
def test_divide():
    with pytest.raises(ZeroDivisionError):
        assert calc.divide(10,0)
```

