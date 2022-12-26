#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * countsArray = malloc(sizeof(*countsArray));
  countsArray->strc = NULL;
  countsArray->nums = 0;
  countsArray->uncount = 0;

  return countsArray;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->uncount++;
  }
  else {
    if (c->nums == 0) {
      c->strc = realloc(c->strc, (c->nums + 1) * sizeof(*c->strc));
      c->strc[c->nums].strv = name;
      c->strc[c->nums].countn = 1;
      c->nums++;
    }
    else {
      int priorEntry = 0;
      for (size_t i = 0; i < c->nums; i++) {
        if (!strcmp(name, c->strc[i].strv)) {
          c->strc[i].countn++;
          priorEntry = 1;
        }
      }

      if (!priorEntry) {
        c->strc = realloc(c->strc, (c->nums + 1) * sizeof(*c->strc));
        c->strc[c->nums].strv = name;
        c->strc[c->nums].countn = 1;
        c->nums++;
      }
    }
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->nums; i++) {
    fprintf(outFile, "%s: %zu\n", c->strc[i].strv, c->strc[i].countn);
  }

  if (c->uncount > 0) {
    fprintf(outFile, "<unknown> : %zu\n", c->uncount);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  free(c->strc);
  free(c);
}