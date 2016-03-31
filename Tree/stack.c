#include <stdlib.h>
#include <stdio.h>

typedef
struct Stack {
    int n;
    int size;
    void** a;
} Stack;

struct Stack * stack_create(int size)
{
    struct Stack * stk;
    stk = (struct Stack *)calloc(1, sizeof(struct Stack));
    stk -> n = 0;
    stk -> size = size;
    stk -> a = calloc(size, sizeof(void*));
    return stk;
}
void stack_push(struct Stack * s, void* x)
{
    if(s -> size == s -> n)
    {
        s -> size++;
        s -> a = realloc(s -> a, (s -> size) * sizeof(s -> a[0]) * 2);
    }
    s -> a[s -> n] = x;
    s -> n++;
}
void* stack_pop(struct Stack * s)
{
    if(!s -> n)
        return NULL;
    return s -> a[--s -> n];
}
void* stack_get(struct Stack * s)
{
    return s -> a[s -> n];
}
/*void stack_print(struct Stack * s)
{
    int i = 0;
    if(s -> n == 0)
        {
            printf("Empty stack");
        }
    for(i = 0; i < s -> n; i++)
        printf("%p ", s -> a[i]);
    printf("\n");
}
void stack_clear(struct Stack * s)
{
    int i = 0;
    for(i = 0; i < s -> n; i++)
        s -> a[i] = 0;
}*/
int stack_is_empty(struct Stack * s)
{
    if(s -> n)
        return 0;
    return 1;
}
int stack_size(struct Stack * s)
{
    return s -> n;
}
void stack_destroy(struct Stack * s)
{
    free(s -> a);
    s -> n = 0;
    s -> size = 0;
    free(s);
}
/*
int main()
{
    struct Stack * sp = stack_create(1);
    int x = 0;
    int i = 0;
    int n = 300001;
    for(i = 0; i < n; i++)
        stack_push(sp, i);
    for(i = 0; i < n; i++)
        stack_pop(sp);
stack_push(sp, 5);
stack_push(sp, 19);
stack_push(sp, -2);
stack_print(sp);
// 5 19 -2

stack_push(sp, 27);
stack_print(sp);
// 5 19 -2 27
printf("is_empty=%d\n", stack_is_empty(sp));
// is_empty=0

x = stack_pop(sp);
printf("x=%d\n", x);
// x=27

x = stack_pop(sp);
printf("x=%d\n", x);
// x=-2

stack_print(sp);
// 5 19

printf("%d\n", stack_size(sp));
printf("%d\n", stack_size(sp));
printf("%d\n", stack_size(sp));
printf("%d\n", stack_size(sp));
printf("x=%d\n", stack_pop(sp));
printf("x=%d\n", stack_pop(sp));
printf("x=%d\n", stack_pop(sp));
printf("x=%d\n", stack_pop(sp));
printf("%d\n", stack_size(sp));
printf("%d\n", sp -> size);
stack_print(sp);
stack_push(sp, 19);
stack_push(sp, 19);
stack_push(sp, 19);
stack_push(sp, 19);
stack_push(sp, 19);
stack_print(sp);

stack_destroy(sp);

return 0;
}*/
