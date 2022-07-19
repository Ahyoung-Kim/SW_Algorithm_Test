#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>

using namespace std;

int n;
int cnt = 0;
bool dp[10] = {
    false,
};

int solution(int num)
{
  int temp = n * num;

  while (temp > 0)
  {
    int r = temp % 10;
    temp /= 10;

    if (dp[r])
    {
      continue;
    }

    dp[r] = true;
    cnt++;
  }

  if (cnt == 10)
  {
    return num;
  }

  return solution(num + 1);
}

int main(void)
{

  int T;

  cin >> T;

  for (int tc = 1; tc <= T; tc++)
  {
    cin >> n;
    cnt = 0;
    memset(dp, false, sizeof(dp));

    int ret = solution(1);
    ret *= n;

    printf("#%d %d\n", tc, ret);
  }

  return 0;
}