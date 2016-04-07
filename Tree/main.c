#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int mycmp(void* first, void* second)
{
  if(*(int*)first > *(int*)second)
    return 1;
  if(*(int*)first == *(int*)second)
    return 0;
  return -1;
}

void* print(void* argument, void* useless)
{
    printf("%d ", *(int*)argument);
    return NULL;
}

#define N 15

int main(){
  Tree* myTree = tree_create(mycmp);
  int arr[N] = {0};
  int i = 0;
  for(i = 0; i < N; i++){
    arr[i] = rand() % 12;
    printf("[%d] = %d [%p]\n", i, arr[i], &arr[i]);
  }
  printf("\n\n");
  for(i = 0; i < N; i++){
    tree_insert(myTree, (arr + i));
  }

  forwIter* it = iter_begin(myTree);
  printf("%d\n", *(int*)iter_get(it));
  iter_next(it);
  while(!iter_cmp(it, iter_end(myTree))){
    printf("%d\n", *(int*)iter_get(it));
    iter_next(it);
  }


  /*(*num) = 3;
  void *p = num;
  tree_insert(myTree, p);
  for_each(myTree, print, (void*)&i);
  list* head = myTree->head;
  printf("head: %p\t head->prev: %p\n", head, head->prev);
  printf("head->left = %p\t head->right = %p\n", head->left, head->right);
  printf("head->left->prev = %p\t head->right->prev = %p\n", head->left->prev, head->right->prev);
  list_remove(head->left, myTree);
  for_each(myTree, print, (void*)&i);
  printf("\n");

  head = myTree->head;
  //printf("head: %p\t head->prev: %p\n", head, head->prev);
  //printf("head->left = %p\t head->right = %p\n", head->left, head->right);
  //printf("head->left->prev = %p\t head->right->prev = %p\n", head->left->prev, head->right->prev);
  list_remove(head->right, myTree);
  for_each(myTree, print, (void*)&i);
  printf("\n");

  head = myTree->head;

  do {
    if(head){
      printf("head: %p\t head->prev: %p\n", head, head->prev);
    }
    else
      break;
    if(head->left)
      printf("head->left = %p\t head->right = %p\n", head->left, head->right);
    if(head->right && head->left)
      printf("head->left->prev = %p\t head->right->prev = %p\n", head->left->prev, head->right->prev);
    for_each(myTree, print, (void*)&i);
    printf("\n");
  }
  while(list_remove(head, myTree) != -1);
  while(list_remove(head->right, myTree) != -1);
  for_each(myTree, print, (void*)&i);
  printf("\n");

  tree_destroy(myTree, 0);

  free(p);*/
  return 0;
}
