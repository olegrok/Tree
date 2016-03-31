#include <stdlib.h>
#include <stdio.h>

#include "stack.h"
#include "tree.h"
typedef struct Stack Stack;

/*
typedef
struct list{
  void* value;
  struct list* right;
  struct list* left;
} list;
*/

list* leftTreeList(list* l);
list* list_create(void* data);
Tree* tree_create(int (*compar)(void *, void *));
int list_insert(int (*compar)(void *,void *), list** startList, list* newList);
int tree_insert(Tree* tree, void* data);
int list_deepFirst(list* list, void*(*func)(void*, void*), void* userVarible);
int list_remove(list* l);
int for_each(Tree* tree, void*(*func)(void*, void*), void* userVarible);
list* leftTreeList(list* l);
int branch_destroy(list* l, int flag);
int tree_destroy(Tree* tree, int flag);



list* list_create(void* data)
{
  list* new_list = calloc(sizeof(list), 1);
  new_list->value = data;
  new_list->left = NULL;
  new_list->right = NULL;
  return new_list;
}

Tree* tree_create(int (*compar)(void *, void *))
{
  Tree* newTree = calloc(sizeof(Tree), 1);
  newTree->compar = compar;
  newTree->head = NULL;
  return newTree;
}

int list_insert(int (*compar)(void *,void *), list** startList, list* newList)
{
  if(*startList == NULL){
      (*startList) = newList;
      return 0;
    }
  if(compar((*startList)->value, newList->value) == -1){
      return list_insert(compar, &((*startList)->left), newList);
    }
  else
    if(compar((*startList)->value, newList->value) == 0)
      {
        free(newList);
        return 0;
      }
    return list_insert(compar, &((*startList)->right), newList);
}

int tree_insert(Tree* tree, void* data)
{
  list* newList = list_create(data);
  list_insert(tree->compar, &(tree->head), newList);
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

int list_remove(list* l)
{
  if(l == NULL)
    return -1;
  list* new_list = 0;
  if(l->right){
    new_list = leftTreeList(l->right);

  }
}

int for_each(Tree* tree, void*(*func)(void*, void*), void* userVarible)
{
  list_deepFirst(tree->head, func, userVarible);
  return 0;
}

list* leftTreeList(list* l)
{
  if(l->left == NULL)
    return l;
  else
  {
    leftTreeList(l->left);
    if(l->left->left == NULL)
    {
        l->left = NULL;
    }
  }
}

int branch_destroy(list* l, int flag)
{
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
    branch_destroy(tree->head, flag);
    free(tree);
    return 0;
}
