#include <stdio.h>

#define M 119
#define N 544

int get_greate_common_div(int m, int n)
{
  int r;

  do {
    r = m % n;

    if (r)
    {
      m = n;
      n = r;
    }
    
  } while (r);

  return n;
}


int main()
{

  printf("m = %d, n = %d, GCD = %d\n", M, N, get_greate_common_div(N, M));
  return 0;

}
