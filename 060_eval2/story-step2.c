#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  //general check for valid argc
  if (argc != 2) {
    fprintf(stderr, "Error on command line argument");
    exit(EXIT_FAILURE);
  }

  //genearl check for open file
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Fail to open file");
    exit(EXIT_FAILURE);
  }

  //store raw word.txt
  Read_t words;
  words = ReadRaw(f);

  //create the cat
  catarray_t * cat = malloc(sizeof(*cat));
  cat->n = 0;
  cat->arr = NULL;
  //process the read text form words.txt
  step2process(words, cat);

  //print  cat
  printWords(cat);

  //free memory
  freeCatarr(cat);
  freeString(words);

  //check for close file sucess
  if (fclose(f) != 0) {
    fprintf(stderr, "close file fail");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
