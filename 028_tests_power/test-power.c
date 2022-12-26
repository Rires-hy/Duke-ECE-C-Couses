#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);
int RC(unsigned x, unsigned y, unsigned expAns) {
  if (expAns == power(x, y)) {
    return 1;
  }
  else {
    return 0;
  }
}
int main() {
  if (RC(0, 0, 1) == 0) {
    return EXIT_FAILURE;
  }
  if (RC(-1, -1, -1) == 0) {
    return EXIT_FAILURE;
  }
  if (RC(2, 0, 1) == 0) {
    return EXIT_FAILURE;
  }
  if (RC(1, -1, 1) == 0) {
    return EXIT_FAILURE;
  }
  if (RC(-1, 3, -1) == 0) {
    return EXIT_FAILURE;
  }
  if (RC(1, -3, 1) == 0) {
    return EXIT_FAILURE;
  }
  if (RC(-3, 3, -27) == 0) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
