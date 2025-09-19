
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
end

defmodule App do
  use Application

  def start(_type, _args) do
    repo =
      User.Repo.new()
      |> User.Repo.add_user(User.new(10, "admin@site.com", :admin))
      |> User.Repo.add_user(User.new(20, "one@site.com", :employee))
      |> User.Repo.add_user(User.new(30, "two@site.com", :employee))

    IO.inspect(repo)
    ok()
  end

  defp ok(), do: {:ok, self()}
end
```