#### Printing to console
```python
# print message with new line at the end
print("Hello world")

# print formatted message
print("Hello %s, are you %d years old?" % ("User", 20))

# print without new line at the end
print("Hello there", end="")
```

##### Comments
```python
# This is a single line comment

"""
      This is a multiline comment
      Also known as comment-block
"""
```


---

#### Operators

|                 Type | Operator   | Explanation             |     |
| -------------------: | :--------- | :---------------------- | --- |
| Arithmetic operators | `()`       | Precedence 1st          |     |
|                      | `**`       | Precedence 2nd          |     |
|                      | `% / // *` | Precedence 3rd          |     |
|                      | `+ -`      | Precedence 4th          |     |
|   Compound operators | `+=`       |                         |     |
|                      | `-=`       |                         |     |
|                      | `*=*`      |                         |     |
|                      | `/=`       |                         |     |
|                      | `**=`      | Power and equal         |     |
|                      | `%=`       | Mod and equal           |     |
|                      | `//=`      | Floor divisor and equal |     |
|    Logical operators | `not`      | Precedence 1st          |     |
|                      | `and`      | Precedence 2nd          |     |
|                      | `or`       | Precedence 3rd          |     |


---

#### Match
```python
# basic example
def run_command(command: str) -> None:
    match command:
        case "reset":
            print("resetting system")
        case "exit":
            print("exiting...")
            exit()
        case other:
            print(f"unrecognized command: '{command}'")


def main() -> None:
    while True:
        command = input("$ ")
        run_command(command)
```

```python
# more advanced usages
def run_command(command: str) -> None:
    match command.split():
        case ["load" | "open", filename]:
            print(f"opening file: {filename}")
        case ["save"]:
            print("saving current file")
        case ["quit" | "exit", *rest] if "--force" in rest or "-f" in rest:
            print("force exiting...")
            exit()
        case ["quit" | "exit"]:
            print("exiting...")
            exit()
        case _:
            print(f"unrecognized command: '{command}'")


def main() -> None:
    while True:
        command = input("$ ")
        run_command(command)
```


---

#### String
```python
message: str = "Hello world"

# access a character using subscript 
alphabet: str = message[0]

# access first five characters
word: str = message[:5]

# access last five words
last_word: str = message[6:11]

# length of string
length: int = len(message)

# convert number to string
num_string: str = str(10)
```


##### String methods
| Operator | Description |  
| -------: | :------ |  
| `title()` | Capitalize the first letter of each word |  
| `upper()` | All letters are uppercase |
| `lower()` | All letters are lowercase |
| `strip()` | Remove whitespace from start and end of the string | 
| `lstrip()` | Remove whitespace from the start of the string | 
| `rstrip()` | Remove whitespace from the end of the string | 
| `split()` | Split string into a list depending on the delimiter | 
| `zfill()` | Adds zeros at the beginning of the string, until it reaches the specified length (provided as argument). |



##### Fstring - String interpolation
```python
name: str = "Mr. Client"
balance: float = 3000.5

message: str = f"Hello {name}, your current balance is USD {balance:.2f}"
print(message)

# Hello Mr. Client, your current balance is USD 3000.50
```


###### Formatting rules
| Operator | Description |  
| -------: | :------ |  
| `%s` | Strings |  
| `%d` | Integers |
| `%f` | Floats |
| `%.3f` | Floating point number with 3 decimal points |
| `%%` | Print out % symbol |


---

#### List

```python
nums: list[int] = [1, 2, 3, 4, 5]

# add element to end of list
nums.append(6)

# insert element at start of list (i.e. index 0)
nums.insert(0, 10)

# remove item from list
nums.remove(5)

# access element at index
result = nums[1]

# apply operation to all elements in list
mapped = map(lambda n: n * 2, nums)
print(list(mapped))

# filter out elements based on criteria
filtered = filter(lambda n: n % 2 == 0, nums)
print(list(filtered))

# sort a list - original is modified
nums.sort(reverse=False)
print(nums)

# loop through all elements in list (with index)
for i, v in enumerate(nums):
    print(i, v)

# check if element does not exist in list
if 5 not in nums:
    print("5 does not exist inside list")
```

```python
# list slices
nums: list[int] = [1, 2, 3, 4, 5]
slice: list[int] = nums[1:3]
print(slice)
```

```python
# list comprehensions
nums: list[int] = [n for n in range(1, 5)]
print(nums)                                 # [1, 2, 3, 4]

nums = [(n+1)*10 for n in range(1, 5)]
print(nums)                                 # [20, 30, 40, 50]

base: list[int] = [10, 21, 32, 44, 55]
nums = [n for n in base if n % 2 == 0]
print(nums)                                 # [10, 32, 44
```


---

#### Tuple
Tuples are an immutable collection of elements

```python
values: tuple[int, str, bool] = (300, "Someone", True,)
print(values)

# tuple comprehensions
nums: tuple[int, ...] = tuple(n for n in range(1, 4))
print(nums)  # (1, 2, 3)
```


---

#### Sets
Sets is a list of unique values. Values inside sets don’t have index values. Sets cannot be sliced.

```python
numbers: set[int] = {10, 20, 30, 20}
print(numbers)          # {10, 20, 30}

# add an element to set, order is not maintained
numbers.add(50)
print(numbers)          # {10, 50, 20, 30}

# remove an element from set
numbers.remove(10)
print(numbers)          # { 50, 20, 30}

# generate set using comprehensions
nums_set: set[int] = {n for n in range(1, 10)}
print(nums_set)
```


---

#### Dictionary
A dictionary is like a list but unlike lists dictionaries are used to store Key-Value Pairs. 

```python
capitals: dict[str, str] = {
    "Pakistan": "Islamabad",
    "China": "Beijing",
    "Japan": "Tokyo"
}

# read a value
value: str | None = capitals.get("China")
if value:
    print(value)

# add new values
capitals.update({"England": "London"})

# remove an item
del capitals["China"]

# check if value exists in dict
if "Japan" in capitals:
    print("Japan exists in records")

# loop over dict key and value
for k, v in capitals.items():
    print(k, v)
```

```python
# Dictionary comprehensions
names: list[str] = ["Stark", "Banner", "Steve", "Romanoff"]
heroes: list[str] = ["Iron Man", "Hulk", "Captain America", "Black Widow"]

identities: dict[str, str] = {
    name: hero for name, hero in zip(names, heroes)
}

print(identities)
# {'Stark': 'Iron Man', 'Banner': 'Hulk', 'Steve': 'Captain America', 'Romanoff': 'Black Widow'}

```

```python
# Pass (and spread) dictionary to function
def greet_user(name: str, email: str) -> None:
    print("Hello %s, you have registered with email %s" % (name, email))


def main() -> None:
    args: dict[str, str] = {
        "name": "someone",
        "email": "someone@site.com",
    }
    greet_user(**args)
```


---

#### Counter
Counter is a built-in class which can help keep track of item occurrences in lists. 

```python
from collections import Counter

c = Counter(["Python", "PHP"])
c.update(["Go", "JS"])
c.update(["PHP", "JS", "TS"])

print(c)
# Counter({'PHP': 2, 'JS': 2, 'Python': 1, 'Go': 1, 'TS': 1})

print(c.most_common(3))
# [('PHP', 2), ('JS', 2), ('Python', 1)]
```


---

#### Taking Input from User
```python
# interactive input
name: str = input("Please enter your name: ")
```

```python
import sys

# command-line arguments
for arg in sys.argv:
	    print(arg)
```


---

#### Functions
```python
# accept an unknown number of arguments
def variadic_func(*args: str) -> None:
    for arg in args:
        print(arg)


# program entry-point function
def main() -> None:
    nums: list[int] = [n for n in range(10)]
    print(nums)
    variadic_func("hello", "world")


# wrap entry-point function for error handling
if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("gracefully shutting down...")
    except Exception as err:
        print("error: ", err)
```

```python
# pass by value
def increment_num(num: int) -> None:
    num += 1


def main() -> None:
    num: int = 300
    increment_num(num)
    print(num)

# 300
```

```python
# pass by reference
def add_item(items: list[int], new_item: int) -> None:
    items.append(new_item)


def main() -> None:
    nums: list[int] = [i for i in range(1, 10)]
    add_item(nums, 300)
    print(nums)

# [1, 2, 3, 4, 5, 6, 7, 8, 9, 300]
```

```python
# lambdas
square = lambda n: n**2

# X is returned if X is larger than y, otherwise y is returned
greater = lambda x, y = x if x > y else y
```

```python
# Higher Order functions
from typing import Callable


# apply callback function to all values in the List
def map(values: list[int], callback: Callable[[int], int]) -> list[int]:
    return [callback(v) for v in values]


def main() -> None:
    nums: list[int] = [n for n in range(10)]
    new_nums: list[int] = map(nums, lambda n: n * 2)
```

```python
# closures
from typing import Callable


def generate_tag(html_tag: str) -> Callable[[str], None]:
    # free variable
    tag = html_tag

    def inline_msg(msg: str) -> None:
        html_code = f"<{tag}>{msg}</{tag}>"
        print(html_code)

    # return the inner function
    return inline_msg


def main() -> None:
    # run the outer function and assign inner function to variable (i.e. heading_1)
    heading_1 = generate_tag("h1")

    # run the inner function
    heading_1("This is a heading")
    heading_1("This is another heading")
```

```python
# generators
from typing import Iterator


# produce a generator
def list_generator(start: int, end: int) -> Iterator[int]:
    for element in range(start, end):
        yield element**2


def main() -> None:
    results = list_generator(1, 10)

    # prints reference of generator
    print(results)

    # prints first value: 1
    print(next(results))

    # loops over all remaining values
    for i in results:
        print(i)
```

```python
# Iterators
from __future__ import annotations


class RangeIterator:
    i: int = 0
    limit: int = 0

    def __init__(self, limit: int):
        self.limit = limit

    def __iter__(self) -> RangeIterator:
        return self

    def __next__(self) -> int:
        self.i += 1
        if self.i >= self.limit:
            raise StopIteration

        return self.i


def main() -> None:
    for i in RangeIterator(10):
        print(i)
```

**Note**: Above code can be made even better in **Python 3.11** by using the `Self` type.

```python
from typing import Self


class RangeIterator:
    i: int = 0
    limit: int = 0

    def __init__(self, limit: int):
        self.limit = limit

    def __iter__(self) -> Self:
        return self

    def __next__(self) -> int:
        self.i += 1
        if self.i >= self.limit:
            raise StopIteration

        return self.i
```


---

#### Exception Handling

```python
def main() -> None:
    entry: str = input("Enter Pin: ")
    pin: int = 12345

    if int(entry) == pin:
        print("correct pin")
    else:
        print("incorrect pin")


if __name__ == "__main__":
    try:
        main()
    except ValueError:
        print("error: pin cannon contain non-numeric characters")
    except KeyboardInterrupt:
        print("ctrl+c: closing program...")
    except Exception as err:
        print("error: ", err)
```


---

#### File Handling

```python
def main() -> None:
    path: str = "./sample.txt"


    # use context manager: file will be automatically closed 
    with open(path, "r") as file:
        # read entire content into memory
        content: str = file.read()
        print(content)
```


##### File modes
| Operator | Description |  
| -------: | :------ |  
| `r` | Read-only |  
| `w` | Write mode. If the file doesn’t exist, create it. If the file already exists, **overwrite** it |
| `a` | Append mode, write to the end of the file. Never overwrite. |
| `r+` | Open file in read and write mode |
| `t` | Text mode |
| `b` | Binary mode |


```python
# read file, line-by-line
def main() -> None:
    path: str = "./sample.txt"

    with open(path, "r") as file:
        for line in file:
            print(line)
```

```python
# reading files in chunks
def main() -> None:
    path: str = "./sample.txt"
    chunk_size: int = 64

    with open(path, "r") as file:
        content: str = file.read(chunk_size)

        while len(content) > 0:
            print(content)
            content = file.read(chunk_size)
```


##### Writing to files
```python
def main() -> None:
    path: str = "./sample.txt"

    with open(path, "w") as file:
        file.write("This is line one\n")
        file.write("This is line two\n")
```

```python
# copy binary files
def main() -> None:
    input_file_path: str = "./input.jpg"
    output_file_path: str = "./output.jpg"

    with open(input_file_path, "rb") as read_file:
        with open(output_file_path, "wb") as write_file:
            for line in read_file:
                write_file.write(line)
```


---

#### Context Managers
Context managers help manage resources effectively. Even in case of errors, they ensure that the resource is disconnected properly.

##### Define using Classes
```python
class open_file:
    def __init__(self, filename, mode):
        self.filename = filename
        self.mode = mode

    # context setUp
    def __enter__(self):
        self.file = open(self.filename, self.mode)
        return self.file

    # context tearDown
    def __exit__(self, exc_type, exc_val, traceback):
        self.file.close()


def main() -> None:
    # using the context manager
    with open_file("./sample.txt", "a") as file:
        file.write("Sample text\n")
```


##### Define using Decorators (recommended)
```python
from contextlib import contextmanager


@contextmanager
def open_file(filename: str, mode: str):
    try:
        # init
        file = open(filename, mode)
        # enter i.e. setUp
        yield file

    finally:
        # exit i.e. tearDown
        file.close()


def main() -> None:
    with open_file("./sample.txt", "a") as file:
        file.write("Some sample text\n")
```


---

#### Environment variables
```python
import os


def main() -> None:
    # read an environment variable
    home: str | None = os.getenv("HOME")
    print(home)

    # list all env variables, environ is dict[str, str]
    for k, v in os.environ.items():
        print(k, v)
```

**Note**: For loading `.env` files, please look at the package `dotenv`.


---

#### Filesystem

```python
import os
from os import path

# get current directory
pwd: str = os.getcwd()

# create path
current_path: str = path.join(pwd, ".gitignore")

# change current directory
new_path: str = path.join(pwd, ".git")
os.chdir(new_path)

# list all items in directory
content: list[str] = os.listdir()

# get basename (i.e. filename) from path
filename: str = path.basename(current_path)

# get directory name from path
directory: str = path.dirname(current_path)

# check if path exists
path_exits: bool = path.exists(current_path)

# check if path is file
is_path_file: bool = path.isfile(current_path)

# check if path is a directory
is_path_dir: bool = path.isdir(current_path)

# create a new folder
os.mkdir("sample")

# create a folder few levels deep
os.makedirs("./New/Folder/NEW")

# remove a directory
os.rmdir("New Folder")

# remove directories few levels deep
os.removedirs("./New/Folder/NEW")

# rename files and Folders
os.rename("NEW", "New-Folder")
```


---

#### JSON

| Method | Description |  
| -------: | :------ |  
| `json.loads(var)` | Load string as JSON |  
| `json.dumps(var)` | Encode and return JSON string |
| `json.load(file_obj)` | Read JSON file from file. Open file nees to be provided |
| `json.dump(data_obj, file_obj)` | Write JSON to provided file |


---

#### Random
```python
import random

# random number between 0 and 1
float_num: float = random.random()

# random float between provided range, end is non-inclusive
float_num = random.uniform(10, 20)

# random int, end is non-inclusive
int_num: int = random.randint(10, 20)

# pick a random value from list
choices: list[str] = ["Pakistan", "China", "Canada"]
random_choice: str = random.choice(choices)

# random shuffle elements in list, updates original list
even_nums: list[int] = [n for n in range(10, 30) if n % 2 == 0]
random.shuffle(even_nums)

# grab random sample from a list, k is number of items to grab
sample_items: list[int] = random.sample(even_nums, k=3)
```


---

#### Dates

```python
import datetime

# create date instance
future_date = datetime.date(2023, 4, 21)

# get current date
today = datetime.date.today()

# get components of date
print("%s, %s, %s" % (today.year, today.month, today.day))

# get date after n days
week_delta = datetime.timedelta(days=7)

# date next week
next_week = today + week_delta
```


##### Track time of execution
```python
from typing import Callable
import datetime


# track execution time decorator
def time_execution(func: Callable[[], None]) -> Callable[[], None]:
    def wrapper() -> None:
        timer_start = datetime.datetime.now()
        func()
        timer_end = datetime.datetime.now()
        elapsed = timer_end - timer_start
        print("elapsed: %s ms" % (elapsed.microseconds, ))

    return wrapper


@time_execution
def slow_task() -> None:
    for i in range(1, 1000000):
        pass


def main() -> None:
    slow_task()
```


##### Time
```python
time = datetime.time(22, 10, 50, 1000 )	# hours, minutes, seconds, milliseconds
print(time)
# output: 22:10:50.001000

# print current time
time = datetime.datetime.now()
print(f"{time: %H:%M:%S}")
```


##### Date-time
```python
time = datetime.datetime(2016, 9, 13, 22, 10, 50, 1000 )	
# year, month, date, hour, minutes, seconds, milliseconds
print(time)
print(time.date())		# 2016-09-13
print(time.time())		# 22:10:50.001000
```


---

#### Parse Arguments
```python
import argparse
from dataclasses import dataclass


@dataclass
class Args:
    name: str
    year: int


def main(args: Args) -> None:
    print(f"Hello {args.name}, you were born in {args.year}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Program description")
    parser.add_argument("-n", "--name", type=str, help="username", default="User")
    parser.add_argument("-y", "--year", type=int, help="year of birth")

    parsed = parser.parse_args()
    args = Args(parsed.name, parsed.year)
    main(args)
```
