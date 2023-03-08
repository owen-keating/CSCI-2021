#include "treemap.h"

//  README: This file was based on the source files found in the hw02-code zip.
//  Many of the functions in the treemap_main.c file are based on logic from
//  list_main.c, in accordance with the project 1 instructions I copied and
//  pasted the code directly from the homework and modified it to correspond
//  to the treemap functions that I wrote in the treemap_funcs.c file.

int main(int argc, char *argv[]){                                
  int echo = 0;
  if(argc > 1 && strcmp("-echo",argv[1])==0) {
    echo=1;
  }

  printf("TreeMap Editor\n");
  printf("Commands:\n");
  printf("  quit:            exit the program\n");
  printf("  print:           shows contents of the tree in reverse sorted order\n");
  printf("  add <key> <val>: inserts the given key/val into the tree, duplicate keys are ignored\n");
  printf("  get <key>:       prints FOUND if the name is in the tree, NOT FOUND otherwise\n");
  printf("  clear:           eliminates all key/vals from the tree\n");
  printf("  size:            prints the total number of nodes in the tree\n");
  printf("  preorder:        prints contents of the tree in pre-order which is how it will be saved\n");
  printf("  save <file>:     writes the contents of the tree in pre-order to the given file\n");
  printf("  load <file>:     clears the current tree and loads the one in the given file\n");
  
  char cmd[128];
  treemap_t tree;
  int success;
  treemap_init(&tree);

  while(1){
    printf("TM> ");
    success = fscanf(stdin,"%s",cmd);
    if(success==EOF){
      printf("\n");
      break;
    }

    if( strcmp("quit", cmd)==0 ){             //  quit command
      if(echo){
        printf("quit\n");
      }
      break;                                  //  ends the while loop
    }

    else if( strcmp("print", cmd)==0 ){       //  print command
      if(echo){
        printf("print\n");
      }
      treemap_print_revorder(&tree);          //  calls reverse order print
    }

    else if( strcmp("add", cmd)==0 ){         //  add command
      char temp[128];
      fscanf(stdin, "%s %s", cmd, temp);
      if(echo){
        printf("add %s %s\n", cmd, temp);
      }
      if(treemap_add(&tree, cmd, temp)==0){   //  calls add node function
        printf("modified existing key\n");    //  declaration of existing node
      }
    }

    else if( strcmp("get", cmd)==0 ){         //  get command
      fscanf(stdin, "%s", cmd);
      if(echo){
        printf("get %s\n", cmd);
      }
      char *str = treemap_get(&tree, cmd);    //  pointer to input key
      if(str==NULL){
        printf("NOT FOUND\n");                //  declaration of missing key
      }
      else{
        printf("FOUND: %s\n", str);           //  prints corresponding value
      }
    }

    else if( strcmp("clear", cmd)==0 ){       //  clear command
      if(echo){
        printf("clear\n");
      }
      treemap_clear(&tree);                   //  calls clear function
    }

    else if( strcmp("size", cmd)==0 ){        //  size command
      int x = treemap_size(&tree);            //  calls size function
      if(echo){
        printf("size\n%d nodes\n", x);        //  displays number of current nodes
      }
    }

    else if( strcmp("preorder", cmd)==0 ){    //  print command
      if(echo){
        printf("preorder\n");
      }
      treemap_print_preorder(&tree);          //  calls pre-order print
    }

    else if( strcmp("save", cmd)==0 ){        //  save command
      fscanf(stdin, "%s", cmd);
      if(echo){
        printf("save %s\n", cmd);
      }
      treemap_save(&tree, cmd);               //  calls save function
    }

    else if( strcmp("load", cmd)==0 ){        //  load command
      fscanf(stdin, "%s", cmd);
      if(echo){
        printf("load %s\n", cmd);
      }
      int x = treemap_load(&tree, cmd);       //  calls load function
      if(x==0){
        printf("load failed\n");              //  declaration file does not exist
      }
    }

    else{                                     //  unknown command case
      if(echo){
        printf("%s\n",cmd);
      }
      printf("unknown command %s\n",cmd);
    }
  }

  treemap_clear(&tree);                       //  clear tree to free memory
  return 0;
}