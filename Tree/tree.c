#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
typedef struct Stack Stack;
typedef struct methods Met;
extern Met TMet;

typedef
struct Tree{
  struct list* head;
  int (*compar)(void *, void *);   //1 (1>2); 0 (1=2) -> nothing; -1 (1 < 2) -> left
} Tree;

typedef
struct list{
  void* value;
  struct list* prev;
  struct list* right;
  struct list* left;
} list;

typedef
struct forward_iterator{
  void* object;
  void* elem;
  Stack* stk;
  Met* m;
} forwIter;

typedef
struct backward_iterator{
  void* object;
  void* elem;
  Stack* stk;
  Met* M;
} backIter;


list* leftTreeList(list* l);
list* list_create(void* data);
Tree* tree_create(int (*compar)(void *, void *));
int list_insert(int (*compar)(void *,void *), list** startList, list* newList, list** prev);
int tree_insert(Tree* tree, void* data);
int list_deepFirst(list* list, void*(*func)(void*, void*), void* userVarible);
int list_remove(list* l, Tree* tree);
int for_each(Tree* tree, void*(*func)(void*, void*), void* userVarible);
list* leftTreeList(list* l);
int branch_destroy(list* l, int flag);
int tree_destroy(Tree* tree, int flag);


list* list_create(void* data)
{
  list* newList = calloc(sizeof(list), 1);
  newList->value = data;
  newList->left = NULL;
  newList->right = NULL;
  newList->prev = NULL;
  return newList;
}

Tree* tree_create(int (*compar)(void *, void *))
{
  Tree* newTree = calloc(sizeof(Tree), 1);
  newTree->compar = compar;
  newTree->head = NULL;
  return newTree;
}

int list_insert(int (*compar)(void *,void *), list** startList, list* newList, list** prev)
{
  if(*startList == NULL){
      (*startList) = newList;
      newList->prev = *prev;
      return 0;
    }
  (*prev) = (*startList);
  if(compar((*startList)->value, newList->value) == -1){
      return list_insert(compar, &((*startList)->left), newList, prev);
    }
  else
    if(compar((*startList)->value, newList->value) == 0)
      {
        free(newList);
        return 0;
      }
    return list_insert(compar, &((*startList)->right), newList, prev);
}

int tree_insert(Tree* tree, void* data)
{
  list* newList = list_create(data);
  list* prev = NULL;
  list_insert(tree->compar, &(tree->head), newList, &prev);
  return 0;
}

int list_deepFirst(list* list, void*(*func)(void*, void*), void* userVarible){
    if(!list)
      return 0;
    if(list->right){
      list_deepFirst(list->right, func, userVarible);
    }
    func(list->value, userVarible);
    if(list->left)
      list_deepFirst(list->left, func, userVarible);
    return 0;
}

int list_remove(list* l, Tree* tree)
{
  if(l == NULL)
    return -1;
  list* newList = 0;

  if(l->prev == NULL)
      return -1;
//    return remove_head(tree);

  if(l->left && !(l->right)){
    newList = l->left;
  }

  if(l->right && !(l->left)){
    newList = l->right;
  }

  if(l->left && l->right){
    newList = leftTreeList(l->right);
    l->value = newList->value;
    list_remove(newList, tree);
    return 0;
  }

  if(l->prev){
    if(l->prev->left == l)
      l->prev->left = newList;
    else
      l->prev->right = newList;
  }

  printf("remove: list->value  = %d\n", *(int*)(l->value));
  if(newList)
    newList->prev = l->prev;

  free(l);
  return 0;
}

int for_each(Tree* tree, void*(*func)(void*, void*), void* userVarible)
{
  if(!tree)
    return -1;
  list_deepFirst(tree->head, func, userVarible);
  return 0;
}

list* leftTreeList(list* l)
{
  if(l->left == NULL)
    return l;
  return leftTreeList(l->left);
}

int branch_destroy(list* l, int flag)
{
  if(l == NULL)
    return -1;
  if(l->right)
    branch_destroy(l->right, flag);
  if(l->left)
    branch_destroy(l->left, flag);
  if(flag)
    free(l->value);
  free(l);
  return 0;
}

int tree_destroy(Tree* tree, int flag)
{
  if(tree == NULL)
    return -1;
  if(tree->head)
    branch_destroy(tree->head, flag);
  free(tree);
  return 0;
}


forwIter* iter_begin(Tree *tree){
  forwIter* iter = calloc(1, sizeof(forwIter));
  iter->object = (void*)tree;
  iter->stk = stack_create(1);
  iter->elem = (void*)tree->head;
  iter->m = &TMet;
  return iter;
}

forwIter* iter_end(Tree *tree){
  forwIter* iter = calloc(1, sizeof(forwIter));
  iter->object =(void*)tree;
  iter->stk = stack_create(1);
  iter->elem = NULL;
  iter->m = &TMet;
  return iter;
}

int iter_cmp(forwIter* it1, forwIter* it2)
{
  if(it1->elem == it2->elem && it1->object == it2->object)
    return 1;
  return 0;
}

int iter_next(forwIter *it)
{
  if(it == NULL || it->elem == NULL)
    return -1;
  list* l = it->elem;
  if(l->right)
    stack_push(it->stk, l->right);
  if(l->left)
    it->elem = (void*)(l->left);
  else
    if(!stack_is_empty(it->stk))
      it->elem = stack_pop(it->stk);
    else
      it->elem = NULL;
  return 0;
}

int iter_destroy(forwIter *it){
  if(!it)
    return -1;
  stack_destroy(it->stk);
  free(it);
  return 0;
}

void* iter_get(forwIter *it){
  if(!it || !it->elem)
    return NULL;
  list* l = it->elem;
  return l->value;
}

int iter_remove(forwIter *it){
  if(!it || !it->elem || !it->object)
    return -1;
  list_remove(it->object, it->elem);
  return 0;
}
