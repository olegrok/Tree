#ifndef STACK_H
#define STACK_H

struct Stack;
typedef struct Stack Stack;

struct Stack * stack_create(int size);
void stack_push(struct Stack * s, void* x);
void* stack_pop(struct Stack * s);
void* stack_get(struct Stack * s);
int stack_is_empty(struct Stack * s);
int stack_size(struct Stack * s);
void stack_destroy(struct Stack * s);

#endif
