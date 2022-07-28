#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

int N;
int cash[8] = {50000, 10000, 5000, 1000, 500, 100, 50, 10};

void solution()
{
  int ret = 0;
  int i = 0;

  while (N != 0)
  {
    int won = cash[i];

    int temp = N / won;
    N = N % won;

    printf("%d ", temp);

    ret += temp;

    i++;

    if (i == 8)
      break;
  }

  for (int j = i; j < 8; j++)
  {
    printf("0 ");
  }

  printf("\n");
}

int main(void)
{

  int T;

  cin >> T;

  for (int tc = 1; tc <= T; tc++)
  {
    cin >> N;
    printf("#%d\n", tc);
    solution();
  }

  return 0;
}