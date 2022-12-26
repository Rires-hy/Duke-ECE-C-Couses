#include <stdio.h>
#include <stdlib.h>
int * arrayMax(int * array, int n) {
  if (n == 0) {
    return NULL;
  }
  else {
    int * q;
    q = &array[0];
    for (int i = 1; i <= n; i++) {
      if (*q < array[i]) {
        q = &array[i];
      }
    }
    return q;
  }
}

size_t maxSeq(int * array, size_t n) {
  int result = 1;
  if (n == 0) {
    return 0;
  }
  int count = 1;

  for (int i = 0; i < n - 1; i++) {
    if (array[i] < array[i + 1]) {
      count++;
    }
    else {
      count = 1;
    }

    if (count > result) {
      result = count;
    }
  }
  return result;
}
