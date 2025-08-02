
```bash
# show file permissions.
$ ls -l /path/to/file
```

Permissions will look something like this

```
drwxrwxr-x
```

This can be split into four sections.

```
d        rwx       rwx         r-x
|         |         |           |
Type    Owner     Group     Other Users
```

**Type**: `d` means directory. In case of file, it will be `-`

|     | Meaning | Binary Reference |
| --- | ------- | ---------------- |
| `r` | Read    | `4`              |
| `w` | Write   | `2`              |
| `x` | Execute | `1`              |

#### Settings Permissions

```bash
# update file permissions.
$ chmod 640 /path/to/file
```

`6` = `4+2` (i.e. Read+Write) - Owner
`4` = `4` (i.e. Read only) - Group
`0` = No permissions - Other users.


#### Gain full access to directory

```bash
$ sudo chmod -R a+rq /path/to/file/or/directory
```
