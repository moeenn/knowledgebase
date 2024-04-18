```cpp
#include <iostream>

class Person {
private:
  /* It is a convention that the member variable should start with m_ */
  std::string m_name;
  uint m_age;

public:
  /* constructor */
  Person(std::string name, uint age) : m_name(name), m_age(age) {}

  /* member functions that don't modify state should be marked const */
  void print() const {
    std::cout << "[Name] " << m_name << '\n' << "[Age] " << m_age << '\n';
  }

  /* class destructor */
  ~Person() { std::cout << "Running destructor ...\n"; }
};

int main() {
  /* direct initialization */
  Person p{"User one", 30};

  /* implicit call to constructor */
  Person x = {"User two", 20};

  p.print();
  x.print();
}
```

It is generally a good idea to prevent implicit constructor calls in our code.

```cpp
explicit Person(std::string name, uint age) : m_name(name), m_age(age) {}
```

```cpp
#include <iostream>

class Shape {
private:
  float m_length, m_width;

public:
  explicit Shape(float length, float width)
      : m_length(length), m_width(width) {}

  float area() const;
  float perimeter() const;
};

float Shape::area() const { return m_length * m_width; }
float Shape::perimeter() const { return 2 * (m_length + m_width); }

int main() {
  Shape s1{30, 20};

  std::cout << "Area: " << s1.area() << '\n'
            << "Perimeter: " << s1.perimeter() << '\n';
}
```


---

#### Printing Custom Objects 

```cpp
#include <iostream>
#include <ostream>

class Pixel {
private:
  uint m_red, m_green, m_blue;

public:
  explicit Pixel(uint red, uint green, uint blue)
      : m_red(red), m_green(green), m_blue(blue) {}

  friend std::ostream &operator<<(std::ostream &os, const Pixel &p) {
    return os << '(' << p.m_red << ", " << p.m_green << ", " << p.m_blue << ')';
  }
};

int main() {
  Pixel p{10, 20, 30};
  std::cout << p << '\n';
}
```


---

#### Reusable Classes and Headers

```cpp
/* main.cpp */
#include "Log.hpp"
#include <iostream>

int main() {
  Log log;
  log.SetLevel(log.LogLevelError);
  log.Error("This is an error");
  log.Warn("This is a warning");
  log.Info("This is some information");
}
```

```cpp
/* Log.hpp */
#pragma once
#include <iostream>

class Log {
public:
  const int LogLevelError = 0;
  const int LogLevelWarning = 1;
  const int LogLevelInfo = 2;

private:
  int m_LogLevel = LogLevelInfo;

public:
  void SetLevel(int level);
  void Error(const char *msg);
  void Warn(const char *msg);
  void Info(const char *msg);
};
```

**Note**: Only the skeleton of the class is defined inside the header file. The actual methods are defined inside the related `CPP` file.

```cpp
/* Log.cpp */
#include "Log.hpp"

void Log::SetLevel(int level) { m_LogLevel = level; }

void Log::Error(const char *msg) {
  if (m_LogLevel >= LogLevelError) {
    std::cout << "[ERROR] \t" << msg << std::endl;
  }
}

void Log::Warn(const char *msg) {
  if (m_LogLevel >= LogLevelWarning) {
    std::cout << "[WARNING] \t" << msg << std::endl;
  }
}

void Log::Info(const char *msg) {
  if (m_LogLevel >= LogLevelInfo) {
    std::cout << "[INFO] \t\t" << msg << std::endl;
  }
}
```

**Note**: It is apparent from the above example that every class has its own unique namespace with the same name as the class.


---

#### Static

##### Static Attributes
Normally when we create instances of a class, the attributes of each instance are stored separately in memory. When we set an attribute within a class as static, it means that this attribute will be shared across different instances of the class. In other words, the static attribute will be stored in memory once and all instances of the class will have the option to read and modify its value.

```cpp
#include <iostream>

class Utils {
private:
  /* it is convention that static member variables start with s_ */
  static int s_Number;

public:
  int get() const { return s_Number; }
  void set(int num) { s_Number = num; }
};

/**
 *  this prevents undefined reference error
 *  we can also define default value for static members here
 */
int Utils::s_Number;

int main() {
  Utils utils;
  utils.set(30);
  std::cout << utils.get() << '\n'; /* 30 */

  Utils utils_a;
  std::cout << utils_a.get() << '\n'; /* 30 */
}
```

- If a Static data member will not change, we can declare it as const directly inside the class declaration.
- If a Static data member will change, We CANNOT provide default values for static data members inside the class. The default value needs to be set outside the class as below.

```cpp
int Utils::s_Number = 30;
```

- Non-Static Methods can access static variables but Static Methods cannot access non-static variables


#### Static Methods
Consider that we have a class with some methods that we would like to call without instantiating an object for that class. We can do so if we declare our class methods as static. This can be useful for grouping together related functions as class methods.

One important thing to note here is that static methods cannot directly access non-static attributes.

```cpp
class Utils {
public:
  static void hello(const char *msg) { std::cout << msg << '\n'; }
};

int main() { Utils::hello("My name is Jeff"); }
```

**Remember**: Static attributes and methods should be called through the class namespace (i.e. through the scope resolution operator `::` ) and all other attributes and methods should be called through the dot operator.


---

#### How do Classes Work
Under the hood, there is no such thing as classes. The code is massively simplified before it can be compiled into machine code. Classes simply provide syntactic sugar to help out in coding. 

The way classes are coded gives the impression that the methods within the class are somehow tied together. In reality, they are able to function the way they do because the compiler is able to pass an invisible argument to all the class methods. This invisible argument is the name of the object of our class.

The above is true for all methods except static methods. They don’t receive the invisible argument and are therefore not able to access the non-static member variables within the class.

The same behavior is even more apparent in Python where we specify the name of the invisible argument using the conventional name self. Similarly, we don’t pass class the self variable to static methods.  

---

#### Constructors & Destructors
```cpp
class Entity {
private:
  float m_x, m_y;

public:
  /* constructor */
  explicit Entity(float x, float y) {
    m_x = x;
    m_y = y;
  }

  /* destructor */
  ~Entity() { std::cout << "Running Destructor ... " << '\n'; }
  void print() const { std::cout << m_x << ", " << m_y << '\n'; }
};
```

In case we simply need to assign values to member variables in the Constructor, we can use an alternate syntax called Member `Initializers`. Note that member `initializers` can only be used with Constructors.

```cpp
explicit Parent(int x, int y) : m_X(x), m_Y(y) {}
```

Member Initialization Lists don’t allow direct initialization of protected members of the Base Class.


---

#### Const Methods
Methods inside Classes can be made Read-Only by using the `const` keyword.

```cpp
#include <iostream>

class Entity {
public:
  int m_x, m_y;

  Entity() : m_x(0), m_y(0){};
  Entity(int x, int y) : m_x(x), m_y(y) {}

  void display() const { std::printf("Entity(x = %d, y = %d)\n", m_x, m_y); }
};

int main() {
  Entity e(10, 40);
  e.display();
}
```

`const` has been used with the `display()` method. This means that the method is not allowed to modify the member variables. Note that const can only be used in this way inside of a Class.


---

#### Inheritance

Inheritance provides a way to avoid duplication of code by copying the content of one Class (Base / Parent Class) into another Class (Derived / Child Class).

There are two types of inheritance

1. Multilevel Inheritance: Grandfather-father-child relationship between classes. E.g. Class A inherits from Class B which in turn inherits from Class C. 

2. Multiple Inheritance: A single class inherits from many different classes. E.g. Class A inherits from both Class X and Class Y

```cpp
class C : public A {
public:
  C() {
    std::cout << "Running Constructor : C " << '\n';
  }
};
```

Within simple inheritance, if a method is implemented in both parent and child classes, the child class will override the method of the parent class.


---

#### Comprehensive Example

```cpp
#include <iostream>

class Entity {
protected:
  float m_x, m_y;

public:
  explicit Entity(float x, float y) : m_x(x), m_y(y) {}
  void print() const { std::printf("Entity(x=%f, y=%f)\n", m_x, m_y); }
};

class Player : public Entity {
private:
  const char *m_name;

public:
  /* passing arguments to constructor of Base class */
  Player(float x, float y, const char *name) : Entity(x, y), m_name(name) {}

  void print() {
    /* calling method from Base class */
    Entity::print();
    std::printf("name: %s\n", m_name);
  }
};

int main() {
  Player p(30, 10, "Alamira");
  p.print();
}

/**
 *  Entity(x=30.000000, y=10.000000)
 *  name: Alamira
 */
```


---

#### Constructor Precedence
When classes are being inherited, the constructors of the Base (parent) classes are executed before the constructor of the Derived (child) class. See the following code.

```cpp
#include <iostream>

class A {
public:
  A() { std::cout << "Running Constructor: A \n"; }
};

class B {
public:
  B() { std::cout << "Running Constructor: B \n"; }
};

/* multiple inheritance */
class C : public A, public B {
public:
  C() { std::cout << "Running Constructor: C \n"; }
};

int main() { C c{}; }

/**
 *  Running Constructor : A
 *  Running Constructor : B
 *  Running Constructor : C
 */
```

When an Object of Class C is created, the Constructors of Base (parent) classes are executed first. The Compiler will read the list of Base (Parent) classes left to right. After the constructors for all Base classes have been executed only then the constructor for the actual (Derived / child) Class will be executed.

If we change the order in which the classes are inherited, the order of constructors execution will also change accordingly.

```cpp
class C : public B, public A {...}

/**
 *  Running Constructor : B
 *  Running Constructor : A
 *  Running Constructor : C
 */
```


---

#### Polymorphism
The objects of Derived (child) classes can behave as Objects of Base (parent) Classes. For instance, if a function can take an object of the Base (parent) class as an argument, we can also pass an object of the Derived (child) class to this function.

```cpp
void execute(Parent p) {
  p.Run();
}

int main() {
  Child c("Avira");
  execute(c);
}
/* running Run method of Parent Class ... */ 
```

Note: Observe that the Polymorphic Function executed the wrong method. This is due to Compile Time / Early Bindings.


##### Early and Late Binding
At compile time the symbols are generated by the compiler and then linked together by the linker. This linking at compile time is called Early Binding, also called Static Binding or Compile-Time Binding.

Early binding can create wrong links between symbols of classes when Polymorphism is used within the Program. Consider the following scenario.

```cpp
#include <iostream>

class Entity {
public:
  void display() const { std::cout << "Entity Displayed \n"; }
};

class Player : public Entity {
public:
  void display() const { std::cout << "Player Displayed \n"; }
};

class Boss : public Entity {
public:
  void display() const { std::cout << "Boss Displayed \n"; }
};

/* Polymorphic function (can take entity and its derived objects as args) */ 
void display(const Entity &e) { e.display(); }

int main() {
  Entity e{};
  display(e);

  Player p{};
  display(p);

  Boss b{};
  display(b);
}

/**
 *  Entity Displayed
 *  Entity Displayed
 *  Entity Displayed
 */
```

The display function is a Polymorphic Function that can take the Objects of Entity, Player and Boss as the argument. During Compile-Time binding, the compiler sees that we have only explicitly specified the Entity type as an accepted argument. The display function symbol is linked only to the Entity Objects.

Recognizing that the symbols are wrongly linked, we can specify that the symbols should not be linked at the Compile-time, i.e. we can opt for Late Binding. We specify this by declaring the overridden method in Base Class as Virtual.

```cpp
#include <iostream>

class Entity {
public:
  virtual void display() const { std::cout << "Entity Displayed \n"; }
};

class Player : public Entity {
public:
  void display() const override { std::cout << "Player Displayed \n"; }
};

class Boss : public Entity {
public:
  void display() const override { std::cout << "Boss Displayed \n"; }
};

/**
 *  Polymorphic function (can take entity and its derived 
 *  objects as args). Passing by value will NOT work
 */
void display(const Entity &e) { e.display(); }

int main() {
  Entity e{};
  display(e);

  Player p{};
  display(p);

  Boss b{};
  display(b);
}

/**
 *  Entity Displayed
 *  Player Displayed
 *  Boss Displayed
 */
```

Note: Even with Virtual in Place, if the object is not passed to the display function without pointers, the result is wrong.

```cpp
void display(Entity e) {
	e.display();
}
// always executes the display() method defined in Entity Class
```

When a Method is defined as Virtual, Early Binding for the method is not performed. Instead, at compile time a V-Table is created for the Symbol (i.e. the method) which is linked at run-time.


##### Virtual Functions
Consider a scenario where a class Parent is inherited by a Class Child. We know in advance that the method execute() in the Parent Class will be overridden by the Child Class. In order to ensure that the program runs as expected with Polymorphism, we must declare the function as virtual in the Parent Class.


##### Alternate solution using Interface
```cpp
#include <iostream>

/* declare common interface */
class IDisplayable {
public:
  virtual void display() const = 0;
};

class Entity : public IDisplayable {
public:
  void display() const override { std::cout << "Entity Displayed \n"; }
};

class Player : public IDisplayable {
public:
  void display() const override { std::cout << "Player Displayed \n"; }
};

class Boss : public IDisplayable {
public:
  void display() const override { std::cout << "Boss Displayed \n"; }
};

/**
 *  Polymorphic function (can take entity and its derived
 *  objects as args). Passing by value will NOT work
 */
void display(const IDisplayable &e) { e.display(); }

int main() {
  Entity e{};
  display(e);

  Player p{};
  display(p);

  Boss b{};
  display(b);
}

/**
 *  Entity Displayed
 *  Player Displayed
 *  Boss Displayed
 */
```


---

#### Pure Virtual functions, Abstract classes & Interfaces

Pure Virtual Function: A method for which no functionality has been defined yet. A Constructor of a Class cannot be a Purely Virtual Function

Abstract Class: A class that contains one or more Purely Virtual Functions. Objects for Abstract classes cannot be created.

Concrete Class: The Classes that we have previously seen are Concrete Classes i.e. Classes not containing any Purely Virtual Functions

Interface: A Class that only contains Purely Virtual Functions and forces the Child Classes to implement these functions.

```cpp
/* Abstract class */
class X {
public:
  /* pure virtual function */
  virtual void run() = 0;
};
```

Since an Abstract Class is an incomplete Class (because not all functionality has been defined) we are not allowed to create Objects for Abstract Classes. However, Abstract Classes can be Inherited by Other Classes.  

Note: If an Abstract Class is inherited by another Class, the Derived Class must implement the functionality for all Purely Virtual Functions of the Base (Abstract) Class. If it doesn’t, it will also be considered an Abstract Class (and we will not be allowed to create Objects for it).


---

#### Friends
```cpp
#include <iostream>

class Parent {
  friend class Relative;
  friend void display(const Parent &p);

private:
  uint m_counter = 30;

public:
  void run() const { std::cout << "[Parent] Running ... \n"; }
};

class Relative {
public:
  void run(Parent p) const {
    std::cout << "[Relative] " << p.m_counter << " ... \n";
  }
};

void display(const Parent &p) { std::cout << p.m_counter << '\n'; }

int main() {
  Parent p{};
  Relative r{};

  r.run(p);
  display(p);
}
```


---

#### Pointers and Objects

```cpp
/**
 *  Simple Inheritance: B inherits A. Both A and B have constructors
 *  that don't require any arguments
 */
int main() {
  /* create pointer to object on stack */
  B *obj;

  /* create pointer to object on heap */
  B *obj = new B;
}
```

There are differences in the way these pointers work

When creating a pointer to an object on Stack, neither the constructor of A nor B will be executed automatically. This way we can create an object without running any constructors

When creating a pointer to an object on Heap, the constructors for both A and B will be executed automatically (in this order). This behavior is the same as if a simple object was initialized (i.e. no pointers involved)

In the above example following output will be produced

```cpp
B *obj;
/* no output */

B *obj = new B;
/**
 *  Running Constructor :: A
 *  Running Constructor :: B
 */
```

Remember: For ordinary objects we can access the member variables and methods using the dot operator. But for pointers to objects we can only call the member variables and methods using the arrow operator.


---

#### Singletons
Singleton is a design pattern where we realize that there will only be one instance of a class. Instead of allowing a Public Constructor, we return a reference to a static instance of the object. This reference can then be used to execute methods of the class.

```cpp
#include <ctime>
#include <iostream>

class Random {
private:
  /* private constructor */
  Random() { std::srand(time(NULL)); }

public:
  static Random &get() {
    static Random m_instance{};
    return m_instance;
  }

  int Int(const int &floor, const int &ceiling) const {
    return std::rand() % (ceiling - floor) + floor;
  }
};

int main() {
  for (int i = 1; i <= 100; i++) {
    std::cout << Random::get().Int(10, 100) << "\t";
    if (i % 10 == 0) {
      std::cout << "\n";
    }
  }
}
```

