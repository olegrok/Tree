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
    printf("%d\n", *(int*)argument);
    return NULL;
}

forwIter* iter_forwardRoot(Tree *tree){
  forwIter* iter = calloc(1, sizeof(forwIter));
  iter->object = (void*)tree;
  iter->stk = stack_create(1);
  iter->elem = (void*)tree->head;
}

#define N 15

int main(){
  Tree* myTree = tree_create(mycmp);
  int arr[N] = {0};
  int i = 0;
  for(i = 0; i < N; i++){
    arr[i] = rand() % 12;
    printf("[%p] = %d\n", &arr[i], arr[i]);
  }
  printf("\n\n");
  for(i = 0; i < N; i++){
    tree_insert(myTree, (arr + i));
  }
  for_each(myTree, print, (void*)&i);
  tree_destroy(myTree, 0);
  return 0;
}
