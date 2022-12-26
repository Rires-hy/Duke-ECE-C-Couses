#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int decrypt(FILE * f) {
  int c;
  int array[26] = {0};
  int temp;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      temp = c - 'a';
      array[temp]++;
    }
  }
  int key;
  int ep = 0;
  for (int i = 1; i < 26; i++) {
    if (array[ep] < array[i]) {
      ep = i;
    }
  }

  if (ep < 4) {
    key = ep + 22;
  }
  else {
    key = ep - 4;
  }
  return key;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int key = decrypt(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  if ((key >= 0) && (key < 26)) {
    fprintf(stdout, "%d\n", key);
  }
  else {
    fprintf(stderr, "cannot figure out!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
