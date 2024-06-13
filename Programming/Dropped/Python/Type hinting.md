
```bash
# installation
$ pip3 install mypy

# check types for a file
$ mypy ./main.py
```

#### Configuration
Global `mypy` config is stored in `~/.config/mypy/config`. Project-specific `mypy` config can be stored in the project directory with the name `setup.cfg`.

```toml
[mypy]
disallow_untyped_defs = True
disallow_any_unimported = True
no_implicit_optional = True
check_untyped_defs = True
warn_return_any = True
warn_unused_ignores = True
show_error_codes = True
ignore_missing_imports = True
```
