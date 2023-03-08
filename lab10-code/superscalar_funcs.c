#include <stdlib.h>             // for NULL

// Loops involving ALU operations to demonstrate superscalar behavior

// only add
void add1_diff(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  unsigned long ret = *start;
  unsigned long inc = *delta;
  for(unsigned long i=0; i<iters; i++){
    ret += inc;
  }
  *start = ret;
}

// Add twice in a loop to different locations
void add2_diff(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  // Compiler tries to optimize away multiple adds; prevent this with
  // wonky constants
  unsigned long retA = *start;
  unsigned long retB = retA + 19;     // start a different spot
  unsigned long delA = *delta;
  unsigned long delB = delA * 3 + 17; // add a different update
  for(unsigned long i=0; i<iters; i++){ 
    retA += delA;
    retB += delB;
  }
  *start = retA+retB;
}

// Add twice in a loop to same location
void add2_same(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  unsigned long retA = *start;
  unsigned long delA = *delta;
  unsigned long delB = delA * 3 + 17; // add a different update
  for(unsigned long i=0; i<iters; i++){ 
    retA += delA;
    retA += delB;
  }
  *start = retA;
}

// Add three times in a loop to different locations
void add3_diff(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  // Compiler tries to optimize away multiple adds; prevent this with
  // wonky constants
  unsigned long retA = *start;
  unsigned long retB = retA + 19;     // start at different spots
  unsigned long retC = retB + 193;    
  unsigned long delA = *delta;
  unsigned long delB = delA * 3 + 17;   // add a different update
  unsigned long delC = delB * 632 - 19; // add a different update
  for(unsigned long i=0; i<iters; i++){ 
    retA += delA;
    retB += delB;
    retC += delC;
  }
  *start = retA+retB+retC;
}


// only multiply
void mul1_diff(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  unsigned long ret = *start;
  unsigned long mul = *delta;
  for(unsigned long i=0; i<iters; i++){
    ret *= mul;
  }
  *start = ret;
}

// multiply twice in a loop to different locations
void mul2_diff(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  // Compiler tries to optimize away multiple adds; prevent this with
  // wonky constants
  unsigned long retA = *start;
  unsigned long retB = retA + 19;     // start a different spot
  unsigned long delA = *delta;
  unsigned long delB = delA * 3 + 17; // add a different update
  for(unsigned long i=0; i<iters; i++){ 
    retA *= delA;
    retB *= delB;
  }
  *start = retA+retB;
}

// Multiply three times in a loop, different locations
void mul3_diff(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  // Compiler tries to optimize away multiple adds; prevent this with
  // wonky constants
  unsigned long retA = *start;
  unsigned long retB = retA + 19;     // start at different spots
  unsigned long retC = retB + 193;    
  unsigned long delA = *delta;
  unsigned long delB = delA * 3 + 17;   // add a different update
  unsigned long delC = delB * 632 - 19; // add a different update
  for(unsigned long i=0; i<iters; i++){ 
    retA *= delA;
    retB *= delB;
    retC *= delC;
  }
  *start = retA+retB+retC;
}

// Multiply four times in a loop, different locations
void mul4_diff(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  // Compiler tries to optimize away multiple adds; prevent this with
  // wonky constants
  unsigned long retA = *start;
  unsigned long retB = retA + 19;     // start at different spots
  unsigned long retC = retB + 193;    
  unsigned long retD = retC + 31;    
  unsigned long delA = *delta;
  unsigned long delB = delA * 3 + 17;   // add a different update
  unsigned long delC = delB * 632 - 19; // add a different update
  unsigned long delD = delC * 1113 - 37; // add a different update
  for(unsigned long i=0; i<iters; i++){ 
    retA *= delA;
    retB *= delB;
    retC *= delC;
    retD *= delD;
  }
  *start = retA+retB+retC+retD;
}

// multiply twice in a loop to same locations
void mul2_same(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  // Compiler tries to optimize away multiple adds; prevent this with
  // wonky constants
  unsigned long retA = *start;
  unsigned long delA = *delta;
  unsigned long delB = delA * 3 + 17; // add a different update
  for(unsigned long i=0; i<iters; i++){ 
    retA *= delA;
    retA *= delB;
  }
  *start = retA;
}

// Add and multiply to different destinations
void add2_and_mul_diff(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  unsigned long retA = *start;
  unsigned long retB = *start + 19;
  unsigned long retM = *start;
  unsigned long del = *delta;
  unsigned long delB = del * 3 + 17; // add a different update

  for(unsigned long i=0; i<iters; i++){
    retA += del;
    retM *= del;
    if(del <= 10000){           // force comparison and potential jump
      retB += delB;             // to be comparable to add1_then_mul_diff
    }
  }
  *start = retA+retB+retM;
}

// Add and multiply to the same destination
void add2_and_mul_same(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  unsigned long ret = *start;
  unsigned long del = *delta;
  unsigned long delB = del * 3 + 17; // add a different update
  for(unsigned long i=0; i<iters; i++){
    ret += del;
    ret *= del;
    if(del <= 10000){           // force comparison and potential jump  
      ret += delB;              // to be comparable to add1_then_mul_diff
    }
  }
  *start = ret;
}


// Add in a loop. Then multiply in a loop. Different destinations.
void add1_then_mul_diff(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  unsigned long retA = *start;
  unsigned long retM = *start;
  unsigned long del = *delta;
  for(unsigned long i=0; i<iters; i++){ // add first
    retA += del;
  }
  for(unsigned long i=0; i<iters; i++){ // then multiply
    retM *= del;
  }
  *start = retA+retM;
}


// Add in a loop. Then multiply in a loop. Same destinations.
void add1_then_mul_same(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  unsigned long ret = *start;
  unsigned long del = *delta;
  for(unsigned long i=0; i<iters; i++){ // add first
    ret += del;
  }
  for(unsigned long i=0; i<iters; i++){ // then multiply
    ret *= del;
  }
  *start = ret;
}


// struct to hold pointers and info on algorithms for timing
typedef struct{
  void (*alg_func)(unsigned long iters, unsigned long *start, unsigned long *delta);
  // ^^ nutty declaration of a function pointer
  char *name;                   // name of algorithm
  char *description;            // description of alg
} alg_t;

// array of descriptions and functions
alg_t algs[] = {
  // func name          string id            description
  {add1_diff,          "add1_diff",          "add 1 times in loop"},
  {add2_diff,          "add2_diff",          "add 2 times in same loop; different destinations"},            
  {add3_diff,          "add3_diff",          "add 3 times in same loop; different destinations"},            
  {add2_same,          "add2_same",          "add 2 times in same loop; same destinations"},                
  {mul1_diff,          "mul1_diff",          "multiply 1 times in loop"},
  {mul2_diff,          "mul2_diff",          "multiply 2 times in same loop; different destinations"},       
  {mul3_diff,          "mul3_diff",          "multiply 3 times in same loop; different destinations"},       
  {mul4_diff,          "mul4_diff",          "multiply 4 times in same loop; different destinations"},       
  {mul2_same,          "mul2_same",          "multiply 2 times in same loop; same destinations"},           
  {add1_then_mul_diff, "add1_then_mul_diff", "add and multiply in different loops; different destinations"}, 
  {add1_then_mul_same, "add1_then_mul_same", "add and multiply in different loops; same destinations"},     
  {add2_and_mul_diff,  "add2_and_mul_diff",  "add twice and multiply in the same loop; different destinations"},  
  {add2_and_mul_same,  "add2_and_mul_same",  "add twice and multiply in the same loop; same destination "},       
  {NULL,               NULL,                 NULL}
};


// // add and then zero out the result
// void add_and_zero_same(unsigned long iters, unsigned long *start, unsigned long *delta)
// {
//   unsigned long ret = *start;
//   unsigned long inc = *delta;
//   for(unsigned long i=0; i<iters; i++){
//     ret += inc;
//     ret = 0;
//   }
//   *start = ret;
// }

// // multiply and then zero out the result
// void mul_and_zero_same(unsigned long iters, unsigned long *start, unsigned long *delta)
// {
//   unsigned long ret = *start;
//   unsigned long mul = *delta;
//   for(unsigned long i=0; i<iters; i++){
//     ret *= mul;
//     ret = 0;
//   }
//   *start = ret;
// }

  // {add_and_zero_same,"add_and_zero_same","add then zero out the result"},
  // {mul_and_zero_same,"mul_and_zero_same","multiply then zero out the result"},
