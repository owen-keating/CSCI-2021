// more_macros.c: Demonstrates the difference between a funciton call
// and a Macro. "Compile" using the following to see the output of the
// preprocessor phase of compilation
//
// > gcc -E more_macros.c > output.c
//
//  Examine the code in output.c and compare it to the original.

#include <stdio.h>

#define ACONST 15

int compute_fun(int a, int b, int c){
  return a*b+c;
}

#define COMPUTE_MAC(a,b,c) ((a)*(b)+(c))

int main(int argc, char *argv[]){

  int a = ACONST;
  printf("a: %d  ACONST: %d\n",
         a, ACONST);

  int xf = compute_fun(1,2,3);
  int xm = COMPUTE_MAC(1,2,3);

  printf("xf: %d  xm: %d",xf,xm);
  
  int yf = compute_fun( 1+2, 3+4+5, 6+7 );
  int ym = COMPUTE_MAC( 1+2, 3+4+5, 6+7 );

  printf("yf: %d  ym: %d\n",yf,ym);

  printf("File '%s' Line: %d\n", __FILE__, __LINE__);

  return 0;
}
