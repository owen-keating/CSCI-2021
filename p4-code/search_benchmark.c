#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "search.h"

int main(int argc, char *argv[]){
  int la = 0, ll = 0, ba = 0, bt = 0;
  int minpow = atoi(argv[1]);
  int maxpow = atoi(argv[2]);
  int repeats = atoi(argv[3]);
  if(argc==4){ la = 1; ll = 1; ba = 1; bt = 1; }
  else{
    for(int i = 4; i<argc; i++){
      if(!strcmp(argv[i], "la")) la = 1;
      if(!strcmp(argv[i], "ll")) ll = 1;
      if(!strcmp(argv[i], "ba")) ba = 1;
      if(!strcmp(argv[i], "bt")) bt = 1;
    }
  }
  printf("    SIZE  NSEARCH");
  if(la) printf("      array");
  if(ll) printf("       list");
  if(ba) printf("     binary");
  if(bt) printf("       tree");
  printf("\n");
  for(int n = minpow; n<=maxpow; n++){
    int size = 1 << n;
    clock_t begin, end;
    int nsearch = size * repeats << 1;
    printf("  %6d   %6d", size, nsearch);
    if(la){
      int *array = make_evens_array(size);
      begin = clock();
      for(int i = 0; i<repeats; i++){
        for(int j = 0; j<=size; j++){
          linear_array_search(array, size, j);
        }
      }
      end = clock();
      double time = (double)(end-begin) / CLOCKS_PER_SEC;
      printf(" %10.4e", time);
      free(array);
    }
    if(ll){
      list_t *list = make_evens_list(size);
      begin = clock();
      for(int i = 0; i<repeats; i++){
        for(int j = 0; j<=size; j++){
          linkedlist_search(list, size, j);
        }
      }
      end = clock();
      double time = (double)(end-begin) / CLOCKS_PER_SEC;
      printf(" %10.4e", time);
      list_free(list);
    }
    if(ba){
      int *sorted = make_evens_array(size);
      begin = clock();
      for(int i = 0; i<repeats; i++){
        for(int j = 0; j<=size; j++){
          binary_array_search(sorted, size, j);
        }
      }
      end = clock();
      double time = (double)(end-begin) / CLOCKS_PER_SEC;
      printf(" %10.4e", time);
      free(sorted);
    }
    if(bt){
      bst_t *tree = make_evens_tree(size);
      begin = clock();
      for(int i = 0; i<repeats; i++){
        for(int j = 0; j<=size; j++){
          binary_tree_search(tree, 0, j);
        }
      }
      end = clock();
      double time = (double)(end-begin) / CLOCKS_PER_SEC;
      printf(" %10.4e", time);
      bst_free(tree);
    }
    printf("\n");
  }
  return 0;
}
