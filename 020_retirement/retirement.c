#include <stdio.h>
#include <stdlib.h>
struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;
void retirement(int startAge,           //in months
                double initial,         //initial savings in dollars
                retire_info working,    //info about working
                retire_info retired) {  //info about being retired;
  for (int i = 0; i < working.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, initial);
    initial = working.contribution + initial * (1 + working.rate_of_return);
    startAge++;
  }
  for (int i = 0; i < retired.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, initial);
    initial = retired.contribution + initial * (1 + retired.rate_of_return);
    startAge++;
  }
}

int main() {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retire_info retire;
  retire.months = 384;
  retire.contribution = -4000;
  retire.rate_of_return = 0.01 / 12;

  int age = 327;
  double saving = 21345;
  retirement(age, saving, working, retire);
  return 0;
}
