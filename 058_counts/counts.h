#include <stdio.h>
#include <stdlib.h>

#ifndef __COUNTS_H__
#define __COUNTS_H__
struct _one_count_t {
  //DEFINE ME
  const char * strv;
  size_t countn;
};
typedef struct _one_count_t one_count_t;

struct _counts_t {
  //DEFINE ME
  size_t nums;
  one_count_t * strc;
  size_t uncount;
};
typedef struct _counts_t counts_t;

counts_t * createCounts(void);
void addCount(counts_t * c, const char * name);
void printCounts(counts_t * c, FILE * outFile);

void freeCounts(counts_t * c);

#endif