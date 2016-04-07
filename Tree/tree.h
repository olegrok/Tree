#ifndef TREE_H
#define TREE_H
#include "stack.h"

#ifdef __cplusplus
extern "C" {
#endif

//application - dictionary or sort

typedef
struct Tree Tree;
typedef
struct forward_iterator forwIter;
typedef
struct backward_iterator backIter;

typedef
struct methods{
  int (*destroy) (forwIter *);
  forwIter* (*begin) (Tree *);
  forwIter* (*end) (Tree *);
  int (*iter_remove) (forwIter *);
  int  (*iter_next) (forwIter *);
  void *(*get) (forwIter*);
  int (*cmp)(forwIter*, forwIter*);
} Met;

Tree* tree_create(int (*compar)(void *, void *));
int tree_insert(Tree* tree, void* data);
int for_each(Tree* tree, void*(*func)(void*, void*), void* userVarible);
int tree_destroy(Tree* tree, int flag);

forwIter* iter_begin(Tree *tree);
forwIter* iter_end(Tree *tree);
int iter_cmp(forwIter* it1, forwIter* it2);
int iter_next(forwIter *it);
int iter_destroy(forwIter *it);
int iter_remove(forwIter *it);
void* iter_get(forwIter *it);

#ifdef __cplusplus
}
#endif
#endif
