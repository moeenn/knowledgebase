##### Installation
```bash
$ sudo apt-get install -y elixir erlang erlang-dialyzer
```

**Note**: Install `ElixirLS` plugin in `VSCode` for better IDE Support.


##### Hello world
```elixir
# main.ex
IO.puts "Hello world"
```

- Single quotes are not the same as double quotes
- `IO.puts` is a function and calling it with `()` will also work as expected


#### Mix
```bash
# set up a new project
$ mix new <project-name>

# start interactive shell
$ iex -S mix

# run the code
> recompile && Sandbox.hello
```



#### Helix Config

```toml
[[language]]
name = "elixir"
scope = "source.elixir"
injection-regex = "(elixir|ex)"
shebangs = ["elixir"]
roots = ["mix.exs", "mix.lock"]
comment-token = "#"
language-servers = [ "elixir-ls" ]
indent = { tab-width = 2, unit = "  " }
auto-format = true
```