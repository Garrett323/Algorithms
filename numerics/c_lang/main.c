#include <stdio.h>

long fast_power_rec(int, int);
long naive_power(int, int);

int main(void) {
  int a = 3;
  int b = 4;
  printf("%d^%d = %ld\n", a, b, fast_power_rec(a, b));
  printf("%d^%d = %ld\n", a, b, naive_power(a, b));

}

// returns a^b
long fast_power_rec(int a, int b) {
  if (b == 0) {
    return 1;
  }
  if (b == 1) {
    return a;
  }
  long ans = fast_power(a*a, b/2);
  if (b % 2) {
    return ans * a;
  }
  else {
    return ans;
  }
}

long naive_power(int a, int b) {
  if (b == 0) {
    return 1;
  }
  long ans = 1;
  for (int i=0; i<b; i++) {
    ans *= a;
  }
  return ans;
}
