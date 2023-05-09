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

| Type | Operator | Explanation |  
| -------: | :------ | :------ |  
| Arithmetic operators | `()` | Precedence 1st | 
|  | `**` | Precedence 2nd | 
|  | `% / // *` | Precedence 3rd | 
|  | `+ -` | Precedence 4th | 
| Compound operators | `+=` |  | 
|  | `-=` |  | 
|  | `*=*` |  | 
|  | `/=` |  | 
|  | `**=` | Power and equal | 
|  | `%=` | Mod and equal | 
|  | `//=` | Floor divisor and equal | 
| Logical operators | `not` | Precedence 1st | 
|  | `and` | Precedence 2nd | 
|  | `or` | Precedence 3rd | 


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


##### Fstring - String interpolation
```python
name: str = "Mr. Client"
balance: float = 3000.5

message: str = f"Hello {name}, your current balance is USD {balance:.2f}"
print(message)

# Hello Mr. Client, your current balance is USD 3000.50
```


