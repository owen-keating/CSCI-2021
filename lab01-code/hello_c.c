// hello_c.c : this file has some typos in it that need to be
// corrected. Run the command
// 
//   > make test-code
//
// and examine the output carefully to determine where to make changes.

#include <stdio.h>                           // include standard I/O funcs
                                             // like printf()

int main(int argc, char *argv[]){            // C programs always start in main()
  char *lines[] = {                          // array of char pointers,
    "Goodbye Python. Goodbye Java.",         // each points at a string
    "Adios array bounds checking and godspeed",
    " garbage collector: I'll miss you both.",
    "Auf wiedersehen exceptions.",
    "So long OO-programming... whatever you are.",
    "",
    "Adieu polymorphic types with type inference, higher-order functions,",
    " rich built-in data, full-on modules, interactive loop,",
    " time-travelling debugger, byte- and native-code compilers.",
    "Au revoir, OCaml: c'est la vie.",
    "",
    "Now it's time to bang on Bits, 8 of which is a Byte.",
    "Now it's time to point pointers past proper positions,",
    " to shift, and, or, xor, and more.",
    "",
    "Now it's time to malloc() myself and free() freely,",
    " to deref dangerously which will suffer segfaults and lead to leaks.",
    "Now it's time to code close to the metal and resonate with the machine.",
    "",
    "It won't be easy. It may not be fun. But it will be true.",
    "And I will stay determined to see this course through."
    "",
    "Hello C.",
    NULL
  };

  for(int i=0; lines[i] != NULL; i++){       // iterate over the strings
    printf("%s\n",lines[i]);                 // print each on its own line
  }

  return 0;                                  // success: program returns 0
}
         
