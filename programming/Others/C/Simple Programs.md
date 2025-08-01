#### Users 

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


---

#### Game entities

```c
#include <stdio.h>

typedef enum {
  DIRECTION_UP,
  DIRECTION_DOWN,
  DIRECTION_LEFT,
  DIRECTION_RIGHT
} Direction;

typedef struct {
  int x;
  int y;
} Position;

Position position_origin() {
  Position p = {.x = 0, .y = 0};
  return p;
}

typedef struct {
  const char *name;
  Position position;
  int step;
} Entity;

Entity entity_new(const char *name, int step) {
  Entity e = {
      .name = name,
      .position = position_origin(),
      .step = 10,
  };
  return e;
}

void entity_move(Entity *e, Direction d) {
  switch (d) {
  case DIRECTION_UP:
    e->position.y += e->step;
    break;

  case DIRECTION_DOWN:
    e->position.y -= e->step;
    break;

  case DIRECTION_LEFT:
    e->position.x -= e->step;
    break;

  case DIRECTION_RIGHT:
    e->position.x += e->step;
    break;
  }
}

void entity_debug(const Entity *e) {
  printf("Entity(name='%s', position=(%d, %d))\n", e->name, e->position.x,
         e->position.y);
}

int main() {
  Entity e_one = entity_new("Entity one", 10);
  entity_move(&e_one, DIRECTION_RIGHT);
  entity_move(&e_one, DIRECTION_DOWN);
  entity_move(&e_one, DIRECTION_DOWN);

  entity_debug(&e_one);
  return 0;
}
```


---


#### Validating C syntax

```c
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "error: please provide an input file\n");
    return 1;
  }

  /** strcmp is backwards: 0 means both strings are equal */
  if (strcmp(argv[1], "-h") == 0) {
    printf("usage: %s <file>\n", argv[0]);
    return 0;
  }

  FILE *file_ptr;
  char c;
  int curly_open, round_open, square_open, angle_open, str_open, char_open;

  curly_open = 0;
  round_open = 0;
  square_open = 0;
  angle_open = 0;
  str_open = 0;
  char_open = 0;

  file_ptr = fopen(argv[1], "rt");
  if (NULL == file_ptr) {
    fprintf(stderr, "error: failed to open file\n");
    return 1;
  }

  do {
    c = getc(file_ptr);

    switch (c) {
    case '{':
      curly_open++;
      break;

    case '}':
      curly_open--;
      break;

    case '(':
      round_open++;
      break;

    case ')':
      round_open--;
      break;

    case '[':
      square_open++;
      break;

    case ']':
      square_open--;
      break;

    case '<':
      angle_open++;
      break;

    case '>':
      angle_open--;
      break;

    case '"':
      str_open++;
      break;

    case '\'':
      char_open++;
      break;
    }
  } while (c != EOF);

  fclose(file_ptr);

  if (curly_open != 0 || round_open != 0 || square_open != 0 ||
      angle_open != 0 || str_open % 2 == 1 || char_open % 2 == 1) {
    fprintf(stderr, "error: invalid file syntax\n");
    return 1;
  }

  printf("ok: syntax\n");
  return 0;
}
```

**Note**: This program assumes that input files are plain text files and don't contain Unicode / wide characters. If the program encounters such a character, it won't fit inside `char c` and the program will segfault. 