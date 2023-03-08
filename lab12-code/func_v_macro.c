// func_v_macro.c: demonstrate timing differences between using
// function calls and macros. The mget()/vset() functions and
// MGET()/VSET() macros behave the same but macros do not involve
// control jumps so lead to better efficiency without
// optimizations. Performing function inlining such as is done at gcc
// -O3 will lead to near identical performance as the bodies of the
// small functions will be inserted at their call sites just like the
// macros are. With minimal optimization such as -Og, one will observe
// timing differences between these versions.
// 
// Note: to see the results of the Preprocessor, compile via
// 
// > gcc -E func_v_macro.c > preprocessed.c
//
// and inspect the freshly created preprocessed.c file. The functions
// and main() code will be low down in the file the contents of many
// header files will be inserted above them.
// 
// Complete the TODO items to finish this file. Each item should only
// require 1 line of code to finish.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>               // for clock() and other functions
#include <stdio.h>
#include <sys/time.h>
#include "matvec.h"

// getter/setter FUNCTIONS working on POINTERS
int mgetp(matrix_t *mat, int i, int j){
  return mat->data[i*mat->cols + j];
}
int vsetp(vector_t *vec, int i, int x){
  return vec->data[i] = x;
}

// Version 1: pointers to structs with function calls
void row_sums_func_p(matrix_t *matp, vector_t *sumsp){
  for(int i=0; i<matp->rows; i++){
    int sum = 0;
    for(int j=0; j<matp->cols; j++){
      // TODO: FUNCTION call to get element from matrix POINTER, add on to sum
      sum += mgetp(matp,i,j);
    }
    // TODO: FUNCTION call to set element in vector POINTER to sum
    vsetp(sumsp, i, sum);
  }
}

// getter/setter FUNCTIONS working on STRUCTS
int mgets(matrix_t mat, int i, int j){
  return mat.data[i*mat.cols + j];
}
int vsets(vector_t vec, int i, int x){
  return vec.data[i] = x;
}

// Version 2: actual structs with function calls
void row_sums_func_s(matrix_t *matp, vector_t *sumsp){
  // dereference pointers to get local var copies of structs
  matrix_t mat = *matp;
  vector_t sums = *sumsp;
  for(int i=0; i<mat.rows; i++){
    int sum = 0;
    for(int j=0; j<mat.cols; j++){
      // TODO: FUNCTION call to get element from matrix STRUCT, add on to sum
      sum += mgets(mat,i,j);
    }
    // TODO: FUNCTION call to set element in vector STRUCT to sum
    vsets(sums, i, sum);
  }
}

// getter setter MACROS working on structs
#define MGET(mat,i,j) ((mat).data[((i)*((mat).cols)) + (j)])
#define VSET(vec,i,x) ((vec).data[(i)] = (x))

// Version 3: Macros with structs
void row_sums_macro(matrix_t *matp, vector_t *sumsp){
  matrix_t mat = *matp;
  vector_t sums = *sumsp;
  for(int i=0; i<mat.rows; i++){
    int sum = 0;
    for(int j=0; j<mat.cols; j++){
      // TODO: MACRO call to get element from matrix STRUCT, add on to sum
      sum += MGET(mat,i,j);
    }
    // TODO: MACRO call to set element in vector STRUCT to sum
    VSET(sums, i, sum);
  }
}

// Version 4: Macro version + unroll innermost loop by 4
void row_sums_unroll4(matrix_t *matp, vector_t *sumsp){
  matrix_t mat = *matp;
  vector_t sums = *sumsp;
  for(int i=0; i<mat.rows; i++){
    int sum0=0, sum1=0;
    // TODO: introduce additional local variables
    int sum2=0, sum3=0;

    // NOTE: j declared outside loop scope so it can be used across
    // several loops below
    int j;                      

    // NOTE: the loop iterations and bounds for unroll factor 4
    for(j=0; j<mat.cols-4; j+=4){
      sum0 += MGET(mat,i,j+0);
      sum1 += MGET(mat,i,j+1);
      // TODO: Complete arithmetic for unroll factor 4
      sum2 += MGET(mat,i,j+2);
      sum3 += MGET(mat,i,j+3);
    }

    // NOTE: "cleanup" loop in case array size is not divisible by the
    // unroll factor; start at last j position, increment by 1
    for(; j<mat.cols; j+=1){
      sum0 += MGET(mat,i,j+0);
    }

    // TODO: MACRO call to set element in vector STRUCT to sum of sums
    VSET(sums, i, (sum0+sum1+sum2+sum3));
  }
}

// Check that the values in both vectors are equal, report first difference
void check_vectors(vector_t expect, vector_t actual){
  for(int i=0; i<expect.len; i++){
    if(expect.data[i] != actual.data[i]){
      printf("[%d] expect %d != actual %d\n",
             i,expect.data[i],actual.data[i]);
      return;
    }
  }
}


#define REPEATS 50              // number of times to repeat the summing 

int main(int argc, char *argv[]){

  if(argc < 3){
    printf("usage: %s <rows> <cols> \n",argv[0]);
    return 1;
  }

  int rows = atoi(argv[1]);
  int cols = atoi(argv[2]);

  // Allocate the matrix and fill it in with 1,2,3,4...
  matrix_t mat;
  matrix_init(&mat, rows,cols);
  matrix_fill_sequential(mat);
  vector_t sums, sums_check;
  vector_init(&sums, mat.rows);
  vector_init(&sums_check, mat.rows);

  // Variables for timing
  clock_t begin, end;
  double cpu_time;

  // TIME version 1
  begin = clock();
  for(int i=0; i<REPEATS; i++){
    row_sums_func_p(&mat,&sums);
  }
  end = clock();
  cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("%10.4e secs : %s\n",cpu_time,"V1 row_sums_func_p");    

  // make copy of the answer to check later optimized versions
  memcpy(sums_check.data, sums.data, sizeof(int)*rows);

  // TIME version 2
  begin = clock();
  for(int i=0; i<REPEATS; i++){
    row_sums_func_s(&mat,&sums);
  }
  end = clock();
  cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("%10.4e secs : %s\n",cpu_time,"V2 row_sums_func_s");    

  check_vectors(sums_check, sums);

  // TIME version 3
  begin = clock();
  for(int i=0; i<REPEATS; i++){
    row_sums_macro(&mat,&sums);
  }
  end = clock();
  cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("%10.4e secs : %s\n",cpu_time,"V3 row_sums_macro");    

  check_vectors(sums_check, sums);

  // TIME version 4
  begin = clock();
  for(int i=0; i<REPEATS; i++){
    row_sums_unroll4(&mat,&sums);
  }
  end = clock();
  cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("%10.4e secs : %s\n",cpu_time,"V4 row_sums_unroll4");    

  check_vectors(sums_check, sums);

  matrix_free_data(&mat);
  vector_free_data(&sums);
  vector_free_data(&sums_check);

  return 0;
}
