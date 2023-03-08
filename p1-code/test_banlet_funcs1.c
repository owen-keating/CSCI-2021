#include "banlet.h"

#define PRINT_TEST sprintf(sysbuf,"awk 'NR==(%d+1){P=1;print \"{\"} P==1 && /ENDTEST/{P=0; print \"}\"} P==1{print}' %s", __LINE__, __FILE__); \
                   system(sysbuf);

void print_int_array(int *arr, int length){
  printf("[");
  for(int i=0; i<length-1; i++){
    printf("%2d, ",arr[i]);
  }
  if(length > 0){
    printf("%2d",arr[length-1]);
  }
  printf("]");
}

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("usage: %s <test_name>\n", argv[0]);
    return 1;
  }
  char *test_name = argv[1];
  char sysbuf[1024];

  if(0){}
  else if( strcmp( test_name, "string_replace_char_1" )==0 ) {
    PRINT_TEST;
    // Tests replacing characters in a string
    char string[]="A A B B A";
    string_replace_char(string, 'A', 'X');
    printf("result: '%s'\n", string);
  } // ENDTEST

  else if( strcmp( test_name, "string_replace_char_2" )==0 ) {
    PRINT_TEST;
    // Tests replacing characters in a string
    char string[]="A A B B A";
    string_replace_char(string, 'B', 'Y');
    printf("result: '%s'\n", string);
  } // ENDTEST

  else if( strcmp( test_name, "string_replace_char_3" )==0 ) {
    PRINT_TEST;
    // Tests replacing characters in a string
    char string[]="A A B B A";
    string_replace_char(string, ' ', '-');
    printf("result: '%s'\n", string);
  } // ENDTEST

  else if( strcmp( test_name, "string_replace_char_4" )==0 ) {
    PRINT_TEST;
    // Tests replacing characters in a string
    char string[]=
      "Four score and seven years ago our forefathers brought forth...";
    string_replace_char(string, 'F', 'P');
    string_replace_char(string, 'f', 'p');
    printf("result: '%s'\n", string);
  } // ENDTEST

  else if( strcmp( test_name, "count_linebreaks_1" )==0 ) {
    PRINT_TEST;
    // Tests counting linebreaks (\n and end of string) in a string
    char string[]="Hi";
    int count = count_linebreaks(string);
    printf("result: %d\n", count);
  } // ENDTEST

  else if( strcmp( test_name, "count_linebreaks_2" )==0 ) {
    PRINT_TEST;
    // Tests counting linebreaks (\n and end of string) in a string
    char string[]="O\nM\nG";
    int count = count_linebreaks(string);
    printf("result: %d\n", count);
  } // ENDTEST

  else if( strcmp( test_name, "count_linebreaks_3" )==0 ) {
    PRINT_TEST;
    // Tests counting linebreaks (\n and end of string) in a string
    char string[]=
      "If you lie to\nthe compiler,\nit will get\nits revenge.\n-Henry Spencer";
    int count = count_linebreaks(string);
    printf("result: %d\n", count);
  } // ENDTEST

  else if( strcmp( test_name, "find_linebreaks_1" )==0 ) {
    PRINT_TEST;
    // Tests locating linebreak indices in a string
    char string[]="Hi";
    int count = -1;
    int *linebreaks = find_linebreaks(string, &count);
    printf("count: %d\n",count);
    printf("array: "); print_int_array(linebreaks, count); printf("\n");
    free(linebreaks);
  } // ENDTEST

  else if( strcmp( test_name, "find_linebreaks_2" )==0 ) {
    PRINT_TEST;
    // Tests locating linebreak indices in a string
    char string[]="O\nM\nG";
    int count = -1;
    int *linebreaks = find_linebreaks(string, &count);
    printf("count: %d\n",count);
    printf("array: "); print_int_array(linebreaks, count); printf("\n");
    free(linebreaks);
  } // ENDTEST

  else if( strcmp( test_name, "find_linebreaks_3" )==0 ) {
    PRINT_TEST;
    // Tests locating linebreak indices in a string
    char string[]="If you lie to\nthe compiler,\nit will get\nits revenge.\n-Henry Spencer";
    int count = -1;
    int *linebreaks = find_linebreaks(string, &count);
    printf("count: %d\n",count);
    printf("array: "); print_int_array(linebreaks, count); printf("\n");
    free(linebreaks);
  } // ENDTEST

  else if( strcmp( test_name, "find_linebreaks_4" )==0 ) {
    PRINT_TEST;
    // Tests locating linebreak indices in a string
    char string[]="10\n20\n30\n40 50\n60 70 80\n 90\n100\n110 120\n130";
    int count = -1;
    int *linebreaks = find_linebreaks(string, &count);
    printf("count: %d\n",count);
    printf("array: "); print_int_array(linebreaks, count); printf("\n");
    free(linebreaks);
  } // ENDTEST

  else if( strcmp( test_name, "print_fontified_oneline_1" )==0 ) {
    PRINT_TEST;
    // print_fontified_oneline function with builtin font_standard
    char string[]="Hello world!";
    print_fontified_oneline(string, &font_standard, strlen(string));
  } // ENDTEST

  else if( strcmp( test_name, "print_fontified_oneline_2" )==0 ) {
    PRINT_TEST;
    // print_fontified_oneline function with builtin font_standard
    char *string;
    string="Holy $#!^";
    print_fontified_oneline(string, &font_standard, strlen(string));
    string="it WORKED.";
    print_fontified_oneline(string, &font_standard, strlen(string));
    string="SHOCKING, I know.";
    print_fontified_oneline(string, &font_standard, strlen(string));
  } // ENDTEST


  else if( strcmp( test_name, "print_fontified_oneline_fox" )==0 ) {
    PRINT_TEST;
    // print_fontified_oneline function with builtin font_standard
    char *string;
    string = "The quick brown fox";
    print_fontified_oneline(string, &font_standard, strlen(string));
    string = "jumps OVER the lazy";
    print_fontified_oneline(string, &font_standard, strlen(string));
    string = "dog.";
    print_fontified_oneline(string, &font_standard, strlen(string));
  } // ENDTEST


  else if( strcmp( test_name, "print_fontified_oneline_3" )==0 ) {
    PRINT_TEST;
    // print_fontified_oneline function with builtin font_standard
    char *string;
    string = " !\"#$%&'()";
    print_fontified_oneline(string, &font_standard, strlen(string));
    string = "*+,-./0123";
    print_fontified_oneline(string, &font_standard, strlen(string));
    string = "456789:;<=";
    print_fontified_oneline(string, &font_standard, strlen(string));
    string = ">?@ABCDEFG";
    print_fontified_oneline(string, &font_standard, strlen(string));
    string = "HIJKLMNOPQ";
    print_fontified_oneline(string, &font_standard, strlen(string));
    string = "RSTUVWXYZ[";
    print_fontified_oneline(string, &font_standard, strlen(string));
    string = "\\]^_`abcde";
    print_fontified_oneline(string, &font_standard, strlen(string));
    string = "fghijklmno";
    print_fontified_oneline(string, &font_standard, strlen(string));
    string = "pqrstuvwxy";
    print_fontified_oneline(string, &font_standard, strlen(string));
    string = "z{|}~";
    print_fontified_oneline(string, &font_standard, strlen(string));
  } // ENDTEST


  else if( strcmp( test_name, "print_fontified_oneline_length" )==0 ) {
    PRINT_TEST;
    // Checks print_fontified_oneline honors the length parameter.
    char *string;
    string = "One two three four, tell me that you love me more.";
    print_fontified_oneline(string, &font_standard, 4);
    print_fontified_oneline(string, &font_standard, 8);
    print_fontified_oneline(string, &font_standard, 19);
  } // ENDTEST


  else{
    printf("No test named '%s' found\n",test_name);
    return 1;
  }
  return 0;
}
