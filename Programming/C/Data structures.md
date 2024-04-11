
### Stack

#### Fix-sized stack

```cpp
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
  assert(stack_size(&s) == 5);

  assert(stack_peek(&s) == 50);
  assert(stack_peek(&s) == 50);
  assert(stack_size(&s) == 5);

  return 0;
}
```


---

#### Queue

```cpp
#include <assert.h>
#include <stdio.h>

#define MAX_QUEUE_SIZE 5

typedef struct {
  int items[MAX_QUEUE_SIZE];
  int count;
} Queue;

Queue queue_new() {
  return (Queue){
      .count = 0,
      .items = {},
  };
}

void queue_enqueue(Queue *q, int item) {
  assert(q->count < MAX_QUEUE_SIZE);
  q->items[q->count] = item;
  q->count++;
}

void shift_array_items(int items[], int size) {
  assert(size > 2);
  int i;
  for (i = 1; i < size; i++) {
    items[i - 1] = items[i];
  }
}

int queue_dequeu(Queue *q) {
  assert(q->count != 0);
  int first = q->items[0];
  shift_array_items(q->items, q->count);
  q->count--;
  return first;
}

int queue_peek(Queue *q) {
  assert(q->count != 0);
  return q->items[0];
}

int queue_is_empty(const Queue *q) { return q->count == 0; }
int queue_is_full(const Queue *q) { return q->count == MAX_QUEUE_SIZE; }

int main() {
  Queue q = queue_new();

  assert(queue_is_empty(&q) == 1);
  queue_enqueue(&q, 10);
  queue_enqueue(&q, 20);
  queue_enqueue(&q, 30);
  queue_enqueue(&q, 40);
  queue_enqueue(&q, 50);

  assert(queue_is_full(&q) == 1);
  assert(queue_peek(&q) == 10);
  assert(queue_peek(&q) == 10);

  assert(queue_dequeu(&q) == 10);
  assert(queue_dequeu(&q) == 20);
  assert(queue_peek(&q) == 30);

  printf("-- success --\n");
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