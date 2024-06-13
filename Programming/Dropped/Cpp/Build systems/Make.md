#### Project structure
```
src/
  main.cpp
bin/
Makefile
.gitignore
```

```Makefile
PROJECT = sandbox

CC = clang++
SRC_DIR =./src
SRC = $(wildcard ${SRC_DIR}/*.cpp)
OUT_DIR = bin
OBJ = ${SRC:.cpp=.o}
LIBS = 
CFLAGS = -Wextra -Werror -Wall -std=c++20 -Wc++20-extensions
BINARY = ${OUT_DIR}/${PROJECT}

main: ${OBJ}
	${CC} -o ${BINARY} ${OUT_DIR}/*.o ${LIBS}

.cpp.o:
	${CC} -c ${CFLAGS} $<
	@mkdir -p ${OUT_DIR}
	@mv ./*.o ${OUT_DIR}/

run:
	@${BINARY}

build:
	@bear -- make

clean:
	@rm -v ./compile_commands.json
	@rm -v ${OUT_DIR}/*.o ${BINARY}
```

```gitignore
bin/*
*.o
.cache
compile_commands.json
```
