```c
#include <stdio.h>

int main() {
  printf("%s\n", "Hello World");
  return 0;
}
```


---

#### Scalar types
```c
/* import if aliases are required */
#include <stdint.h>

/* import if boolean types required */
#include <stdbool.h>
```

| Type | Size | Alias | Range | 
| ------- | ------- | ------- |------- |
| `char` | 1 byte | `uint8_t` | 0..255 |
| `signed char` | 1 byte | `int8_t` | -128 .. 127 |
| `unsigned short` | 2 byte | `uint16_t` | 0 .. 65,535 |
| `short` | 2 bytes | `int16_t` | -32,768 .. 32,767 |
| `unsigned int` | 4 bytes | `uint32_t` | 0 .. 4,294,967,295 |
| `int` | 4 bytes | `int32_t` | -2,147,483,648 .. 2,147,483,647 |
| `unsigned long long` | 8 bytes | `uint64_t` | 0 .. 18,446,744,073,709,551,615 |
| `long long` | 8 bytes | `int64_t` | -9,223,372,036,854,775,808 .. 9,223,372,036,854,775,807 |
| `float` | 4 bytes | - | 3.4E-38 to 3.4E+38 |
| `double` | 8 bytes | - | - |
| `long double` | 16 bytes | - | - |


##### Boolean Types
In C, boolean types are simply integer literals. They are defined inside the header `stdbool.h`

```c
#define true 1
#define false 0
```


##### Characters
A character written between single quotes represents an integer value equal to the numerical
value of the character in the machine's character set. Following program prints the Characters with their Integer values.

```c
#include <stdio.h>

int main() {
  int i;  
  for(i = 0; i < 256; i++)
    printf("%-10d %c\n", i, i); /* print as decimal and char */

  return 0;
}
```


---

#### Display to console

| Placeholder | Type |  
| ------- | ------- | 
| `%s` | String i.e. character stream |
| `%c` | Character |
| `%d` | Decimal i.e. Base 10 Decimal Number 0-9 |
| `%i` | Integer |
| `%li` | Long Integer |
| `%u` | Unsigned Decimal |
| `%o` | Octal Number i.e. Base 8 Number 0-7 |
| `%x` | Hexadecimal Number i.e. Base 16 Number 0-F |
| `%f` | Floating Point Number |
| `%e` | Exponential Floating Point Number |
| `%%` | A Percentage Symbol |

| Placeholder | Description |  
| ------- | ------- | 
| `%10s` | String with 10 width, right aligned |
| `%-10d` | Decimal (Int) with 10 width, left aligned |
| `%5.2f` | Float with 5 width, and 2 decimal places, right aligned |


---

#### Example 
```c
#include <stdio.h>


/* function signatures */
float convert_to_celcius(int fahrenheit);

/* symbolic constants */
#define LOWER 0
#define UPPER 3000
#define STEP 20

int main() {
  /* Fahr and Celc are both 10 characters wide */
  printf("%10s %10s\n", "Fahr", "Celc");
  for(int i = LOWER; i <= UPPER; i += STEP)
    /* Celc precision is 2 decimal places */
    printf("%10d %10.2f\n", i, convert_to_celcius(i));

  return 0;
}

float convert_to_celcius(int fahrenheit) {
  return (5.0f / 9) * (fahrenheit - 32);
}
```


---

#### Taking Input from User

##### Command-line Arguments
```c
int main(int argc, char *argv[]) {
  int i;
  /* loop over command line args */
  for (i = 0; i < argc; ++i) 
    printf("%s\n", argv[i]);

  return 0;
}
```


##### Interactive Input
```c
#include <stdio.h>

int main() {
  int age;

  printf("How old are you? ");
  scanf("%d", &age);

  printf("You are %d years old\n", age);
  return 0;
}
```


---

##### Arrays

```c
#include <stdio.h>

int main() {
  int nums[] = {10, 20, 30, 40, 50};
  int i;
  size_t len;

  len = sizeof(nums) / sizeof(nums[0]);

  for (i = 0; i < len; ++i)
    printf("%d\n", nums[i]);

  return 0;
}
```

**Note**: sizeof returns `size_t` which is just an alias for `unsigned long`.


---

#### Strings

##### `Sprintf`
`sprintf` is similar to `printf`. It writes a formatted string into a Character Array.

```c
#include <stdio.h>

int main() {
  char result[100];
  sprintf(result, "This is a %s message with id %d", "cool", 300);
  printf("%s\n", result);

  return 0;
}
```


---

#### Structs

```c
#include <stdio.h>

struct Entity {
  unsigned int x, y;  
};

void entity_display(struct Entity *e) {
  printf("Entity(x = %d, y = %d)\n", e->x, e->y);
}

int main() {
  struct Entity e = { .x = 30, .y = 40 };

  e.x = 500;
  e.y = 600;

  entity_display(&e);
  return 0;
}
```


---

#### Enumerations

```c
#include <stdio.h>

enum IP { V4, V6 };

void ip_print(enum IP ip) {
  switch (ip) {
    case V4:
      printf("IP type if v4\n");
      break;

    case V6:
      printf("IP type if v6\n");
      break;

    default:
      printf("Unknown ip type: %d\n", ip);
  }
}

int main() {
  ip_print(V4);
  ip_print(V6);
  ip_print(3);

  return 0;
}
```


---

#### Typedef

```c
#include <stdio.h>
#include <stdint.h>

typedef enum { V4, V6 } IPKind;

typedef struct {
  uint32_t x, y;
} Entity;

int main() {
  Entity e = { .x = 30, .y = 40 };
  printf("entity: Entity{x: %d, y: %d}\n", e.x, e.y);

  IPKind k = V4;
  printf("IP: %s\n", k == V4 ? "v4" : "v6");

  return 0;
}
```


---

#### Handling files
The following program will read out the input file, one character at a time and print it out to the console.


```c
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s <filename.txt>\n", argv[0]);
    return 1;
  }
   
  FILE *fptr;
  char c;

  fptr = fopen(argv[1], "rt");
  if (fptr == NULL) {
    fprintf(stderr, "failed to open file: %s\n", argv[1]);
    return 1;
  }

  while ((c = fgetc(fptr)) != EOF) {
    printf("%c", c);
  }

  fclose(fptr);
  return 0;
}
```

`EOF` stands for End of File. It is a symbolic constant defined inside `<stdio.h>` with the Integer value of `-1`.


---

#### Get Code Information

```c
/* print line number */
printf("%d\n", __LINE__);

/* print file name */
printf("%s\n", __FILE__);
```


---

#### Pointer arithmetic

```c
#include <stdio.h>

int main() {
    int a;
    int *b, *c;
    
    a = 100;
    b = &a;
    c = b + 1;
    
    printf("a: %d, *a: %p \n", a, &a);
    printf("b: %p, *b: %d \n", b, *b);
    printf("c: %p, *c: %d \n", c, *c);
    printf("Sizeof Int: %d \n", sizeof(int));

    return 0;
}

/* output: 
 * a: 100, *a: 0x738e4269bfcc 
 * b: 0x738e4269bfcc, *b: 100            Hexadecimal: 127054836776908
 * c: 0x738e4269bfd0, *c: 0              Hexadecimal: 127054836776912
 * Sizeof Int: 4 
*/
```

Every Byte in memory has a unique address. On Linux / Unix systems these addresses are represented as Hexadecimal Numbers.

Different amounts of space are allocated by the compiler to different data types. E.g. Int takes up 4 Bytes and Char takes up 1 Byte etc.

When we get a pointer to a variable, it points to the address of the starting byte of the variable. E.g. address of an int* is 200 this means that the value of the int is stored on memory addresses 200-203 i.e. 4 Bytes.

In the above example, both b and c are int* pointers. When we increment pointer to b, we get the memory address 4 Bytes ahead of the memory address of *b. This is because Int takes up 4 Bytes in memory.


##### Looping through arrays using Pointer Arithmetic

```c
#include <stdio.h>

int main()
{
    int a[] = {1,2,3,4};

    printf("first element: %d\n", *a);
    printf("second element: %d\n", *(a+1));
    printf("third element: %d\n", *(a+2));
    
    return 0;
}

/*
first element: 1
second element: 2
third element: 3
*/
```

Remember the following 

```c
*(a + 1) == a[i]
(a + 1) == &a[i]
```


---

#### Character arrays

```c
#include <stdio.h>

int main()
{
    char* copy;
    char msg[50] = "Jim is a good actor";
    
    copy = msg;
    printf("msg: %s\n", copy);
    
    copy[0] = 'K';
    printf("msg: %s\n", copy);
    
    return 0;
}
```

In C / C++ double quotations represent string literals. They are nothing but character arrays ending with a Null Termination Character i.e. \0. The name of the Character Array is of type char* and points to the memory address of the first character in the array. 

You may be wondering how `printf` figured out the size of the character array when we didn’t pass it explicitly. Here’s how.

```c
#include <stdio.h>

void print(char*);

int main() {
    char msg[50] = "Jim is a good actor";
    print(msg);
    
    return 0;
}

void print(char* string) {
    int i = 0;
    
    // look for the null termination character
    while(string[i] != '\0')
    {
        printf("%c", string[i]);
        i++;
    }
}
```


---

#### Elaborate example 

```c
#include <stdint.h>
#include <stdio.h>

typedef enum {
  Admin,
  Client,
} UserRole;

void userrole_tostring(const UserRole userrole, char *buffer) {
  sprintf(buffer, "%s", userrole == Admin ? "Admin" : "Client");
}

typedef struct {
  uint32_t id;
  const char *email;
  UserRole role;
} User;

void user_tostring(const User *user, char *buffer) {
  char roleBuf[100];
  userrole_tostring(user->role, roleBuf);
  sprintf(buffer, "User(id=%d, email=%s, role=%s)", user->id, user->email,
          roleBuf);
}

int main() {
  User user = {.id = 10, .email = "admin@site.com", .role = Admin};

  char buf[100];
  user_tostring(&user, buf);

  printf("%s\n", buf);
  return 0;
}
```
