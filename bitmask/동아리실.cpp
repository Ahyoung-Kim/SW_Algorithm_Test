#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define MOD 1000000007

int dp[10001][17];
string str;

int solution()
{
  int ret = 0;

  cin >> str;

  for (int day = 0; day < str.size(); day++)
  {
    // DCBA
    int admin = 1 << (str[day] - 'A');

    for (int i = 1; i < 16; i++)
    {

      // 1일차: 'A"랑 첫째날 관리자가 모두 포함된 경우
      if (day == 0)
      {
        if ((i & 1) && (admin & i))
        {
          dp[day][i] = 1;
        }
        continue;
      }

      // 전날 i 사람들이 참여했을 때 불가능한 경우일때
      if (dp[day - 1][i] == 0)
        continue;

      // 2일차 ~
      for (int j = 1; j < 16; j++)
      {
        if ((i & j) && (admin & j))
        {
          dp[day][j] += dp[day - 1][i];
          dp[day][j] %= MOD;
        }
      }
    }
  }

  for (int i = 1; i < 16; i++)
  {
    ret += dp[str.size() - 1][i];
    ret %= MOD;
  }

  memset(dp, 0, sizeof(dp));
  return ret;
}

int main(void)
{
  int T, N;

  cin >> T;

  for (int t = 1; t <= T; t++)
  {

    int ans = solution();
    printf("#%d %d\n", t, ans);
  }

  return 0;
}