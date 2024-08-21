#### Todo
- [ ] cURL
- [ ] AWK
- [ ] Sed
- [ ] Grep
- [ ] Vim


#### Linux commands cheat-sheet

```bash
# check size of a file (-h means human-readable)
$ du -h /path/to/file
```

```bash
# kill a program
$ killall -v --ignore-case
```

```bash
# gain full access to a file or directory
$ sudo chmod -R a+rq /path/to/file/or/directory
```

```bash
# create a zip file
$ zip -r <zip_name.zip> -x folder/sub_folder/**\* -x folder/another_folder/**\*
```

```bash
# connect to remote server using ssh key
$ ssh -i <ssh_key.pem> <username>@<host>
```

```bash
# copy file to local machine through SSH
$ scp -i <ssh_key.pem> -P <port> <username>@<ip_address>:/path/to/file ./<local_directory>
```

```bash
# obfuscate a file (currupt without delete)
$ shred <file>
```

```bash
# add new user to the system
# without password
$ sudo useradd <username>

# with password
$ sudo adduser <username>
```

```bash
# act as another user
$ su <username>
```

```bash
# set password for a user
$ sudo passwd <username>
```

```bash
# get quick description of a program
$ whatis <program_name>
```

```bash
# find where a program is (in $PATH)
$ whereis <program_name>
# Or
$ which <program_name>
```

```bash
# quickly view file
# start of file
$ head <file>

# end of file 
$ tail <file>

# one page at a time
$ less <file>
```

```bash
# preview difference between two files
$ diff <file_one> <file_two>
```

```bash
# find files
# find by name
$ find <dir> -name <pattern>

# find files
$ find <dir> -type f -name <pattern>
```

```bash
# get local IP (package: net-tools)
$ ifconfig 
# Or
$ ip address
```

