#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "invalid input\n");
    exit(EXIT_FAILURE);
  }
  char m[10][10];
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "cannot open file");
    exit(EXIT_FAILURE);
  }
  char c;
  char * p;
  for (int i = 0; i < 10; i++) {
    p = fgets(m[i], 11, f);
    if (p == NULL) {
      fprintf(stderr, "input row invalid");
      exit(EXIT_FAILURE);
    }
    if ((c = fgetc(f)) != '\n') {
      printf("%c\n", c);
      fprintf(stderr, "Row too long");
      exit(EXIT_FAILURE);
    }
  }
  if ((c = fgetc(f)) != EOF) {
    fprintf(stderr, "extra row\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      fprintf(stdout, "%c", m[9 - j][i]);
    }
    fprintf(stdout, "\n");
  }
  return EXIT_SUCCESS;
}
