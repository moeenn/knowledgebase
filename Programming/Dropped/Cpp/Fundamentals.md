```bash
$ sudo apt-get install bear clang clang-format clangd 
```


#### How does C++ Work
###### Preprocessing
Preprocessing is used for gathering the resources that are required for our code to run e.g. standard language libraries. All statements in our C++ code that start with pound symbol (i.e. #) are not C++ instructions. They are meant for the preprocessor and are called Preprocessor Directives. E.g.


###### Object Files
After the preprocessing is done. The code is converted into Object files. For every Translation unit a new object file is created. This object file contains binary instructions. If we need to view the exact content of this binary data, we can convert the object file into `ASM` file (i.e. Assembly File). 

Translation Units:  A translation unit is the basic unit of compilation. Generally, a `cpp` file and its header form a single translation unit. But if we include multiple `cpp` files inside a main `cpp` file, they will form a single translation unit.

###### Linking
During the compilation stage several object files may have been created. The linker combines these object files into a single executable file. 

The compiler can be fooled using the function prototypes. E.g. 
- If we call a function Log inside our entry point and don’t actually define this function, we will hit a compilation error
- If we call the Log function and specify a phony function prototype, the code will compile into object files and we will not hit any errors
- When we run the linker for linking the compiled object files, the linker will hit an Unresolved External Symbol or undefined (g++) error because the function declaration of the Log function was not found in any of the object files.

**Note**: If we have multiple functions with the same signature (i.e. prototype) defined in different Translation units, we will hit a linking error because now our symbol (i.e. function) is ambiguous: The linker doesn’t know which function to link to which symbol.

**Note**: Linking done at compile-time is also called Early Binding or Compile-Time Binding.


---

#### Hello world
```cpp
#include <iostream>

int main() {
  std::cout << "Hello World\n";
}
```

Tip: By default boolean are printed to the console as either 1 (true) or 0 (false). We can also get it print true or false to console


#### Printing tips
```cpp
// print out bool as True or False
std::cout << std::boolalpha << is_even << '\n';
```

```cpp
#include <iomanip>
…

// set precision for floating point numbers
std::cout << std::fixed << std::showpoint << std::setprecision(2);
std::cout << "Your average scores are " << avg << '\n';
```

---

#### Strings

##### Raw strings
```cpp
const char* message = R"(this is line 1
this is line 2
this is line 3)";
```

##### String functions
```cpp
#include <cstring>

int main() {
  const char *msg_1{"This is a message"};
  char msg_2[]{"This is another message"};
  std::string msg_3{"This is a modern message"};

  std::cout << "Length: " << std::strlen(msg_1) << '\n'
            << "Length: " << std::strlen(msg_2) << '\n'
            << "Length: " << msg_3.length() << '\n';
}
```

```cpp
#include <iostream>
#include <string>

bool palindrome(const std::string &message);

int main() {
  const std::string message{"naman"};
  const bool is_palindrom{palindrome(message)};
  std::cout << std::boolalpha << message << '\t' 
            << is_palindrom << '\n';
}

bool palindrome(const std::string &message) {
  const uint size = message.size() - 1;

  for (int i = 0; i <= size; i++) {
    if (message.at(i) != message.at(size - i))
      return false;
  }

  return true;
}
```

```cpp
#include <iostream>

int main() {
  const std::string msg1{"hello"};

  // string comparison
  if(msg1.compare("hello") == 0)
    std::cout << "[Match]";
}

// [Match]
```

```cpp
#include <algorithm>

int main() {
  const std::string input{"example};

  // create copy using copy constructor
  std::string copy{input};
  
  // reverse
  std::reverse(copy.begin(), copy.end());
}
```

```cpp
int main() {
  std::string str_1 = input("string 1: ");
  for(auto i = 0; i < str_1.size(); i++) {
	// random access
	std::cout << str_1.at(i) << "\t";
  }
}
```

```cpp
int main() {
  std::string msg{"I'm son of Earth and Fiery Heavens\n"};

  // find substring
  std::cout << ((msg.find("Heavens") != std::string::npos)
                  ? "[Match Found] \n"
                  : "[Match Not Found] \n");
}
```

**Note**: If sub-string is not found, `find()` method will return the value `std::ios::npos`.

```cpp
#include <cstring>

int main() {
  const std::string msg{"This is a message"};

  // convert std::string to c string
  const uint length{ strlen(msg.c_str()) };
  print(length);
}
```


##### String Optimizations through String Views
```cpp
#include <iostream>
#include <string>

/* track every call to the new operator */
void *operator new(size_t size) {
  static uint s_alloc = 0;
  std::cout << ++s_alloc << " allocations\n";
  return malloc(size);
}

/* borrow only, don't make a copy */
void print_str(const std::string &str) { std::cout << str << "\n"; }

int main() {
  /* first allocation */
  std::string msg{"some_random_word word_count_word_word"};

  /* two more heap allocations */
  std::string first = msg.substr(0, 16);
  std::string second = msg.substr(17, 30);

  print_str(first);
  print_str(second);
}
```

```cpp
/* borrow only, don't make a copy */
void print_str(const std::string_view &str) { std::cout << str << "\n"; }

int main() {
  const char* msg{"some_random_word word_count_word_word"};

  /**
   *  get a read-only view into a const char*
   *  if msg was a std::string we'd use the following 
   *  std::string_view first{msg.c_str(), 16}; 
   */
  std::string_view first{msg, 16};
  std::string_view second{msg + 17, 15};

  print_str(first);
  print_str(second);

  /* no allocations in this case */
}
```


---

#### Bit-wise operators
```cpp
#include <iostream>

int main() {
  for (const uint &i : {1, 2, 3, 4, 5}) {
    std::cout << (3 << i) << '\t';
  }
}
// 3    6    12    24    48
```

In the code above the expression `3 << i` is interesting. It simply means `3 * pow(2, i)`
Similarly, if we had the expression `48 >> i` it would mean `3 / pow(2, i)`.


---

#### Const
```cpp
// value of MAX_AGE cannot be changed
const uint MAX_AGE = 90;
```

Making the de-referenced value of pointer constant

```cpp
const int* current = new int(2);

// this is not allowed
*current = 30;

// this is fine
current = &some_int_variable;
```

Making the pointer constant

```cpp
int* const current = new int(2);

// this is fine
*current = 30;

// this is not allowed
current = &some_int_variable;
```

Making the pointer and de-referenced value constant

```cpp
const int* const current = new int(2);

// this is not allowed
*current = 30;

// this is not allowed
current = &MAX_AGE;
```

Defining Class Getter (i.e. constant) Methods

```cpp
class Entity {
private:
  int m_x, m_y;
  std::string *m_name;

public:
  Entity(int x, int y): m_x(x), m_y(y) {
    *m_name = std::string("Entity");
  }

  /**
   *  getter method, cannot modify class properties in any way
   */
  std::tuple<int, int> position() const {
    return std::make_tuple(m_x, m_y);
  }

  /**
   *  the returned pointer is constant
   *  the dereferenced value of pointer is constant
   *  the method is a getter i.e. constant
   */
  const std::string* const get_name() const {
    return m_name;
  }
};
```


---

#### Control-flow
```cpp
const bool flag_1{true};
const bool flag_2{false};

std::cout << ((flag_1 && flag_2) 
  ? "Flags were true" 
  : "Not all Flags were true")
  << '\n';

// Not all Flags were true
```

```cpp
const bool flag_1{true};
const bool flag_2{false};

if (flag_1 or flag_2) {
  std::cout << "At Least one flag true \n";
}

// At Least one flag true
```

```cpp
if (const int n = process(); n == 10) {
  std::cout << "output was 10";
}
```

**Note** that the scope of `n` will be limited to the body of the if-statement.

```cpp
switch (package.name) {
case 'a':
case 'A':
  package.hours = 10;
  break;

case 'b':
case 'B':
  package.hours = 20;
  break;

default:
  std::cerr << "Invalid Package Name!\n";
  return 1;
}
```

```cpp
for(int i = 0; i <= 10; i++) {
  std::cout << i << "\t";
}

int i = 0;
while(i < 10) {
  std::cout << "Counting\t" << i << "\n";
  i++;
}

// infinite loops
for(;;) {
  std::cout << "Destroy!\n";
}

while(true) {
  std::cout << "Destroy!\n";
}

// do while 
int counter = 0;
do {
  std::cout << counter << "\n";
  counter += 1;
} while(counter <= 100);
```


---

#### Functions
```cpp
/* old syntax */
bool isLarge(int n) {
  return (n >= 100);
}

/* alternate syntax */
auto task(int num) -> int {
  return num * 2;
}

int main() {
  std::cout << std::boolalpha << isLarge(1001) << '\n';
}
```


##### Function Pointers
```cpp
void hello(const char* msg) {
  std::cout << msg << '\n';
}

int main() {
  // implicit type deduction
  auto placeholder = hello;
  
  // this will also work
  // auto placeholder = &hello;


  placeholder("Hello");
  placeholder("World");
}

// Hello
// World
```

```cpp
void(*placeholder)(const char*) = hello;
```

```cpp
# include <functional>
...
std::function<void(const char*)>
```

```cpp
#include <vector>

void Print(const char* msg) {
  std::cout << msg << '\n';
}

void Tag(const char* msg) {
  std::cout << "<" << msg << "/>";
}

template<typename T>
void ForEach(std::vector<T> vec, void(*func)(T element)) {
  for (T element : vec) {
    func(element);
  }
}

int main() {
  std::vector<const char*> words{"This", "Is", "A", "Message"};
  ForEach<const char*>(words, Print);
  ForEach<const char*>(words, Tag);
}
```

```cpp
#include <iostream>

// this will prevent throwing away function return values
[[nodiscard]] 
auto process(uint a, uint b) -> uint { 
  return a + b; 
}

auto main() -> int {
  /* following line will produce an error */ 
  process(10, 20);
  std::cout << "sum " << '\n';
}
```


##### Lambdas
```cpp
int main() {
  std::vector<const char*> words{"This", "Is", "A", "Message"};
  ForEach<const char*>(words, [](const char* msg) {
    std::cout << msg << '\t';
  });
}
```

```cpp
int main() {
  auto print = [](const char* message) -> void { 
    std::cout << message << '\n'; 
  };
  
  print("Hello world");
}
```

```cpp
#include <functional>

int main() {
  int total{30};
  
  std::function<int(int, int)> add = [&total](int a, int b) {
    total += a + b;
    return total;
  };

  std::cout << "sum: " << add(10, 50) << '\n';

}
```


Note: The Square brackets of the lambda expression are called Capture List. The lambda expression is needed to modify the value of the captured variable (i.e. total) therefore it is passed by reference. Read-only variables can be captured by Lambda expressions without the reference &

If we need to capture all values in scope, we can do the following

```cpp
// capture all variables by reference
auto add = [&](int a, int b) { ... }

// capture all variables by value
auto add = [=](int a, int b) { ... }
```

```cpp
#include <iostream>

auto main() -> int {
  auto range = [i = 0]() mutable { 
    return i++; 
  };
  
  std::cout << range() << '\n'      /* 0 */
            << range() << '\n'      /* 1 */
            << range() << '\n';     /* 2 */
}
```


---

#### Strongly Typed Enums
```cpp
enum class Color {
  Red, Green, Blue
};

int main() {
  Color c{Color::Red};
}
```


---

#### Random Numbers
```cpp
#include <iostream>
#include <ctime>

Int main() {
  /* randomize seed: don’t randomize more than once */ 
  std::srand{time(NULL)};
  const int num = std::rand() % 50 + 10;

  std::cout << num << "\n";
}
/* generate numbers in range [10,60) */
```

```cpp
#include <iostream>
#include <ctime>

namespace Random {
  bool m_seed_set{false};

  int randInt(const int& floor, const int& ceil) {
    if(!m_seed_set) {
      std::srand(time(NULL));
      m_seed_set = true;
    }
    return std::rand() % (ceil - floor) + floor;
  }
}

int main() {
  for(uint i = 0; i < 100; i++) {
    std::cout << Random::randInt(50, 100) << "\t";
    if ((i + 1) % 10 == 0) std::cout << '\n';
  }
}
```


---

#### Exception Handling
```cpp
#include <iostream>

/* throw exception: NOT RECOMMENDED */
bool throw_runtime_excp(const int &num) {
  if (num == 300) {
    throw std::runtime_error{"The number was 300. Cannot proceed"};    
  }

  return true;
}

int main() {
  bool result;

  try {
    result = throw_runtime_excp(300);
  } catch (const std::runtime_error &err) {
    std::cerr << "[error] " << err.what() << "\n";
    return 1;
  }

  if (result) {
    std::cout << "all good! \n";
  }
}
```

```cpp
#include <iostream>
#include <optional>

/* better alternative */
std::optional<bool> returns_optional(const int& num) {
  if (num == 300) {
    return {};
  }

  return true;
} 

int main() {
  std::optional<bool> result = returns_optional(400);

  if (!result) {
    std::cerr << "[error] optional value not returned \n";
    return 1;
  }


  if (*result) {
    std::cout << "all good! \n";
  }
}
```


##### Force Terminate Program
```cpp
#include <iostream>
#include <cstdlib>

int main() {
  const int num{300};

  for(int i = 0; i < num; i += 2) {
    if(i % 30 == 0) {
      std::cout << '\n';
    } else {
      std::cout << i << "\t";
    }


    if(i == 250) {
      std::cout << "[250]\t Exception reached\n";
      exit(EXIT_FAILURE);
    }
  }
}
```


---

#### Namespaces
```cpp
#include <filesystem>
#include <iostream>

/* bring specific symbols into scope */
using std::cout, std::boolalpha;

/* alias a long namespace */
namespace fs = std::filesystem;

int main() {
  const char *path = "./example/02";
  const bool is_dir = fs::is_directory(path);

  cout << boolalpha << is_dir << '\n';
}
```

```cpp
/* file: Entity.hpp */
#pragma once
#include <iostream>

namespace Entity {
struct Entity {
  uint x, y;
};

Entity New(uint x, uint y);
void Serialize(const Entity &e, char *buf);
std::ostream& operator<<(std::ostream& stream, const Entity &e);
}; // namespace Entity
```

```cpp
/* file: Entity.cpp */
#include "./Entity.hpp"

Entity::Entity Entity::New(uint x, uint y) {
  Entity e = {.x = x, .y = y};
  return e;
}

void Entity::Serialize(const Entity &e, char *buf) {
  std::sprintf(buf, "Entity{x: %d, y: %d}", e.x, e.y);
}

std::ostream& Entity::operator<<(std::ostream& stream, const Entity &e) {
  stream << "Entity{x:" << e.x << ", y:" << e.y << "}";
  return stream;
}
```

```cpp
/* file: main.cpp */
#include <iostream>
#include "./Entity.hpp"

int main() {
  Entity::Entity e = Entity::New(10, 20);
  std::cout << e << "\n";
}
```


---

#### Static
The static keyword can have different meanings depending on the context in which it is used. 

- Used outside of a class / struct
- Used inside local scope
- Used Inside a class / struct (discussed in OOP Section)


##### Used Outside of a class / struct
When a symbol (i.e. variable, function etc.) is defined as static, the symbol will be limited to its translation unit and the linker will not try to link it across different translation units. In other words, static makes the variable private within its translation unit.

```cpp
static const int number = 300;
```


##### Used inside Local Scope
Variables inside local scope e.g. functions can be defined as static. This sets the lifetime of the variable equal to the full length of execution of the program. This means that any time this function will be called, the static variables inside the function will not be reinitialized. Instead their previous values will be used.

```cpp
int generator() {
  static uint id{0};
  id++;
  return id;
}

int main() {
  for (uint i = 0; i < 100; i++) {
    std::cout << generator() << "\n";
  }
}
```

The above code behaves as if the variable id was a global variable, however this variable cannot be modified from outside the function `generator`.


---

#### Generics
Generics are a way to write meta-code i.e. instructions that get evaluated at compile time which instruct the compiler to write code for us.

```cpp
template<typename T>
void print(T data) {
  std::cout << data << '\n';
}

int main() {
  /* infer type of data */
  print("Hello");
  print('a');
  print(300);
  print(40.2222f);
  print(true);

  /* explicitly specify type of data */
  print<int>(30);
}
```

```cpp
template<typename T, int N>
class List {
public:
  std::array<T, N> m_data;
  uint m_size{N};

  std::array<T, N> iter() const {
    return m_data;
  }
};

int main() {
  List<int, 200> my_list{0};
  for(auto i : my_list.iter()) std::cout << i << "\t";
}
```


##### Infer return types
```cpp
#include <iostream>
#include <tuple>  /* to access std::get */

class Entity {
private:
  uint m_x, m_y;

public:
  Entity(uint x, uint y) : m_x(x), m_y(y) {}

  /* return type is not the same at the argument types */
  auto operator+(const Entity &other) const -> std::pair<uint, uint> {
    auto result = std::make_pair(m_x + other.m_x, m_y + other.m_y);
    return result;
  }
};

/**
 *  decltype will infer the return type when it is not the same as argument 
 *  types
 */
template <typename T> 
auto sum(const T &a, const T &b) -> decltype(a + b) {
  return a + b;
}

auto main() -> int {
  const Entity a{10, 20};
  const Entity b{1000, 2000};

  /* result type is deduced to be std::pair<uint, uint> */
  auto result = sum(a, b);

  std::cout << "Pair: " << std::get<0>(result) << ", " 
            << std::get<1>(result) << "\n";
}
```


---

#### Constant Expressions
Constant Expressions keyword `constexpr` can be used to optimize pure functions. These functions take arguments and calculate results based solely on the arguments. `constexpr` instructs the compiler to compute their results at compile-time rather than at run-time, although compile-time computation is not guaranteed. This will lead to faster program execution.

All `STL` Template arguments and some `STL` Functions are meant to be constants. We can use `constexpr` to tell the compiler that the value is in fact constant. This value will be evaluated at compile time. See the following example for better understanding.

```cpp
constexpr uint factorial(const unsigned int& number) {
  if(number == 0) return 1;

  uint retval{1};
  for(uint i = 2; i <= number; i++)
    retval *= i;

  return retval;
}

int main() {
  std::array<uint, factorial(3)> list{0};
  for(const auto& elem : list)
    std::cout << elem << "\t";
}
```

`std::array` is a Template and both arguments (i.e. data type and length) must be either constant or known at Compile-Time. If the `factorial()` function is not marked as a Constant Expression the compiler will bitch that a Non-Constant value has been provided as a Template Argument.


---

#### Constant Evaluation
Any time we want to ensure that a function will only be computed at compile time, we must use `consteval` instead of `constexpr`. The following code will compile without errors. However, `n` is not a constant so we cannot guarantee that this function will not be executed during run-time.

```cpp
constexpr auto process(uint a, uint b) -> uint { 
  return a + b; 
}

auto main() -> int {
  int n = 20;
  auto result = process(n, 20);
  std::cout << "sum " << result << '\n';
}
```

```cpp
consteval auto process(uint a, uint b) -> uint { 
  return a + b; 
}

auto main() -> int {
  int n = 20;
  auto result = process(n, 20);
  std::cout << "sum " << result << '\n';
}
```


---

#### Command Line Arguments

```cpp
#include <iostream>

int main(int argc, char* argv[]) {
  std::cout << "Number of Arguments: " << argc << '\n';

  for(uint i = 0; i < argc; i++) {
    std::cout << argv[i] << '\n';
  }
}
```


---

#### Algorithms

Sort Vector of Random Numbers

```cpp
#include <algorithm>
#include <ctime>
#include <functional>
#include <iostream>
#include <vector>

std::vector<int> random_nums(int total_nums, int start, int end) {
  std::vector<int> result;
  for (int i = 0; i < total_nums; i++) {
    int num = std::rand() % (end - start + 1) + start;
    result.push_back(num);
  }
  return result;
}

void print_vector(const std::vector<int> &vec) {
  for (auto &n : vec) {
    std::cout << n << " ";
  }
  std::cout << '\n';
}

int main() {
  std::vector<int> randoms = random_nums(50, 10, 50);
  print_vector(randoms);

  /* sort descending */
  std::sort(randoms.begin(), randoms.end(), std::greater<int>());
  print_vector(randoms);
}
```

Note: std::sort() can be provided a function / lambda as a third argument. This will be used to sort in a custom order.

Note: std::sort() is a versatile function which can even be used to sort alphabets in a string.

We can provide a custom function for sorting STL Containers. There are also various builtin functions that can be used.


---

#### Structured Bindings
```cpp
std::pair<const char*, int> get_person() {
  return { "Moeen", 28 };
}

int main() {
  auto[name, age] = get_person();
  std::cout << "My name is " << name << " and I am " 
            << age << " years old\n";
}
```

Note: In the above code, we could have used `std::tuple` instead of `std::pair` and it would still work the exact same way.

```cpp
std::map<const char*, const char*> data {
  { "moeenn", "github" },
  { "waqar", "gitlab" },
};

for (const auto&[name, site] : data) {
  std::cout << "[name] " << name << "\t[site] " << site << '\n';
}
```

