#### Greet user

```ex
defmodule Sandbox do
  def main do
    IO.gets("Please enter your name: ")
    |> String.trim()
    |> greet
    |> IO.puts()
  end

  defp greet(name), do: "Hello, #{name}!"
end
```


#### Fizz-buzz

```ex
defmodule Fizzbuzz do
  def action(n) when rem(n, 15) == 0, do: "#{n} Fizzbuzzz"
  def action(n) when rem(n, 3) == 0, do: "#{n} Fizz"
  def action(n) when rem(n, 5) == 0, do: "#{n} Buzz"
  def action(n), do: "#{n}"
end

defmodule Sandbox do
  def main do
    Enum.map(0..100, &Fizzbuzz.action/1)
    |> Enum.each(&IO.puts/1)
  end
end
```


#### Print table of numbers

```ex
defmodule Table do
  defp square(n), do: n * n
  defp cube(n), do: :math.pow(n, 3)
  defp calculate_output(n), do: %{n: n, square: square(n), cube: cube(n)}
  defp format_output(%{n: n, square: square, cube: cube}), do: "#{n}\t#{square}\t#{cube}\n"
  defp format_header(), do: "n\tsquare\tcube\n"

  def format_table(range) do
    header = format_header()

    rows =
      range
      |> Enum.reverse()
      |> Enum.map(&calculate_output/1)
      |> Enum.map(&format_output/1)
      |> Enum.reduce(fn e, c -> e <> c end)

    header <> rows
  end
end

defmodule Sandbox do
  def main do
    Enum.to_list(1..10)
    |> Table.format_table()
    |> IO.puts()
  end
end
```


#### Multiple inputs from user

```ex
defmodule Operation do
  def get_inputs(n) do
    for _ <- 1..n,
        do:
          IO.gets("enter a number: ")
          |> String.trim()
          |> String.to_integer()
  end
end

defmodule Sandbox do
  def main do
    inputs = Operation.get_inputs(3)

    (Enum.sum(inputs) / length(inputs))
    |> IO.puts()
  end
end
```

#### Distance between two points

```ex
defmodule Point do
  defstruct [:x, :y]

  def distance(%{x: x1, y: y1}, %{x: x2, y: y2}) do
    x_delta_square = :math.pow(x2 - x1, 2)
    y_delta_square = :math.pow(y2 - y1, 2)
    :math.sqrt(x_delta_square + y_delta_square)
  end
end

defmodule Sandbox do
  def main do
    p_one = %Point{x: 3, y: 2}
    p_two = %Point{x: 9, y: 7}

    Point.distance(p_one, p_two) |> IO.puts
  end
end
```