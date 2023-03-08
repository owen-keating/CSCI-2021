#include "banlet.h"

void string_replace_char(char *str, char old, char new){
  int i = 0;
  while(str[i]!='\0'){                                                            //  iterate until reaching end of string
    if(str[i]==old) str[i] = new;                                                 //  replace original character with parameter
    i++;
  }
}

int count_linebreaks(char *msg){
  int i = 0;                                                                      //  start at index 0 in string
  int n = 1;
  while(msg[i]!='\0'){                                                            //  iterate until reaching end of string
    if(msg[i]=='\n') n++;                                                         //  new line at index i, increase by 1
    i++;
  }
  return n;                                                                       //  return number of linebreaks
}

int *find_linebreaks(char *msg, int *nbreaks){
  *nbreaks = count_linebreaks(msg);                                               //  pointer to number of linebreaks in string
  int *arr = malloc(*nbreaks*sizeof(int));                                        //  allocate memory for linebreaks array
  int i = 0;
  int n = 0;
  while(msg[i]!='\0'){                                                            //  iterate until reaching end of string
    if(msg[i]=='\n'){                                                             //  check if current index is linebreak
      arr[n] = i;                                                                 //  add index to array
      n++;                                                                        //  number of indices in array increase by 1
    }
    i++;                                                                          //  update current index in string
  }
  arr[n] = i;                                                                     //  final linebreak equal to last index in string
  return arr;                                                                     //  return pointer to array of linebreaks
}

void print_fontified_oneline(char *msg, font_t *font, int length){
  for(int i = 0; i<font->height; i++){                                            //  iterate through the height of the glyphs
    for(int j = 0; j<length; j++){                                                //  length represents number of glyphs in phrase
      int codepoint = msg[j];                                                     //  codepoint of current glyph
      printf("%s", font->glyphs[codepoint].data[i]);                              //  prints one row from a single glyph
    }
    printf("\n");                                                                 //  completed row, new line to continue printing
  }
}

void print_fontified(char *msg, font_t *font){
  int num = count_linebreaks(msg);                                                //  count number of linebreaks in message
  int *linebreaks = find_linebreaks(msg, &num);                                   //  pointer to array of linebreak indices
  int a = 0; int b = linebreaks[0];                                               //  b corresponds to the first linebreak
  for(int i = 0; i<num; i++){                                                     //  loop through num times (number of linebreaks)
    char *substr = malloc(b-a);                                                   //  pointer to substring array from index a to b
    for(int j = 0; j<b-a; j++){ substr[j] = msg[a+j]; }                           //  copy char data from msg to substr
    print_fontified_oneline(substr, font, b-a);                                   //  prints the substring in fontified form
    if(i<num-1){ a = b + 1; b = linebreaks[i+1]; }                                //  update the indices to next linebreak if not at the end
    free(substr);                                                                 //  free memory from the substring pointer
  }
  free(linebreaks);                                                               //  free linebreaks pointer
}


// PROVIDED: Initializes a glyph to mostly X's except for its
// codepoint on the first line.
void glyph_init(glyph_t *glyph, int codepoint){
  glyph->codepoint = codepoint;
  glyph->width = 6;
  for(int i=0; i<MAX_HEIGHT; i++){
    for(int j=0; j<MAX_WIDTH; j++){
      if(j == glyph->width){
        glyph->data[i][j] = '\0';
      }
      else{
        glyph->data[i][j] = 'X';
      }
    }
  }
  int len = sprintf((char *)glyph->data, "%d",codepoint);
  glyph->data[0][len] = 'X';
}        

font_t *font_load(char *filename){
  FILE *file = fopen(filename,"r");                                               //  open file
  if(file==NULL){ return NULL; }                                                  //  return null if file does not exist
  font_t *font = malloc(sizeof(font_t));                                          //  allocate memory for new font struct
  font->glyphs = malloc(NUM_ASCII_GLYPHS*sizeof(glyph_t));                        //  allocate memory for new array of glyphs pointer
  int ht; fscanf(file, "height: %d", &ht);
  font->height = ht;                                                              //  scan in first line to initialize height variable
  for(int i = 0; i<NUM_ASCII_GLYPHS; i++){ glyph_init(&font->glyphs[i], i); }     //  initialize glyphs to default representation
  int pt; int ret = fscanf(file, "%d", &pt);
  while(ret!=EOF){                                                                //  scan until reacing the end of the file
    for(int i = 0; i<ht; i++){                                                    //  read from row one to the bottom row of the glyph
      fscanf(file, "%s", font->glyphs[pt].data[i]);                               //  string represents one row of a glyph
      string_replace_char(font->glyphs[pt].data[i],'?',' ');                      //  replace all '?' characters with whitespace
    }
    ret = fscanf(file, "%d", &pt);                                                //  skip whitespace to next codepoint value (int)
  }
  fclose(file);                                                                   //  close file
  return font;                                                                    //  return font pointer
}

void font_free(font_t *font){
  free(font->glyphs);                                                             //  free memory array of glyphs pointer
  free(font);                                                                     //  free font struct
}
