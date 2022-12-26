#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

void display(int Age_month, double balance) {
  int age = Age_month / 12;
  int month = Age_month % 12;
  printf("Age %3d month %2d you have $%.2f \n ", age, month, balance);
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  int finalage = startAge + working.months + retired.months;
  int retireAge = startAge + working.months;
  while (startAge < finalage) {
    if (startAge < retireAge) {
      display(startAge, initial);
      initial = initial + initial * working.rate_of_return / 12 + working.contribution;
    }
    else {
      display(startAge, initial);
      initial = initial + initial * retired.rate_of_return / 12 + retired.contribution;
    }

    startAge++;
  }
}

int main() {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01;

  int startAge = 327;
  int initial = 21345;

  retirement(startAge, initial, working, retired);

  return 0;
}
