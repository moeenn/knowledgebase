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
