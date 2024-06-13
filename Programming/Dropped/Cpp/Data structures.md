#### Struct
```cpp
struct Point {
  int x;
  int y;
};
```

```cpp
# method # 1
Point p {10 , 20};

# method # 2
Point p = Point {20, 30};

# method # 3
Point p = {
  .x = 10,
  .y = 20,
};

# method # 4
auto p = Point {
  .x = 20,
  .y = 40,
};

```

Methods can also be attached to structs

```cpp
#include <iostream>

struct Player {
  uint m_xpos, m_ypos;
  uint m_speed;

  Player(const uint& speed) 
      : m_xpos(0), m_ypos(0), m_speed(speed) {}

  void move(int x, int y) {
    m_xpos += x * m_speed;
    m_ypos += y * m_speed;
  }

  std::pair<uint, uint> position() { 
    return std::make_pair(m_xpos, m_ypos); 
  }
};

int main() {
  Player player(10);
  player.move(2, 3);

  std::pair<uint, uint> pos = player.position();

  std::cout << "[x] " << pos.first << "\n"
            << "[y] " << pos.second << "\n";
}
```

Pointers to Struct Objects

```cpp
struct Record {
  const char* key;
  const char* data;
};

int main() {
  Record base_record;
  Record *my_record = &base_record;

  my_record->key = "laravel";
  my_record->data = "A PHP Framework";

  std::cout << my_record->key << "-" << my_record->data << '\n';
}
```


---

#### Arrays
Array Container is an Alternative to the standard C-Style Array. It stores Contiguous data in Stack Memory. The main advantage of STL Container Array over C-Style Array is that Iterator and Iterator specific methods have been implemented.

```cpp
#include <array>

int main() {
  std::array<int, 10> nums{1, 2, 4, 30, 40, 50, 3};

  for(int i = 0; i < nums.size(); i++) {
    // no bounds checking
    std::cout << nums[i] << '\n';
 
    // perform bounds checking (at Runtime!)
    std::cout << nums.at(i) << '\n';
  }
 
  // range-based for-loop 
  for (const int n : nums) {
    std::cout << n << "\n";
  }
}
```

Unassigned Elements in the STL Array will contain garbage values. If we need the whole STL array to be 0-Valued we can do following

```cpp
std::array<int, 200> nums{0};
```

Array can also be initialised in the following way

```cpp
auto nums = std::array<int, 3> {1,2,3};
```

```cpp
struct TestCase {
  std::array<int, 3> nums;
  int result;
};

int main() {
  TestCase testCase = TestCase {
    .nums = {1,2,3},
    .result = 50,
  };
}
```


---

#### Vectors
```cpp
#include <vector>

int main() {
  std::vector<int> myVector;

  // adding elements to end
  for(auto i=100; i <= 1000; i += 50) {
    myVector.push_back(i);
  }

  // adding elements to start
  myVector.insert(myVector.begin(), 404);


  // adding elements to index 2
  myVector.insert(myVector.begin() + 2, 1001);

  // loop through the vector
  for(const int& n : myVector) {
    std::cout << n << '\n';
  }

  // using iterators: standard way of traversing containers
  for(auto i = myVector.begin(); i != myVector.end(); i++) {
    std::cout << *i << "\t";
  }

  // size of vector
  std::cout << "\nSize: " << myVector.size() << "\n";
}
```

**Note** We can also access individual elements inside a Vector using subscripts e.g. `myVector[2]`. A better approach is to use the method `at()` which will also perform bounds checking on the Vector.


##### How Do Vectors Work?
Vectors store Data on the Heap. Every time we add an element to the Vector, a new Vector is created that is larger than the original Vector and then old elements are copied over from the original Vector. **The elements in Vector are stored contiguously**. Vectors also have optional bounds checking with the `at()` method i.e. same as `STL` Arrays.


Operator Overloading can be implemented to Print out an entire Vector using `std::cout`.

```cpp
std::ostream& operator<<(std::ostream& stream, const std::vector<int>& vec) {
  for(const auto& elem : vec) {
    stream << elem << " ";
  }
  return stream;
}

int main() {
  std::vector<int> numbers{0,1,2,3,4,5,6,7,8};
  std::cout << numbers << '\n';
}

// 0 1 2 3 4 5 6 7 8
```

Following are properties of Vectors
- Fast Insert / remove at the end: O(1)
- Slow Insert / remove at the beginning: O(n)
- Slow Search: O(n)


---

#### Tuples

```cpp
#include <iostream>
#include <tuple>

int main() {
  std::tuple<const char*, uint, bool> person = { "Admin", 28, true };
  std::cout << "[name] " << std::get<0>(person) << '\n'
            << "[age] " << std::get<1>(person) << '\n'
            << "[isEmployed] " << std::boolalpha << std::get<2>(person) 
            << '\n';
}
```

```cpp
auto person = std::make_tuple("Admin", 28, true);
```


---

#### Pair
```cpp
#include <iostream>

int main() {
  std::pair<const char*, uint> person = { "Moeen", 28 };
  std::cout << "[name] " << person.first << '\n'
            << "[age] " << person.second << '\n';
}
```

```cpp
std::pair<int, std::string> p = std::make_pair(10, "Hello world");
```


---

#### Maps

```cpp
#include <iostream>
#include <map>

int main() {
  std::map<std::string, std::string> capitals = {
    {"Pakistan", "Islamabad"},
    {"China", "Beijing"},
  };

  for (const std::pair<std::string, std::string> pair : capitals) {
    std::cout << pair.first << ", " << pair.second << "\n";
  }

  // structured bindings
  for (const auto& [key, value] : capitals) {
    std::cout << key << ", " << value << "\n";
  }

  auto entry = std::make_pair("Britain", "London");
  capitals.insert(entry);


  bool exists = capitals.find("USA") != capitals.end();
  std::cout << std::boolalpha << exists << "\n";
}
```

The Keys Inside the Map are Constants. This means that they cannot be changed after dereferencing.

```cpp
// illegal behavior
(*iter).first = "c#";
```


---

#### Stack

```cpp
#include <iostream>
#include <stack>

int main() {
  std::stack<int> s;
  {
    s.push(10);
    s.push(20);
  }

  while (!s.empty()) {
    std::cout << s.top() << "\n";
    s.pop();
  }
}
```

**Note**: `pop` method does **NOT** return the value at the top of the stack.


---

#### Standard Template Library (STL)

Algorithms are Functions that perform predefined sets of operations. Containers refer to prebuilt advanced Data Structures provided with the language.

The implementation details of different Data Structures can be very different from each other. This means that different Algorithms cannot operate directly on different Containers. 

In order to solve this problem the concept of Iterators was introduced. Iterators allow the Containers to have a standard interface which allows different Algorithms to be able to operate on different Containers. 

Note: The Design of the STL goes against the Ideas of OOP which seeks to combine Algorithms and Data Structures. This design was followed to make the code mode modular and therefore more reusable.


---

#### Types of Containers
Sequence Containers 
- Vector, Deque
- List
- Forward List
- Array

Associative Containers (Binary Trees) i.e. Ordered Containers 
- Set and Multi-set
- Map and Multi-map

Unordered Containers (Hash Tables) 
- Unordered Set / Multi-set
- Unordered Map / Multi-map

```cpp
#include <vector>
#include <deque>
#include <list>
#include <set> 				// set and Multi-set
#include <map> 				// map and Multi-map
#include <unordered_set>	// unordered set or Multi-set
#include <unordered_map> 	// unordered map or Multi-map
#include <iterator>
#include <algorithm>
#include <numeric> 			// some numeric algorithms
#include <functional>
```


---

#### Deque
Deque is a dynamic array that can grow in two directions i.e. towards the beginning and towards the end of the Deque. Deque provides Non-Contiguous data in Heap Memory.

```cpp
#include <iostream>
#include <deque>

// overloading for stream insertion operator
std::ostream& operator << (std::ostream& stream, const std::deque<int>& d) {
	for(const auto& elem : d)
		stream << elem << " ";
	return stream;
}

int main() {
	std::deque<int> numbers{1,2,3,4,5,6};

	// insert at beginning
	numbers.push_front(0);

	// insert at the end
	numbers.push_back(7);

	std::cout << numbers << std::endl;
}
```

Following are properties of Deque
- Fast Insert / Remove at the beginning and the end: O(1)
- Slow Insert / Remove in the Middle: O(n)
- Slow Search: O(n)


---

#### List
List is a Double Linked List.

```cpp
int main() {
	std::list<int> numbers{100, 20, 50, 34, 82, 95};

	// add elements
	numbers.push_front(5);
	numbers.push_back(70);

	// find element "50" inside the list
	// if value is found :: *result == 50
	// if value not found :: *result == no. of elements in the list
	std::list<int>::iterator result = 
            std::find(numbers.begin(), numbers.end(), 50);


	std::cout << *result << std::endl;	// *result == 50

	// insert() method :: new element will be inserted before 
    // the provided iterator
	numbers.insert(result, 2000);
	std::cout << numbers << std::endl; 
    // 5 100 20 2000 50 34 82 95 70

	// increment iterator: *result == 34
	result++;

	// remove the selected element i.e. 34
	numbers.erase(result);				
    // 5 100 20 2000 50 82 95 70

	std::cout << numbers << std::endl;
}
```

Following are properties of List
- Fast Insert / Remove at any place in the List: O(1)
- Slow Search: O(n)
- No Random Access i.e. Subscripts [] cannot be used with Lists 
- splice() method is present with List; it allows copying of elements from one list into another in Constant Time i.e. O(1)


---

#### Associative Containers (Binary Trees)
Associative Containers are also called Ordered Containers because the Elements in the Container are always sorted. Associative Containers don’t have the methods push_back() or push_front()


##### Sets
A Set is a group of Non-Duplicate Elements. 

```cpp
int main() {
	std::set<int> primes;
	primes.insert(2);			// O(log(n))
	primes.insert(3);
	primes.insert(5);

	// find() method is present for associative containers
	// but not for sequence containers
	std::set<int>::iterator result =  primes.find(5); 	// O(log(n))

	// inserting duplicate element int set
	// retval_dup.first == iterator pointing to the provided value
	// irrespective of whether insert succeeds or fails
	// retval_dup.second == boolean false if insert fails
	std::pair<std::set<int>::iterator, bool> retval_dup 
            = primes.insert(3);
	
      std::pair<std::set<int>::iterator, bool> retval_nondup 
            = primes.insert(7);

	assert(*retval_dup.first == 3);
	assert(retval_dup.second == false);
	assert(*retval_nondup.first == 7);
	assert(retval_nondup.second == true);

	// remove an element (iterator is not required)
	// in sequence containers e.g. vectors, iterator is required
    // by erase() method
	primes.erase(2);

	std::cout << primes << std::endl;
}
```

One important thing to note is that the Iterators to the Elements in a Set / Multi-set are Constants. They cannot be modified through dereferencing.


##### Multi-set
A Multi-set is the same as a Set with one distinction: Multi-set allows Duplicate Elements. This also means that insertion into a Multi-set will always succeed, provided the element is of the right data type.

Following are the Properties of Set / Multi-set:
- Fast Search: O(log(n))
- Traversing through the Set / Multi-set is slow compared with Vector or Deque
- No Random Access Allowed i.e. Subscripts [] are not available with Sets / Multi-sets.


---

##### Multi-map
Multi-map is the same as a Map with one distinction: Multi-map allows duplicate Keys.


---

#### Unordered Containers
Hash Table: An Array of Linked Lists

```cpp
#include <iostream>
#include <unordered_set>
#include <string>
#include <array>

int main() {
	std::unordered_set<std::string> set{"red", "green", "blue"};

	// if value is found :: iterator to value is returned
	// if value not found :: iterator to end() is returned
	std::unordered_set<std::string>::const_iterator iter 
            = set.find("violet");	// O(1)

	// important: check if value is found
	// if we deref set.end() the core will be dumped
	if(iter != set.end()) {
		std::cout << *iter << "\n";
	}

	// insert values into unordered set
	set.insert("yellow");

	// insert std::array into an unordered set
	std::array<std::string, 2> new_elems = {"charcoal", "magenta"};
	set.insert(new_elems.begin(), new_elems.end());

	for(const auto& elem : set)
		std::cout << elem << "\n";
}
```

Following are the properties of Unordered Containers
- Fastest Insert at any place: O(1)
- Fastest Search: O(1)
- Unordered Set / Multi-set: Element values cannot be changed
- Unordered Map / Multi-map: Element Key cannot be changed


