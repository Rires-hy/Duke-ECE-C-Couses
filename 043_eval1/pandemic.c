#include "pandemic.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int * arrayMax(int * array, int n) {
  //same function I done in task_035
  if (n == 0) {
    return NULL;
  }
  else {
    int * q = NULL;
    q = &array[0];
    for (int i = 1; i < n; i++) {
      if (*q < array[i]) {
        q = &array[i];
      }
    }
    return q;
  }
}

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;
  //error if the first char is a comma
  if (line[0] == ',') {
    fprintf(stderr, "No input of country name");
    exit(EXIT_FAILURE);
  }
  // error if too long
  if (strchr(line, '\n') == NULL) {
    fprintf(stderr, "line is too long or not match the correct format!\n");
    exit(EXIT_FAILURE);
  }
  int i = 0;
  //check if there is a comma:
  if (strchr(line, ',') == NULL) {
    fprintf(stderr, "No comma, invalid input!\n");
    exit(EXIT_FAILURE);
  }
  if (line == NULL) {
    fprintf(stderr, "invliad input for line");
    exit(EXIT_FAILURE);
  }
  //put the char before comma to ans.name
  while (!(line[i] == ',')) {
    if (i > 64) {
      fprintf(stderr, "name exceed the maximum length");
      exit(EXIT_FAILURE);
    }
    ans.name[i] = line[i];
    i++;
  }
  //array p to store the number in char
  char p[64] = {0};
  ans.name[i] = '\0';
  i = i + 1;
  if (line[i] == '\n') {
    fprintf(stderr, "empty input of population\n");
    exit(EXIT_FAILURE);
  }
  if (line[i] == '\0') {
    fprintf(stderr, "there is no input of population\n ");
    exit(EXIT_FAILURE);
  }
  if (strchr(&line[i], ',') != NULL) {
    fprintf(stderr, "more than 1 comma found, invalid input\n");
    exit(EXIT_FAILURE);
  }
  int j = 0;
  //move population to array p
  while (!((line[i] == '\0') || (line[i] == '\n'))) {
    if (isdigit(line[i])) {
      p[j] = line[i];
    }
    else {
      fprintf(stderr, "there is non-digit input of population");
      exit(EXIT_FAILURE);
    }
    i++;
    j++;
  }
  //convert to number
  if (atoi(p) != 0) {
    ans.population = atoi(p);
  }
  else {
    fprintf(stderr, "convert from string to uint64_t failed!");
    exit(EXIT_FAILURE);
  }
  if (ans.population < 0) {
    fprintf(stderr, "population should not be a negative value");
    exit(EXIT_FAILURE);
  }
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  //error of no enough data
  if (n_days < 7) {
    // doing nothing, exit success
    exit(EXIT_SUCCESS);
  }
  //error if invalid input
  if (data == NULL) {
    fprintf(stderr, "input data error");
    exit(EXIT_FAILURE);
  }
  //running average
  double total;
  for (int i = 0; i < n_days - 6; i++) {
    total = 0;
    for (int j = 0; j <= 6; j++) {
      total += (double)data[i + j];
    }
    avg[i] = total / 7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  uint64_t total = 0;
  for (int i = 0; i < n_days; i++) {
    total += data[i];
    cum[i] = 100000 * total / (double)pop;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  if (n_countries <= 0) {
    fprintf(stderr, "invalid countries number");
    exit(EXIT_FAILURE);
  }
  if (n_days <= 0) {
    fprintf(stderr, "invalid days number");
    exit(EXIT_FAILURE);
  }
  int eachMax[n_countries];
  //initialize eachMax to prevent memory error:
  for (int k = 0; k < n_countries; k++) {
    eachMax[k] = 0;
  }
  //find the max daily countries for each countries
  for (int i = 0; i < n_countries; i++) {
    eachMax[i] = *(arrayMax((int *)data[i], n_days));
  }
  // find the country of max daily case among this countries's max array,
  int * maxC = arrayMax(eachMax, n_countries);
  //transfer from address to n_countries
  int ANSc = maxC - &eachMax[0];
  //output
  printf("%s has the most daily cases with %u\n", countries[ANSc].name, eachMax[ANSc]);
}
