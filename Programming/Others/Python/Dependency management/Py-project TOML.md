
The file `pyproject.toml` can be used to list out details of the project, including the dependencies. Certain tools (e.g. `black`) also support this file and can be configured using it.

```toml
[project]
name = "sandbox"
version = "0.1.0"
dependencies = [
    "invoke",
    "ruff",
    "pyinstaller"
]
```

**Note**: One of the big disadvantages of `pyproject.toml` file is that it doesn't help with reproducible builds because we cannot pin dependency versions.


#### Installing dependencies

```bash
(virtual-env) $ pip install .
```