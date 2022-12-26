#include "kv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvpair_t parseKeyVals(char * line) {
  kvpair_t kvPair;
  kvPair.key = NULL;
  kvPair.value = NULL;

  size_t keyLen = 0;
  while (*line != '=' && *line != '\0') {
    kvPair.key = realloc(kvPair.key, (keyLen + 1) * sizeof(kvPair.key));
    kvPair.key[keyLen] = *line;
    keyLen++;
    line++;
  }

  kvPair.key[keyLen] = '\0';

  line++;

  if (strchr(line, '\n') != NULL) {
    *strchr(line, '\n') = '\0';
  }

  kvPair.value = strdup(line);

  return kvPair;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open file");
    exit(EXIT_FAILURE);
  }

  kvarray_t * kvArray = malloc(sizeof(*kvArray));
  kvArray->kvPairs = NULL;

  char * curr = NULL;
  size_t linecap;
  size_t numPairs = 0;

  while (getline(&curr, &linecap, f) >= 0) {
    kvArray->kvPairs =
        realloc(kvArray->kvPairs, (numPairs + 1) * sizeof(*kvArray->kvPairs));
    kvArray->kvPairs[numPairs] = parseKeyVals(curr);

    free(curr);

    curr = NULL;
    numPairs++;
  }

  free(curr);
  kvArray->numPairs = numPairs;

  // exit with error if file can't be closed
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file!");
    exit(EXIT_FAILURE);
  }

  return kvArray;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->numPairs; i++) {
    free(pairs->kvPairs[i].key);
    free(pairs->kvPairs[i].value);
  }

  free(pairs->kvPairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->numPairs; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvPairs[i].key, pairs->kvPairs[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  char * value = NULL;

  for (size_t i = 0; i < pairs->numPairs; i++) {
    if (!strcmp(key, pairs->kvPairs[i].key)) {
      value = pairs->kvPairs[i].value;
    }
  }

  return value;
}