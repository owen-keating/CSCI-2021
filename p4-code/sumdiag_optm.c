#include "matvec.h"

int sumdiag_OPTM(matrix_t *mat, vector_t *vec) {
  // introducing local variables for len, rows, cols
  int len = vec->len;
  int rows = mat->rows;
  int cols = mat->cols;
  // error for non-square matrix
  if(len != (rows + cols - 1)){
    printf("sumdiag_base: bad sizes\n");
    return 1;
  }
  // creating pointer variables for the matrix and vector data
  int *vdata = vec->data;
  int *mdata = mat->data;
  // clear the vector data; set all diagonal totals to zero
  for(int i=0; i<len; i++){
    vdata[i] = 0;
  }
  // traversing through the matrix data sequentially
  for(int i = 0; i<rows; i++){
    int x = i * cols;
    for(int j = 0; j<cols; j++){
      int adj = j - i - 1;
      vdata[cols+adj] += mdata[x+j];
    }
  }
  return 0;
}
