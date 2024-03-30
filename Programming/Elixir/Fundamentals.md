#### Variables
```ex
# simple variable
number = 42

# constant
@myConst 300

# comparing variables
m1 = 100
m2 = 100.0

IO.inspect(m1 == m2)    # true
IO.inspect(m1 === m2)   # false
```

**Note**: Reading the value of a constant will also require the `@` symbol before the constant’s name

In Elixir, `=` operator is not the assignment operator. It is actually called Pattern matching operator. In the above example we have bound variable number with a constant value of `42`.

In order to prevent re-binding of variables, use following

```elixir
defmodule Actions do
  def meaning do
    42
  end
end

defmodule Main do
  result = 43
  ^result = Actions.meaning

  IO.puts result
end
```

The above **code will produce an error** saying that the right hand side cannot be matched against the left hand side. If we remove the pin operator from the result variable it will be bound to a new value of `42`. However, in this case the compiler will warn the value of `43` was never read.


---

#### Logical Operators & Control Flow
```elixir
@age 18
@gender :male

if @age >= 18 and @gender === :male do
  IO.puts "You may pass"
else
  IO.puts "You may not pass"
end

# You may pass
```

```elixir
@age 18
@gender :male

unless @age >= 18 and @gender === :male do
  IO.puts "You may not pass"
else
  IO.puts "You may pass"
end

# You may pass
```

```elixir
@marks 92

grade =
  cond do
    @marks < 40 -> "F"
    @marks < 60 -> "D"
    @marks < 80 -> "C"
    @marks < 90 -> "B"
    @marks <= 100 -> "A"
    true -> nil
  end

IO.inspect(grade)
# "A"
```

```elixir
defmodule Grade do
  def calc(marks) when marks < 0, do: {:error, "cannot be negative"}
  def calc(marks) when marks <= 40, do: {:ok, "F"}
  def calc(marks) when marks <= 60, do: {:ok, "C"}
  def calc(marks) when marks <= 80, do: {:ok, "B"}
  def calc(marks) when marks <= 100, do: {:ok, "A"}
  def calc(_), do: {:error, "cannot be more than 100"}
end

defmodule Sandbox do
  @marks 90

  def main do
    Grade.calc @marks
  end
end
```

Elixir doesn’t directly have the ternary operator. We can use the following

```elixir
allowed = if age > 18, do: true, else: false
```

```elixir
@input 30

case @input do
  10    -> IO.puts "You entered 10"
  20    -> IO.puts "You entered 20"
  30    -> IO.puts "You entered 30"
  _     -> IO.puts "Invalid Type"
end

# You entered 30
```


---

#### User input
```elixir
name = IO.gets("Enter your name: ") |> String.trim
IO.puts "Hello #{name}. Welcome to our website"
```


---

#### Strings
```elixir
name = "User"
IO.puts "Hello there, #{name}"

greeting = "Hello there, "
welcome = "Welcome to our website"

# string concatenation
message = greeting <> welcome

# Find out length of a string
String.length()

# Change case to upper
String.upcase()

# Change case to lower
String.downcase()

# Convert string to Array of characters
String.graphemes()

# Repeat a string n number of times
String.duplicate(string, times)

# Get character at a specific index
String.at(string, index)

# Check if a string ends with another string / values in a List
String.ends_with?(string, match)
String.ends_with?(string, [match1, match2])

# Strip whitespace from start and end of a String
String.trim(string)

# Replace all matches within a String
String.replace(string, with, what)

# Split a string into a List
String.split(string, delimiter)

# Reverse a String
String.reverse(string)

# Atoms can also be converted into Strings
Atom.to_string(:HelloWorld)

# Join a list into a String
Enum.join(["My", "name", "is", "Admin"], " ")
```


---

#### Lists

```elixir
# Get first item in a List
List.first(list)

# Get last item in a List
List.last(list)

# Get length of a List
length(list)

# Generate a List in range (bounds inclusive)
Enum.to_list(0..10)


# concatenate lists
numbers = Enum.to_list(1..10)
alphas = ["a", "b"]
results = numbers ++ alphas


# check Element Exists in List
nums = [1, 2, 3, 4, 5]
IO.puts(2 in nums)
# true


# loop over list
nums = [1, 2, 3, 4, 5]
Enum.each nums, fn element -> IO.puts(element) end


# insert at start of list
numbers = [1, 2, 3, 4, 5, 6, 7, 8]
prepend = [0 | numbers]
# [0, 1, 2, 3, 4, 5, 6, 7, 8]


# filter a list
numbers = Enum.to_list(1..8)
results = Enum.filter(numbers, fn n -> rem(n, 2) == 0 end)
IO.inspect(results)
# [2, 4, 6, 8]


# list comprehensions
numbers = Enum.to_list(1..10)
results = for n <- numbers, do: n * n
# [1, 4, 9, 16, 25, 36, 49, 64, 81, 100]


# generate list of tuples
numbers = for x <- 0..3, y <- 0..3, do: {x, y, x + y}
```


##### Lists example
```elixir
defmodule Task do
  def new(id, body) do
    %{id: id, body: body}
  end

  def update(task, new_body) do
    Map.merge(task, %{ body: new_body })
  end
end

defmodule TaskList do
  def new() do
    []
  end

  def add_task(task_list, id, body) do
    task = Task.new(id, body)
    [task | task_list]
  end

  def update_task(task_list, id, new_body) do
    updater = fn t -> if t.id == id, do: Task.update(t, new_body), else: t end
    Enum.map task_list, updater
  end

  def delete_task(task_list, id) do
    Enum.filter task_list, fn t -> t.id != id end
  end
end

defmodule Sandbox do
  def main do
    task_list = TaskList.new
      |> TaskList.add_task(1, "Buy Groceries")
      |> TaskList.add_task(2, "Conquer Earth")

    TaskList.update_task(task_list, 2, "Invade Mars")
     |> TaskList.delete_task(1)
  end
end

# [%{body: "Invade Mars", id: 2}]
```


---

#### Tuples
Tuple are different from Lists because tuples are not supposed to be iterable

```elixir
point = {12, 10}

IO.puts "Is Tuple: #{is_tuple(point)}"    # true

point = Tuple.append(point, 15)
IO.inspect point                          # {12, 10, 15}

z = elem(point, 2)
IO.puts "Z Coordinate: #{z}"              # 15

size = tuple_size(point)
IO.puts "Size: #{size}"                   # 3

point = Tuple.delete_at(point, 2)
IO.inspect point                          # {12, 10}

{x, y} = point
IO.puts "x: #{x}, y: #{y}"                # x: 12, y: 10
```


---

#### Maps
```elixir
defmodule Sandbox do
  def main do
    map_one = %{ hello: "world" }
    map_two = %{ :hello => "world" }
    IO.puts map_one.hello == map_two.hello

    map_three = %{ "hello" => "world" }
    IO.puts map_three["hello"]
  end
end
```


---

#### Structs
```elixir
defmodule Task do
  defstruct id: nil, body: nil, done: false

  def new(id, body) do
    %Task{id: id, body: body}
  end

  def mark_done(%Task{id: id, body: body}) do
    %Task{id: id, body: body, done: true}
  end
end

defmodule Sandbox do
  def main do
    f = Task.new(1, "Buy Groceries")
    Task.mark_done f

    # destructuring values
    %Task{id: id} = f
  end
end
```


---

#### Functions
```elixir
def double(list) do
  Enum.map(list, fn x -> x * 2 end)
end
```

Anonymous Functions

```elixir
task = fn a, b -> a * b end
result = task.(30,10)
```

If an anonymous function doesn’t take any arguments, we can skip that part.

```elixir
task = fn -> IO.puts "This is a function call" end
task.()
```

Higher-order functions

```elixir
defmodule Learning do
  def square(n) do
    n * n
  end
end

list = [1,2,3,4,5,6,7,8,9,10]
result = Enum.map(list, &Learning.square/1)

result_2 = Enum.map(list, fn n -> n * n end)
IO.inspect result_2

# [1, 4, 9, 16, 25, 36, 49, 64, 81, 100]
```

**Note**: In the above example `/1` is the **Arity** of the Function i.e. Number of arguments the function accepts.


##### Function Guards
```elixir
defmodule Actions do
  def test(n) when is_number(n) and n < 0 do
    :negative
  end

  def test(0), do: :zero

  def test(n) when is_number(n) and n > 0 do
    :positive
  end
  # catch all cases
  def test(any) do
    {:error, "Unhandled exception: #{any}"}
  end
end

defmodule Main do
  IO.puts Actions.test 200
  IO.puts Actions.test 0
  IO.puts Actions.test -30
  IO.inspect Actions.test "a"
end
```

Alternatively, the test function can also be written as a lambda function

```elixir
defmodule Actions do
  test = fn
    n when is_number(n) and n < 0 ->
      :negative

    0 ->
      :zero

    n when is_number(n) and n > 0 ->
      :positive

    any ->
      {:error, "Unhandled exception: #{any}"}
  end
end
```

```elixir
defmodule Fizzbuzz do
  def run(n) when rem(n, 15) == 0, do: "#{n} fizzbuzz"
  def run(n) when rem(n, 5) == 0, do: "#{n} buzz"
  def run(n) when rem(n, 3) == 0, do: "#{n} fizz"
  def run(n), do: n
end

defmodule App do
  def main do
    action = fn n -> IO.puts Fizzbuzz.run(n) end
    Enum.each(0..100, action)
  end
end
```


---

#### Recursion
```elixir
defmodule Learning do
  def sum([]) do
    0
  end

  def sum([head | tail]) do
    head + sum(tail)
  end
end

sum = Learning.sum([1,2,3,4,5,6,7,8,9,10])
IO.puts sum  # 55
```


---

#### Pattern Matching
```elixir
defmodule Learning do
  def life do
    {:ok, 42}
  end
end

defmodule Main do
  {:ok, meaning} = Learning.life
  IO.puts meaning
end
```

Expression on the right is matched to the variables on the left. In the above case, it is being used to return multiple values from a function and assign them to two variables in the Main module.

```elixir
defmodule Actions do
  def time do
    :calendar.local_time()
  end
end

defmodule Main do
  {_, {hours, minutes, _}} = Actions.time
  IO.inspect {hours, minutes}
end
```

We can also throw away values that we don’t need. `Actions.time/0` returns two tuples one related to date, second related to time. 


##### Pattern Matching on Lists
```elixir
defmodule Main do
  [head | _] = Enum.sort [5,4,3,2,1]
  IO.inspect head
end
```

The above program will output 1. We have thrown away the tail of the list i.e. all the other elements.


##### Pattern Matching Maps

```elixir
defmodule Main do
  person = %{
    name: "User",
    age: 28,
  }

  %{age: age} = person

  IO.inspect age
end
```

In the above program we have extracted a single property from a map.` age` is a `string` variable and not a map itself.


##### Pattern Matching in Function Arguments
```elixir
defmodule Actions do
  @pi 3.142

  def area({:rect, height, width}) do
    height * width
  end

  def area({:triangle, base, height}) do
    base * height |> div(2)
  end

  def area({:circle, r}) do
    @pi * r * r
  end
end

defmodule Main do
  rect = {:rect, 10, 20}
  area = Actions.area rect
  IO.puts "Square: #{area}"

  triangle = {:triangle, 20, 30}
  area = Actions.area triangle
  IO.puts "Triangle: #{area}"

  circle = {:circle, 10}
  area = Actions.area circle
  IO.puts "Circle: #{area}"
end
```

**Note**: Elixir allows function overloading provided that the arguments to the function variations are different.


##### Order of Pattern Matching in Overloaded Functions
```elixir
defmodule Actions do
  def max(a, b) when a >= b, do: a
  def max(_a, b), do: b
end

defmodule Main do
  IO.puts Actions.max 200, 300
end
```

**Note**: In the second declaration of the `Actions.max/2` function, variable a is unused. Therefore, we prefix it with an `underscore`.

When we call `Actions.max/2` Elixir will match functions in the order they are declared. So be careful to **put the catch-all case at the very end**.


---

#### Idiomatic error handling 

```ex
defmodule Operation do
  def calculate(n) when rem(n, 2) == 0, do: {:ok, n * 10}
  def calculate(n) when rem(n, 2) == 1, do: {:error, :no_odd_nums}
end

defmodule Sandbox do
  def main do
    case Operation.calculate(11) do
      {:ok, result} -> IO.puts("success: #{result}")
      {:error, reason} -> IO.puts("error: #{reason}")
    end
  end
end
```

In the above example, we return an error tuple when an odd number is provided as input. The second value in the tuple is the reason for error. It could have been a string, but **it is conventional to provide an atom as reason for error**.


---

#### Modules
```elixir
defmodule Learning do
  def hello do
    IO.puts "Hello world"
  end
end

Learning.hello()
```

##### Private Functions
```elixir
defmodule Actions do
  def public_action do
    IO.puts "Called public function"
    private_action()
  end

  defp private_action do
    IO.puts "Called private function"
  end
end

defmodule Main do
  Actions.public_action()
end
```


---

#### Comprehensive Example
```elixir
defmodule Form do
  defp extract_login(%{login: login}), do: {:ok, login}
  defp extract_login(_), do: {:error, "Login field not found"}

  defp extract_pwd(%{pwd: pwd}), do: {:ok, pwd}
  defp extract_pwd(_), do: {:error, "Password field not found"}

  defp extract_email(%{email: email}), do: {:ok, email}
  defp extract_email(_), do: {:error, "Email field not found"}

  def extract_data(data) when is_map(data) do
    with {:ok, login} <- extract_login(data),
         {:ok, pwd}   <- extract_pwd(data),
         {:ok, email} <- extract_email(data) do
         {:ok, %{login: login, pwd: pwd, email: email}}
    end
  end
end

defmodule Main do
  data = %{
    login: "moeen",
    pwd: "q1w2e3r4",
    email: "moeen@site.com",
  }

  with {:ok, result} <- Form.extract_data(data) do
    IO.inspect result
  end

  with {:error, why} <- Form.extract_data(data) do
    IO.puts why
  end
end
```

