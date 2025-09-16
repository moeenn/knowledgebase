
```bash
# create a new project (will create new directory).
$ mix new <project-name>

# install dependencies.
$ mix deps.get

# clean all dependencies.
$ mix deps.clean --all

# compile project.
$ mix compile
```


---

#### Basic program

Ensure the following is present in the `mix.exs` file.

```elixir
  def application do
    [
      mod: {App, []}
    ]
  end
```

```elixir
defmodule App do
  use Application

  def start(_type, _args) do
    IO.puts("Hello world")
    ok()
  end

  defp ok(), do: {:ok, self()}
end
```

```bash
$ mix run
```


---

#### More involved example

```elixir
defmodule User do
  @type user_role :: :admin | :employee
  @type t :: %__MODULE__{id: integer, email: String.t(), role: user_role}
  defstruct [:id, :email, :role]

  @spec new(integer, String.t(), user_role) :: t
  def new(id, email, role),
    do: %User{
      id: id,
      email: email,
      role: role
    }
end

defmodule User.Repo do
  @type t :: %__MODULE__{users: [User.t()]}
  defstruct [:users]

  @spec new() :: t
  def new(),
    do: %User.Repo{
      users: []
    }

  @spec add_user(t, User.t()) :: t
  def add_user(repo, user) do
    %User.Repo{
      users: repo.users ++ [user]
    }
  end

  @spec update_single_user(User.t(), User.t()) :: User.t()
  defp update_single_user(old, new) do
    if old.id == new.id,
      do: Map.merge(old, new),
      else: old
  end

  @spec update_user(t, User.t()) :: t
  def update_user(repo, user) do
    %User.Repo{
      users: Enum.map(repo.users, fn u -> update_single_user(u, user) end)
    }
  end

  @spec remove_user(t, integer) :: t
  def remove_user(repo, user_id) do
    %User.Repo{
      users: Enum.filter(repo.users, fn user -> user.id != user_id end)
    }
  end
end

defmodule App do
  use Application

  def start(_type, _args) do
    repo =
      User.Repo.new()
      |> User.Repo.add_user(User.new(10, "admin@site.com", :admin))
      |> User.Repo.add_user(User.new(20, "one@site.com", :employee))
      |> User.Repo.add_user(User.new(30, "two@site.com", :employee))
      |> User.Repo.remove_user(20)
      |> User.Repo.update_user(User.new(10, "adminx@site.com", :admin))

    IO.inspect(repo)
    ok()
  end

  defp ok(), do: {:ok, self()}
end
```


---

#### Message passing

```elixir
defmodule Calculator do
  @spec start() :: pid
  def start(), do: spawn(&loop/0)

  def loop do
    receive do
      {:add, pid, a, b} -> send(pid, {:add, add(a, b)})
      {:sub, pid, a, b} -> send(pid, {:sub, sub(a, b)})
    end

    # revursively call self, to continue waiting for the next message.
    loop()
  end

  @spec add(integer, integer) :: integer
  defp add(a, b), do: a + b

  @spec sub(integer, integer) :: integer
  defp sub(a, b), do: a - b
end

defmodule App do
  use Application

  def loop() do
    # receiving on pid blocks.
    receive do
      {:add, result} -> IO.puts("Add: #{result}")
      {:sub, result} -> IO.puts("Sub: #{result}")
    end

	# call self to continue waiting for next message.
    loop()
  end

  def start(_type, _args) do
    pid = Calculator.start()
    self_pid = self()

    # sending on pid does not block.
    send(pid, {:add, self_pid, 10, 20})
    send(pid, {:sub, self_pid, 50, 10})

    # this will block because of receive.
    loop()
    
    # process will never exit.
  end
end
```

```elixir
defmodule Calculator do
  @spec start() :: pid
  def start(), do: spawn(&register/0)

  def register() do
    # give a name to the pid of spawned process. Messages can be sent using
    # `send` using this atom instead of the PID.
    Process.register(self(), :calculator)
    loop()
  end

  def loop do
    receive do
      {:add, pid, a, b} -> send(pid, {:add, a + b})
      {:sub, pid, a, b} -> send(pid, {:sub, a - b})
    end

    # recursively call self, to continue waiting for the next message.
    loop()
  end

  @spec add(pid, integer, integer) :: pid
  def add(pid, a, b) do
    send(:calculator, {:add, pid, a, b})
  end

  @spec sub(pid, integer, integer) :: integer
  def sub(pid, a, b) do
    send(:calculator, {:sub, pid, a, b})
  end
end

defmodule App do
  use Application

  def loop() do
    # receiving on pid blocks.
    receive do
      {:add, result} ->
        IO.puts("Add: #{result}")
        loop()

      {:sub, result} ->
        IO.puts("Sub: #{result}")
        loop()

      {:exit} ->
        IO.puts("-- exiting --")
    end
  end

  def start(_type, _args) do
    Calculator.start()
    self_pid = self()

    # don't send messages from the process where results will be received.    
    spawn(fn ->
      # self() will be different here from self_pid.
      Enum.each(0..10, fn i ->
        Process.sleep(500)
        Calculator.add(self_pid, 10 * i, 20)
      end)

      send(self_pid, {:exit})
    end)

    loop()
    {:ok, self()}
  end
end
```