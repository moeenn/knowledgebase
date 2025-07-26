```bash
#!/bin/bash
echo "Hello world"
```

```bash
$ bash ./script.sh

# make the script executable
$ chmod +x ./script.sh

# run directly
$ ./script.sh
```


#### Variables
```bash
NAME="Moeen"
MESSAGE="Hello world"

echo $MESSAGE
echo "My name ${NAME}"
```

- It is a convention that all variables should be **uppercase**
- There shouldn’t be a space before or after the equals (i.e. `=`) sign when declaring variables
- Variables can be interpolated in strings. This only works in double-quote strings


#### Arrays
```bash
declare -a packages=(
  "libx11-dev"
  "libfontconfig1-dev"
  "libxft-dev"
)

# loop through the array
for pkg in ${packages[@]}; do
  echo $pkg
done

# concatenate array values
packages_str=""
for pkg in ${packages[@]}; do
  packages_str="${packages_str}${pkg} "
done

echo $packages_str
```


#### User Input

##### Interactive input
```bash
read -p "Enter name: " NAME
echo "Your name is ${NAME}"
```


##### Command-line Arguments
```bash
# print all args including script name
echo $0 $1 $2

# print all args excluding script name
echo $@
```


#### Capture output of command
```bash
NAME=$(whoami)
```


#### Control Flow
```bash
NAME="User"

if [[ $NAME == "User" ]]; then
  echo "You are ${NAME}"
elif [[ $NAME == "Admin" ]]; then
  echo "You are z -> ${NAME}"
else
  echo "You are unknown"
fi
```


##### Value Comparison
```bash
A=30
B=40

# -eq	(==)	values are equal
# -ne	(!=)	values are not equal
# -gt		first value greater than second value
# -ge		first value greater or equal to second value
# -lt		first value less than second value
# -le		first value less than or equal to second value
if [[ $A -eq $B ]]; then
  echo "values are equal"
fi
```


#### File Checks
```bash
FILENAME="example.txt"

# -e		check if exists
# -d 		check if directory 
# -f 		check if file
# -r 		check if file is readable
# -w 		check if file is writable
# -x 		check if file is executable

if [[ -e $FILENAME ]]; then
  echo "file exists"
fi
```


#### Execute Commands
```bash
update_cmd="sudo apt-get update && sudo apt-get upgrade -y"
eval $update_cmd
```


#### Function

```bash
function greet() {
  name=$1
  echo "Hello, $name!"
}

greet 'admin'
```

```bash
function combine() {
  input=$@
  result=""
  for entry in $input; do
    result+="$entry, "
  done

  echo $result
}

declare -a roles=('admin' 'customer' 'another')
combine "${roles[@]}"
```