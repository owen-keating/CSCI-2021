#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct to hold pointers and info on algorithms for timing
typedef struct{
  void (*alg_func)(unsigned long iters, unsigned long *start, unsigned long *delta);
  // ^^ nutty declaration of a function pointer
  char *name;                   // name of algorithm
  char *description;            // description of alg
} alg_t;

extern alg_t algs[];

void print_usage(char *prog_name){
  printf("usage: %s <MULT> <EXP> <ALG>\n",prog_name);
  printf("  <MULT> and <ALG> are integers, iterates for MULT * 2^{EXP} iterations\n");
  printf("  <ALG> is one of\n");
  for(int i=0; algs[i].alg_func != NULL; i++){
    printf("%18s : %s\n",algs[i].name,algs[i].description);
  }
}  

int main(int argc, char *argv[]){
  if(argc < 4){
    print_usage(argv[0]);
    return 1;
  }

  unsigned long mult = atol(argv[1]);
  unsigned long exp  = atol(argv[2]);
  char *alg_name = argv[3];

  // Function pointer associated with alg
  void (*alg_func)(unsigned long iters, unsigned long *start, unsigned long *delta);
  alg_func = NULL;

  // select algorithm to use
  for(int i=0; algs[i].alg_func != NULL; i++){
    if(strcmp(alg_name, algs[i].name) == 0){
      alg_func = algs[i].alg_func;
    }
  }
  if(alg_func == NULL){
    printf("Unknown algorithm '%s'\n",alg_name);
    print_usage(argv[0]);
    return 1;
  }

  // determine number of iterations
  unsigned long one  = 1;                    // bothersome but necessary
  unsigned long iters = mult * (one << exp); // exponentiate 2 with a shift

  unsigned long start = 0;
  unsigned long delta = 3;

  printf("%s for %lu * 2^{%lu} = %lu iterations... ",alg_name,mult,exp,iters);
  fflush(stdout);
  alg_func(iters, &start, &delta);         // run the specified algorithm
  printf("complete\n");

  return 0;
}
