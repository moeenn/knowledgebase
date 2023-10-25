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
is_flag = true

# symbol (i.e. atom)
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
puts nums[1..4] # access by range (end index inclusive)

# append element to array
nums.append 30
nums << 50

# check if element exists in array
puts nums.include? 30
```

```rb
# create list from range
nums = (1..10).to_a

# convert each value to string
result_one = nums.map { |n| n.to_s }

# alternative preferred syntax
result_two = nums.map(&:to_s)
```

```rb
# sum all numbers in range
puts (1..100).reduce(:+)
```


#### Hash-map

```rb
capitals = {
  'Pakistan' => 'Islamabad',
  'China' => 'Beijing',
  'Russia' => 'Moscow'
}

# using symbols (i.e. atoms) as keys
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


#### Control-flow

```ruby
marks = 80

if marks.negative?
  puts 'error: marks cannot be negative'
elseif marks > 100
  puts 'error: marks cannot be more than 100'
else
  puts "valid: #{marks}"
end
```

```ruby
marks = 80

case marks
when 80..100
  puts 'A'

when 60..79
  puts 'B'

when 40..59
  puts 'C'

else
  puts 'Failed'

end
```

```rb
def even_or_odd(num)
  (num % 2).zero? ? 'Even' : 'Odd'
end
```

```ruby
# loop n times
10.times do
  puts 'hello'
end

10.times { puts 'hello' }

# loop n times (alternative)
for n in 1..5
  puts n
end

# loop over array items
nums = [1, 2, 3, 4, 5]
for n in nums
  puts "iteration #{n}"
end

# multi-line while loop
i = 0
while i < nums.length
  puts "Looping #{nums[i]}"
  i += 1
end
```

```ruby
(1..10).each do |n|
  puts "iter: #{n}"
end

nums.each do |n|
  puts "iteration #{n}"
end

# single-line syntax
(1..10).each { |n| puts "iter: #{n}" }

# loop over hashmap keys and values
capitals.each do |key, value|
  puts "#{key} - #{value}"
end
```


#### Functions

```rb
def greet(name)
  puts "Hello, #{name}"
end

def named_argument_greet(name:)
  puts "Hello, #{name}!"
end

def main
  # parenthesis are optional
  greet 'name'

  # can only be called with named arguments 
  named_argument_greet(name: 'User')
end
```

```rb
# variadic functions
def print_values(*values)
  values.each { |value| puts value }
end

print_values(10, 20, 30, 40)
```

```rb
def surround
  puts 'BEGIN'
  yield
  puts 'END'
end

# no parenthesis needed if function doesn't take arguments
def main
  surround do
    puts 'line one'
    puts 'line two'
  end
end
```

```rb
def surround(&block)
  puts 'BEGIN'
  block.call 'some random value'
  puts 'END'
end

def main
  # single-line syntax
  surround { |value| puts value }

  surround do |value|
    puts value
  end
end
```

```rb
def main
  f = -> { puts 'Hello from simple lambda' }
  f.call

  # define and execute lambda directly
  -> { puts 'Direct execution lambda' }.call

  # pass arguments to lamda
  f = ->(n) { puts "Number: #{n}!" }
  f.call 30

  # use lambda keyword for multi-line definition
  f = lambda do
    puts 'hello from multi-line lambda'
  end
  f.call
end
```

```rb
def approach_one(pipeline, start = 10)
  value = start
  pipeline.each do |lmb|
    value = lmb.call value
  end
  value
end

def approach_two(pipeline, start = 10)
  pipeline.reduce(start) { |accum, current| current.call(accum) }
end

def main
  lambda_pipeline = [
    ->(n) { n * 10 },
    ->(n) { n / 2 },
    ->(n) { n + 5 }
  ]

  puts approach_one lambda_pipeline
  puts approach_two lambda_pipeline, 10
end
```

```rb
p = proc { |n| puts "Number: #{n}!" }
p.call 30
```

```rb
# this function will return 10
def return_from_proc
  f = proc { return 10 }
  f.call
  puts 'This will never be printed!'
end

def main
  puts return_from_proc
end
```


#### Errors

```rb
def problematic_function
  raise StandardError.new('Unexpected number provided')
end

def main
  begin
    problematic_function
  rescue StandardError => e
    puts "Error: #{e}"
  end
end
```

**Note**: There is also an `Exception` class .  Instances of `Exception` are meant to be handled.


#### Structs

```rb
User = Struct.new(:id, :email, :active)

def main
  user = User.new(10, 'admin@site.com', true)
  puts user

  # access single member
  puts user.email
  puts user['email']
  puts user[:email]

  # update property
  user.active = true
  user['active'] = true
  user[:active] = false
end
```

#### Classes

```rb
# class for storing position on cartesian plane
class Position
  attr_accessor :x, :y

  def initialize(x_pos = 0, y_pos = 0)
    @x = x_pos
    @y = y_pos
  end

  # static class method
  def self.hello
    'Hello from Position'
  end

  # entity object printable
  def to_s
    "Position(x=#{x}, y=#{y})"
  end
end

# Enumerate directions
class Direction
  UP = :UP
  DOWN = :DOWN
  LEFT = :LEFT
  RIGHT = :RIGHT
end

# class for modeling player entities
class Entity
  attr_accessor :name, :position

  # static member variable
  @@step = 10

  def initialize(name)
    @name = name
    @position = Position.new
  end

  def move(direction)
    case direction
    when Direction::UP
      position.y += @@step

    when Direction::DOWN
      position.y -= @@step

    when Direction::LEFT
      position.x -= @@step

    when Direction::RIGHT
      position.x += @@step
    end
  end

  def to_s
    "Entity(name=#{name}, position=#{position})"
  end
end

def main
  entity = Entity.new 'Entity one'
  puts entity

  entity.move Direction::RIGHT
  entity.move Direction::DOWN
  puts entity

  puts Position.hello
end
```


#### Split code into multiple files 

```
src/
	main/
		main.rb
		others/
			direction.rb
			position.rb
			entity/
				entity.rb
```

```rb
# file: main.rb
require_relative 'others/entity/entity'

def main
  entity = Entity.new 'Entity one'
  puts entity

  entity.move Direction::RIGHT
  entity.move Direction::DOWN
  puts entity

  puts Position.hello
end

main
```

```rb
# file: direction.rb

# Enumerate directions
class Direction
  UP = :UP
  DOWN = :DOWN
  LEFT = :LEFT
  RIGHT = :RIGHT
end
```

```rb
# file: position.rb

# class for storing position on cartesian plane
class Position
  attr_accessor :x, :y

  def initialize(x_pos = 0, y_pos = 0)
    @x = x_pos
    @y = y_pos
  end

  # static class method
  def self.hello
    'Hello from Position'
  end

  # entity object printable
  def to_s
    "Position(x=#{x}, y=#{y})"
  end
end
```

```rb
# file: entity.rb

require_relative '../position'
require_relative '../direction'

# class for modeling player entities
class Entity
  attr_accessor :name, :position

  # static member variable
  @@step = 10

  def initialize(name)
    @name = name
    @position = Position.new
  end

  def move(direction)
    case direction
    when Direction::UP
      position.y += @@step

    when Direction::DOWN
      position.y -= @@step

    when Direction::LEFT
      position.x -= @@step

    when Direction::RIGHT
      position.x += @@step
    end
  end

  def to_s
    "Entity(name=#{name}, position=#{position})"
  end
end
```