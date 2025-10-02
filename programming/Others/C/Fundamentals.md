### Conventions
- Types are named in snake case with following suffixes:
  - `_t` for structs.
  - `_e` for enums.
  - `_u` for unions.
- Enum values are generally upper case.
- Use `calloc` instead of `malloc` because it zeros out the allocated memory.
- Print errors using `fprintf`.