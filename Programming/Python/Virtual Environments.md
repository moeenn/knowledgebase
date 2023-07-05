The Python package manager (PIP) installs packages from `PyPI`. The packages can change over time and scripts written using older versions of the third-party packages may not work any more. 

The above problem can be easily solved if we installed the third-party packages directly in the project folder (instead of a system-wide installation). This is precisely the purpose of a virtual environment. It isolates the project dependencies from the rest of the system by installing them directly in the project folder.

```bash
# installation
$ pip3 install venv


# setting up virtual env in current folder
$ python -m venv ./


# activate the environment
$ . ./bin/activate


# deactivate environment
$ deactivate
```


#### Note on Git
Inside your project folder you will notice that `venv` creates directories containing PIP dependencies and Library executable. For security reasons these should never be pushed to the project’s Git Repository.

It is highly advisable to create the following `.gitignore` file at the root of your project folder.

```
bin/
lib/
include/
lib64/
share/
__pycache__/
*.pyc
*/*.pyc
pyvenv.cfg
```
