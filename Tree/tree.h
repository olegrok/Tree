#ifndef TREE_H
#define TREE_H
#include "stack.h"

#ifdef __cplusplus
extern "C" {
#endif

//application - dictionary or sort

typedef
struct list{
  void* value;
  struct list* prev;
  struct list* right;
  struct list* left;
} list;

typedef
struct Tree{
  list* head;
  int (*compar)(void *, void *);   //1 (1>2); 0 (1=2) -> nothing; -1 (1 < 2) -> left
} Tree;

typedef
struct forward_iterator{
  void* object;
  void* elem;
  Stack* stk;
} forwIter;

typedef
struct backward_iterator{
  void* object;
  void* elem;
  Stack* stk;
} backIter;

list* leftTreeList(list* l);
Tree* tree_create(int (*compar)(void *, void *));
int tree_insert(Tree* tree, void* data);
int list_deepFirst(list* list, void*(*func)(void*, void*), void* userVarible);
int list_remove(list* l);
int for_each(Tree* tree, void*(*func)(void*, void*), void* userVarible);
list* leftTreeList(list* l);
int branch_destroy(list* l, int flag);
int tree_destroy(Tree* tree, int flag);

#ifdef __cplusplus
}
#endif
#endif
