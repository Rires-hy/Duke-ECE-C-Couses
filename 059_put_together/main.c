#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
    FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "could not open file");
    exit(EXIT_FAILURE);
  }

  counts_t * countsArray = createCounts();

  char * curr = NULL;
  char * countStr = NULL;
  size_t line;

  while (getline(&curr, &line, f) >= 0) {
    if (strchr(curr, '\n') != NULL) {
      *strchr(curr, '\n') = '\0';
    }
    countStr = lookupValue(kvPairs, curr);
    addCount(countsArray, countStr);

    free(curr);

    countStr = NULL;
    curr = NULL;
  }

  free(curr);

  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close file\n");
    exit(EXIT_FAILURE);
  }

  return countsArray;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc < 3) {
    fprintf(
        stderr,
        "Expected usage ./count_values key/value.txt countfile1.txt countfile2.txt\n");
    return EXIT_FAILURE;
  }
  else {
    kvarray_t * kv = readKVs(argv[1]);
    //count from 2 to argc (call the number you count i)
    for (int i = 2; i < argc; i++) {
      //count the values that appear in the file named by argv[i], using kv as the key/value pair
      //   (call this result c)
      counts_t * c = countFile(argv[i], kv);
      //compute the output file name from argv[i] (call this outName)
      char * outName = computeOutputFileName(argv[i]);
      //open the file named by outName (call that f)
      FILE * f = fopen(outName, "w");
      //print the counts from c into the FILE f
      printCounts(c, f);
      //close f
      if (fclose(f) != 0) {
        fprintf(stderr, "Failed to close file\n");
        return EXIT_FAILURE;
      }
      //free the memory for outName and c
      free(outName);
      freeCounts(c);
    }

    //free the memory for kv
    freeKVs(kv);
  }
  return EXIT_SUCCESS;
}
