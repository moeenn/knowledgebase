```
bin/
src/
	main.c
Makefile
.gitignore
```

```Makefile
PROJECT = sandbox

CC = clang
SRC_DIR =./src
SRC = $(wildcard ${SRC_DIR}/*.c)
OUT_DIR = bin
OBJ = ${SRC:.c=.o}
LIBS =
CFLAGS = -std=c99 -pipe -Wno-unused -Wall -Wno-deprecated-declarations
BINARY = ${OUT_DIR}/${PROJECT}

main: ${OBJ}
	${CC} -o ${BINARY} ${OUT_DIR}/*.o ${LIBS}

.c.o:
	${CC} -c ${CFLAGS} $<
	@mv ./*.o ${OUT_DIR}/

run:
	@${BINARY}

clean:
	@rm -v ${OUT_DIR}/*.o ${BINARY}
```

```gitignore
bin/*
*.o
```

```c
#include <stdio.h>

int main() {
  printf("Hello world\n");
  return 0;
}
```

```bash
# compile
$ make 

# execute compiled binary
$ make run

# cleanup build objects and binary
$ make clean
```