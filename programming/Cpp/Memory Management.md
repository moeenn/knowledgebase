**Stack**: An area in our system memory that has a fixed / predefined size depending on the Compiler and the System Architecture. Stack size is usually `~2MB`. 

**Heap**: An area in our system memory that is entirely dependent on the amount of memory physically installed in the system. This is also sometimes called Dynamic Memory.


##### Differences between Stack & Heap
Memory in stack is automatically managed whereas memory in Heap needs to be manually managed by the programmer. E.g. When a variable is created on the Stack, it will be automatically deleted when it goes out of scope. Variables created on the Heap will remain in the Heap until they are manually deleted in the Program.

Note: The situation where data is stored on the Heap but not deleted after it has been used is called a Memory Leak.

In Stack Memory, the variables are stored contiguously in memory. This makes Stack memory much faster than Heap Memory. In Heap memory, variables are created wherever there is space available. There is more CPU cycles required to keep track of free memory (i.e. Free List), address look-ups, extending memory allocation of objects etc. which makes Heap memory slower than Stack Memory.


---

#### Example

```cpp
struct Entity {
  int x, y;
};

int main() {
  /* variables on the stack */
  int s_int = 40;
  float s_float = 30.5f;
  int s_array[5] = {1, 2, 3, 4, 5};
  Entity s_struct = {30, 40};

  /* create variables on Heap */
  int *h_int = new int;
  *h_int = 40;

  float *h_float = new float;
  *h_float = 30.5f;

  int *h_array = new int[5];
  for (auto i = 0; i < 5; i++) {
    h_array[i] = i + 1;
  }

  Entity *h_struct = new Entity;
  *h_struct = {30, 40};

  /* free-up memory on Heap */
  delete h_int;
  delete h_float;
  delete[] h_array;
  delete h_struct;
}
```


---

#### Pointers

Pointer is simply an integer that holds a memory address. Primitive types (e.g. int, char, bool) are completely irrelevant to a pointer. Pointer is a large number that is represented in the form of a hexadecimal number.

Pointers are used for two reasons:
1. Scope of variables is at block level and global variables should be avoided as much as possible. Pointers are used to share variables between different functions
2. Optimize the memory usage: When a variable is passed to a function, the function receives a copy of the original variable. Duplicating data between variables can be prevented using pointers.


```cpp
/* pointer to an int value */
int num = 300;
int* ptr = &num;

/* pointer to a pointer */
int** ptr_to_ptr = &ptr;

/* dereferencing a pointer */
*ptr = 100;                   /* num = 100 */
**ptr_to_ptr = 600;           /* num = 600 */
```

```cpp
/* passing variable by pointer */
void myFunc(int* num) {
  std::cout << "You entered: " << *num << "\n";
  *num += 30;
}

int main() {
  int a{30};

  myFunc(&a);                 /* You entered: 30 */
  std::cout << a << "\n";     /* 60 */
}
```

We cannot modify the  variable a (declared in main) from within the function myFunc unless we use pointers.

```cpp
/* passing value by reference */
void myFunc(int& num) {
  std::cout << "You entered: " << num << "\n";
  num += 30;
}

int main() {
  int a{30};

  myFunc(a);                  /* You entered: 30 */
  std::cout << a << "\n";     /* 60 */
}
```


---

#### Smart pointers
Smart Pointers provide a wrapper around traditional C-Style Pointers to try to prevent memory leaks in Heap Allocated Pointers. Smart Pointers are not created with the new keyword and therefore don’t need to be deleted with the delete keyword.

There are different types of Smart Pointers

- `std::unique_ptr`: This pointer is limited to its scope. When the pointer goes out of scope it is automatically deleted and memory is freed. Unique pointer cannot be copied i.e. no two unique pointers can point to the same variable in memory

- `std::shared_ptr`: Shared Pointers can be copied. The data itself is Heap allocated but the pointer is stored on the stack. Shared Pointers have a property Reference Counter. This property keeps track of Total number of references made to the pointer. When a shared pointer is copied, the Reference Counter is incremented by One. When a copy is deleted (e.g. copy going out of scope) the Reference counter is Decremented by One. When the Reference Counter reaches Zero, the original variable in the Heap memory is deleted and memory is freed. 


---

#### Unique Pointers

```cpp
#include <memory>

class Entity {
private:
  int m_counter;

public:
  Entity(int counter) : m_counter(counter) {
    std::cout << "[Entity] Created" << '\n';
  }

  ~Entity() {
    std::cout << "[Entity] Deleted ..." << '\n';
  }

  void action() {
    std::cout << "[Entity] Counter Value: " << m_counter << '\n';
  }
};

int main() {
  std::unique_ptr<Entity> e = std::make_unique<Entity>(10);
  e->action();
}

// [Entity] Created
// [Entity] Counter Value: 10
// [Entity] Deleted ...
```


---

#### Shared Pointer

```cpp
void execute(std::shared_ptr<Entity> e) {
  e->action();
}

int main() {
  std::shared_ptr<Entity> e = std::make_shared<Entity>(20);

  // create copy: reference count += 1
  std::shared_ptr<Entity> shared_e = e;
  execute(shared_e);
}

// [Entity] Created
// [Entity] Counter Value: 20
// [Entity] Deleted ...
```


---

#### Void Pointers

```cpp
#include <iostream>
#include <string>

template<typename T>
class Node {
private:
  T m_value;
  void* m_ref;

public:
  Node(T value) {
    m_value = value;
  }

  void setRef(void* ref) {
    m_ref = ref;
  }

  void* getRef() const {
    return m_ref;
  }
};

int main() {
  Node<int> n1{300};
  Node<std::string> n2{"Random String"};

  n1.setRef(&n2);

  // cast void ptr to (std::string*) and the dereference 
  std::string n1_ref_value = *(std::string*)(n1.getRef());

  std::cout << "N2 ref: " << &n2 << '\n'
            << "N1 holding ref: " << n1.getRef() << '\n'
            << "N1 ref value: " << n1_ref_value << '\n';
}
```


---

#### Tracking Heap Allocations

```cpp
#include <iostream>
#include <string>
#include <memory>

class Entity {
public:
  Entity() { std::cout << "Entity created\n"; }
  ~Entity() { std::cout << "Entity Destroyed\n"; }
};

uint32_t allocations = 0;

void *operator new(size_t size) { 
  allocations++;
  std::cout << "[alloc] " << allocations << '\n';
  return malloc(size); 
}

int main() {
  std::unique_ptr<Entity> e = std::make_unique<Entity>();
  std::unique_ptr<Entity> e_2 = std::make_unique<Entity>();
}

/**
 * [alloc] 1
 * Entity created
 * [alloc] 2
 * Entity created
 * Entity Destroyed
 * Entity Destroyed
 */
```

