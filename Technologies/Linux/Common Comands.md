
#### File and folder

```bash
# make nested directories
$ mkdir -p /some/nested/path

# get size of a folder or folder.
$ du -hs /path/to/folder
```


---

#### Find files and folders

```bash
# find by name.
$ find /path/to/directory -name '*node-project*'

# find by name ignoring case.
$ find /path/to/directory -iname '*node-project*'

# find files over 1 MB in size. (k = KB, M = Mb, G = Gb)
$ find /folder -type f -size +1M

# find in directory and sub-directory
$ find /path/to/directory -iname '*.jpg' -ls

# find directories only.
$ find ~/Public/ -type d

# find a path.
$ find / -type d -name 'img' -ipath "*public_html/example.com*"
```


---


#### Archives

```bash
# compress multiple files.
$ zip archive.zip file1.txt file2.txt

# compress folder will all content.
$ zip -r archive.zip /path/to/folder

# unzip archive.
$ unzip archive.zip -d /output/directory
```

```bash
# compress directory using tar.
$ tar -czvf archive_name.tar.gz directory_name/

# uncompress tar.gz archive.
$ tar -xzvf archive_name.tar.gz
```


---

#### Processes

```bash
# find process by program name.
$ px aux | grep <program-name>

# find process using an system port.
$ lsof -i :<port>

# kill a process using PID.
$ kill -9 <pid>
```


---

#### IP 

```bash
# find network interface names.
$ ip link show | grep -E '.: '

# find local IP address
$ ip addr | grep '<interface-name>'
```



#### Linux commands cheat-sheet

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

