#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (!(argc == 3 || argc == 4)) {
    fprintf(stderr, "Error on command line argument");
    exit(EXIT_FAILURE);
  }

  if (argc == 3) {
    FILE * f = fopen(argv[2], "r");
    if (f == NULL) {
      fprintf(stderr, "Fail to open file 1\n");
      exit(EXIT_FAILURE);
    }
    FILE * f2 = fopen(argv[1], "r");
    if (f2 == NULL) {
      fprintf(stderr, "Fail to open file 2\n");
      exit(EXIT_FAILURE);
    }

    //store raw text
    Read_t text;
    text = ReadRaw(f);
    //store raw word
    Read_t words;
    words = ReadRaw(f2);

    //lset up the cat
    catarray_t * cat = malloc(sizeof(*cat));
    cat->n = 0;
    cat->arr = NULL;

    //use the previosu step2 process to parce the word.txt
    step2process(words, cat);

    //replace the blank accoring to the cat from word.txt
    ParseProcess(text, cat);

    //print the text after parse
    outputStory(text);

    //free memory
    freeString(text);
    freeCatarr(cat);
    freeString(words);

    //general check for close file
    if (fclose(f) != 0) {
      fprintf(stderr, "close file fail\n");
      exit(EXIT_FAILURE);
    }
    if (fclose(f2) != 0) {
      fprintf(stderr, "close file 2 fail\n");
      exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
  }
}
