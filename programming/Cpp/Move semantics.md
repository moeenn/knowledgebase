#### `Lvalue` and `Rvalues`
Lvalues generally have some storage backing them i.e. they have an identifiable storage in memory. Everything which is not an Lvalue, is an Rvalue i.e. Rvalues are generally temporary values.


Rules
1. Nothing can be assigned to an Rvalue.
2. We cannot take an Lvalue reference from an Rvalue i.e. we can only have an Lvalue reference for an Lvalue.
3. Rule # 2 doesn’t apply, if the Lvalue reference is const.


---

#### Basic example

```cpp
#include <iostream>

int calculate_lvalue() { return 10; }

int &calculate_lvalue_reference() {
  static int value = 10;
  return value;
}

int main() {

  /* a is lvalue, 10 is rvalue */
  int a = 10;

  /* both a and b are lvalues */
  int b = a;

  /**
   *  the result of the function calculate_value is a temporary value i.e. rvalue.
   *  c is an lvalue
   */
  int c = calculate_lvalue();

  /**
   *  the function calculate_lvalue_reference returns a modifiable l-value 
   *  reference, this is why we can assign to it. 300 is the r-value   
   */
  calculate_lvalue_reference() = 300;
}
```


---

#### Function example

```cpp
#include <iostream>


/* we can pass only lvalues to this function */
void set_value(int &value) { /**/ }


/* we can pass lvalues and rvalues to this function */
void set_by_const_value(const int &value) { /**/ }

int main() {
  int i = 10;

  /**
   *  this will not work because lvalue reference cannot be created
   *  from an rvalue (it can only be created from another lvalue )
   */
  int &a = 10;

  /**
   *  this is valid because we can create a const lvalue reference from an
   *  rvalue (b is const lvalue reference, 200 is an rvalue)
   */
  const int &b = 200;

  /* this is valid because i is lvalue reference */
  set_value(i);

  /**
   *  this will not work because 100 is not an lvalue reference
   *  it is an rvalue
   */
  set_value(100);

  /**
   *  both of the following will work because function accepts const
   *  lvalue reference
   */
  set_by_const_value(i);
  set_by_const_value(100);
}
```

```cpp
#include <iostream>

/* accepts lvalues only */
void print_name(std::string& name) { /**/ }

/* accepts both lvalues and rvalue */
void print_name(const std::string& name) { /**/ }

/* accepts rvalues only (rvalue reference) */
void print_name(std::string&& name) { /**/ }


int main() {
  /* 'first' is lvalue, right hand side of statement is rvalue */
  std::string first = "M. ";

  /* 'last' is lvalue, right hand side of statement is rvalue */
  std::string last = "Moeen";

  /**
   *  'full_name' is lvalue, right hand side of statement is rvalue
   *  when we add two lvalues (first and last), it creates a new temporary
   *  value (which is an rvalue) which is then assigned to 
   *  'full_name' i.e. lvalue
   */
  std::string full_name = first + last;

  /* passing lvalue to the function */
  print_name(full_name);

  /* passing rvalue to the function */
  print_name(first + last);
}
```


---

#### Another example

```cpp
/* lvalues will be bound to this function */
auto print_value(int &value) -> void {
  std::cout << "lvalue " << value << "\n";
}

/* nothing will ever be bound to this function */
auto print_value(const int &value) -> void {
  std::cout << "lvalue / rvalue " << value << "\n";
}

/* rvalues will be bound to this function */
auto print_value(int &&value) -> void {
  std::cout << "rvalue " << value << "\n";
}

auto main() -> int {
  /* prints lvalue */ 
  int n = 10;
  print_value(n);

  /* prints rvalue */
  print_value(10);
}
```


---

#### Move semantics

##### Scenario

```cpp
#include <iostream>
#include <string>

class Entity {
private:
  std::string m_name;

public:
  Entity(const char *name) : m_name(name) {
    std::cout << "entity constructed\n";
  }

  /* copy constructor */
  Entity(const Entity &other) {
    std::cout << "entity copied\n";
    m_name = other.m_name;
  }

  ~Entity() { std::cout << "entity destroyed\n"; }
};

class EntityManager {
private:
  Entity m_entity;

public:
  EntityManager(const Entity& entity) : m_entity(entity) {}
};

int main() { 
  /**
  *  implicit construction of Entity and pass to EntityManager constructor
  *  same as following:
  *  EntityManager em{Entity{"Someone"}} 
  */
  EntityManager em{"Someone"}; 
}

/**
 *  entity constructed
 *  entity copied
 *  entity destroyed
 *  entity destroyed
 */
```

Reference: [Link](https://www.youtube.com/watch?v=ehMg6zvXuMY&t=34s)

