#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);
int RC(int * array, size_t y, size_t expAns) {
  if (expAns == maxSeq(array, y)) {
    return 1;
  }
  else {
    return 0;
  }
}
int main() {
  int array1[] = {1, 1, 1, 1, 1};
  if (RC(array1, 5, 1) == 0) {
    return EXIT_FAILURE;
  }
  int array2[] = {1, 2, 3, 4};
  if (RC(array2, 4, 4) == 0) {
    return EXIT_FAILURE;
  }
  int array3[] = {-5, 1, 2, 3, 4, 1, 2, 0};
  if (RC(array3, 8, 5) == 0) {
    return EXIT_FAILURE;
  }
  int array4[] = {1};
  if (RC(array4, 0, 0) == 0) {
    return EXIT_FAILURE;
  }
  int array5[] = {-5, 5, 0, 1, 2};
  if (RC(array5, 5, 3) == 0) {
    return EXIT_FAILURE;
  }
  int array6[] = {1, 1, 1, 1};
  if (RC(array6, 4, 1) == 0) {
    return EXIT_FAILURE;
  }
  int array7[] = {-2, 0, 0, 0};
  if (RC(array7, 4, 2) == 0) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
