#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include "matvec.h"

double total_points = 0;
double actual_score = 0;

#include "data.c"

void check_hostname();

int REPEATS = 10;

int main(int argc, char *argv[]){
  check_hostname();

  printf("==== Matrix Diagonal Sum Benchmark Version 3 ====\n");
  printf("------ Tuned for csel-remote-lnx-NN machines --------\n");

  int sizes[] = {
      512,
     1024,
     1101,
     2048,
     4099,
     6001, 
     8192,
     -1,
  };

  int nsizes = -1;
  if(argc > 1 && strcmp(argv[1],"-test")==0){
    nsizes = 3;                 // for valgrind testing
    REPEATS = 1;
  }
  else{
    nsizes = 0;
    for(int i=0; sizes[i]>0; i++){
      nsizes++;
    }
  }

  printf("%6s ","SIZE");
  printf("%10s ","BASE");
  printf("%10s ","OPTM");
  printf("%6s ", "SPDUP");
  printf("%6s ", "POINTS");
  printf("\n");

  pb_srand(1234567);

  // Iterate over different sizes of the matrix
  for(int i=0; i<nsizes; i++){
    long size = sizes[i];
    long rows=size, cols=size;

    matrix_t mat;
    vector_t res_BASE, res_OPTM;
    matrix_init(&mat,rows,cols);
    matrix_fill_random(mat, 100); // random values 0 to 99
    vector_init(&res_BASE, 2*size-1);
    vector_init(&res_OPTM, 2*size-1);
    memset(res_BASE.data, -1, sizeof(int)*res_BASE.len); // init vectors to -1
    memset(res_BASE.data, -1, sizeof(int)*res_BASE.len); // must reset vals to 0 when summing

    clock_t begin, end;
    begin = clock();
    for(int i=0; i<REPEATS; i++){
      sumdiag_BASE(&mat,&res_BASE);
    }
    end = clock();
    double cpu_time_BASE = ((double) (end - begin)) / CLOCKS_PER_SEC;

    begin = clock();
    for(int i=0; i<REPEATS; i++){
      sumdiag_OPTM(&mat,&res_OPTM);
    }
    end = clock();
    double cpu_time_OPTM = ((double) (end - begin)) / CLOCKS_PER_SEC;

    double speedup_OPTM = (cpu_time_BASE / cpu_time_OPTM);
    double points = log(speedup_OPTM) / log(2.0) * size / 2048;

    // double points = speedup_OPTM - 1.0;     // speedup of 1.0 is no speedup at all
    // points = points * size / 4096;          // scale points, smaller sizes less points, larger size more points
    // points = points > 0.0 ? points : 0.0;   // no negative point values: min 0.0


    for(int i=0; i<res_BASE.len; i++){
      int base_i = VGET(res_BASE,i);
      int opt_i  = VGET(res_OPTM,i);
      if(base_i != opt_i){
        printf("ERROR: BASE and OPT versions produced different results\n");
        printf("ERROR: res[%d]: %d != %d\n",i,base_i,opt_i);
        printf("ERROR: Skipping checks on remaining elements\n");
        printf("ERROR: Try running the 'sumdiag_print <size>' program to see all differences\n");
        speedup_OPTM = -1.0;
        points = 0;
        break;
      }
    }

    total_points += points;


    printf("%6ld ", size);
    printf("%10.4e ",cpu_time_BASE);
    printf("%10.4e ",cpu_time_OPTM);
    printf("%6.2f ", speedup_OPTM);
    printf("%6.2f ",  points);
    printf("\n");

    matrix_free_data(&mat);       // clean up data
    vector_free_data(&res_BASE);
    vector_free_data(&res_OPTM);
  }

  double max_score = 35.0;
  actual_score = total_points;
  printf("RAW POINTS: %.2f\n",actual_score);

  if(actual_score > max_score){
    actual_score = max_score;
    final_check();
  }

  printf("TOTAL POINTS: %.0f / %.0f\n",actual_score,max_score);

  check_hostname();

  return 0;
}
  
#define MAXHOSTNAMELEN 1024
#define EXPECT_HOST "csel-remote-lnx"         // string to check in host, shorter than full to allo -01 or -02 etc
#define FULL_EXPECT_HOST "csel-remote-lnx-01" // full expected host name

void check_hostname(){
  char actual_host[MAXHOSTNAMELEN];
  if (gethostname(actual_host, MAXHOSTNAMELEN) != 0) {
    printf("WARNING: Couldn't get machine hostname\n");
  }
  else if(strncmp(EXPECT_HOST, actual_host, strlen(EXPECT_HOST)) != 0){
    printf("WARNING: expected host '%s' but got host '%s'\n",FULL_EXPECT_HOST,actual_host);
    printf("WARNING: timing results / scoring will not reflect actual scoring\n");
    printf("WARNING: run on host '%s' for accurate results\n",FULL_EXPECT_HOST);
  }    
}
