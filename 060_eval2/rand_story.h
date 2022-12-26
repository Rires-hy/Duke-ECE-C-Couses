#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

//any functions you want your main to use
//input file

//the struct to store both kind of input text.
struct _Input_Read_struct {
  char ** strarr;
  size_t row;
};
typedef struct _Input_Read_struct Read_t;

Read_t ReadRaw(FILE * f);

void outputStory(Read_t Rtxt);

void freeString(Read_t Rtxt);

void parse(Read_t Raw);

char * parseAid(char * line, int * i);

void step2process(Read_t words, catarray_t * cat);

int checkRepeat(catarray_t * cat, char * line);

void freeCatarr(catarray_t * cat);

void storeCat(catarray_t * cat, char * catName, char * catWord);

void parse_Cat(Read_t Raw, catarray_t * cat);

int Ifdigit(char * line);

void freePrevious(category_t * previous);

void ParseProcess(Read_t sto, catarray_t * cats);

char * ChangeBlank(const char * SUB, char * line, char * befCat, char * aftCat);

void loadPrevious(category_t * previous, char * SUB);
#endif
