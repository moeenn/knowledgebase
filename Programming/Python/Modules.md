There are three types of imports 

1. Generic Import: Import an entire module
2. Function Import: Import a specific function from a module
3. Universal Import: Import all functions from a module


##### Generic import
```python
import random

# print a random integer between 1 and 10 inclusive
print(random.randint(1,10))
```


##### Function import 
```python
from random import randint


print(randint(1,10))
```


##### Universal Import (not recommended)
```python
from random import *

print(randint(1,10)) 
```

 Generic import and universal import do the same thing. The only difference is in the syntax of calling module functions. This is not recommended because it makes it difficult to find which module contains the function.


---

#### Custom modules

##### Importing files

```python
# file: utils.py
def hello() -> None:
    print("Hello world")
```

```python
# file: main.py
import utils

utils.hello()
```


##### Defining module

```python
# file: utils/__init__.py
def power(base: int, exp: int) -> int:
    return base ** exp
```

```python
# file: main.py
import utils

res = utils.power(10, 20)
print(res)
```

Multiple files can be defined inside a single module.

```python
# file: utils/math.py
def add(x: int, y: int) -> int:
    return x + y
```

```python
# file: utils/__init__.py
# this file is empty but needs to be created
```

```python
# file: main.py
from utils import math

res = math.add(10, 20)
print(res)
```


##### Example

```python
# file: utils/math.py
def add(x: int, y: int) -> int:
  return x + y

def double(n: int) -> int:
  return n * 2
```

```python
# file: utils/__init__.py
from utils.math import add, double
```

```python
# file: main.py
import utils

res = utils.add(10, 20)
print(res)
```
