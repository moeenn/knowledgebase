#### Installation

```bash
$ sudo apt-get install ruby-full

# install global packages
$ gem install solargraph rake rubocop
```


#### Variables

```rb
# Integer
int_num = 300

# Float
float_num = 400.2

# String
string_var = "Hello world"

# FalseClass / TrueClass
isFlag = true

# symbol
:hello

# empty value
nil
```


#### Arrays

```rb
nums = [1,2,3,4,5,6]

puts nums.length
puts nums.first
puts nums.last

# access values
puts nums[1]
puts nums[-2]
puts nums[20] # nil
puts nums[1..4] # access by range

# append element to array
nums.append 30
nums << 50

# check if element exists in array
puts nums.include? 30
```


#### Hashmap

```rb
capitals = {
  'Pakistan' => 'Islamabad',
  'China' => 'Beijing',
  'Russia' => 'Moscow'
}

# using symbols as keys
map = {
  a: 10,
  b: 20,
  c: 30
}

# access keys and values as arrays
puts capitals.keys
puts capitals.values

# access elements
puts capitals['Pakistan']
puts map[:a]
```


#### Functions

```rb
def main(name)
  puts "Hello, #{name}"
end

main 'name'
```