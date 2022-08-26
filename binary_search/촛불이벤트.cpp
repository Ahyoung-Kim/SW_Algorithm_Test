#include <stdio.h>
#include <cmath>

using namespace std;

int main(void)
{

  int T;

  scanf("%d", &T);

  for (int tc = 1; tc <= T; tc++)
  {

    long long n;
    scanf("%lld", &n);

    long long s = 1;
    long long e = sqrt(n) * 2;
    long long m;
    long long ret = -1;

    while (s <= e)
    {
      m = (s + e) / 2;
      long long tmp = m * (m + 1);

      if (tmp < n * 2)
      {
        s = m + 1;
      }
      else if (tmp > n * 2)
      {
        e = m - 1;
      }
      else
      {
        ret = m;
        break;
      }
    }

    printf("#%d %d\n", tc, ret);
  }

  return 0;
}