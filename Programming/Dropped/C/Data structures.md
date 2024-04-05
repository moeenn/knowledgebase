
### Stack

#### Fix-sized stack

```c
#include <assert.h>
#include <stdio.h>

#define MAX_STACK_SIZE 5

typedef struct {
  int cursor;
  int items[MAX_STACK_SIZE];
} Stack;

void stack_init(Stack *s) { s->cursor = 0; }

void stack_push(Stack *s, int item) {
  assert(s->cursor < MAX_STACK_SIZE);
  s->items[s->cursor] = item;
  s->cursor++;
}

int stack_pop(Stack *s) {
  assert(s->cursor != 0);
  int item = s->items[s->cursor - 1];
  s->cursor--;
  return item;
}

int stack_peek(Stack *s) {
  assert(s->cursor != 0);
  int item = s->items[s->cursor - 1];
  return item;
}

int stack_size(Stack *s) { return s->cursor; }
int stack_is_empty(Stack *s) { return s->cursor == 0; }

int main() {
  Stack s;
  stack_init(&s);
  assert(stack_is_empty(&s) == 1);

  stack_push(&s, 10);
  stack_push(&s, 20);

  stack_push(&s, 30);
  stack_push(&s, 40);
  stack_push(&s, 50);
  assert(s.cursor == 5);

  assert(stack_peek(&s) == 50);
  assert(stack_peek(&s) == 50);
  assert(stack_size(&s) == 5);

  return 0;
}
```


---

#### To-do

- [ ] Dynamic stack
- [ ] Stack using linked-list
	- [ ] Tower of Hanoi
	- [ ] N-Queens problem
	- [ ] Infix to prefix problem
- [ ] Queue
- [ ] Vector
- [ ] Linked-list
- [ ] Graph
- [ ] Hash-map
- [ ] Table
- [ ] Tree