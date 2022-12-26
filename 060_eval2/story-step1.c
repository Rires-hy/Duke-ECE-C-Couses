#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Error on command line argument");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Fail to open file");
    exit(EXIT_FAILURE);
  }
  Read_t text;
  text = ReadRaw(f);
  parse(text);
  outputStory(text);
  freeString(text);
  if (fclose(f) != 0) {
    fprintf(stderr, "close file fail");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
