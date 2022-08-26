#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>

using namespace std;

int n, p;           // 1~200,000
int study[2000001]; //번호 크기 1~1000,000
int dp[2000001];

bool check(int len)
{

  for (int i = study[0]; i <= study[n - 1]; i++)
  {
    int days = dp[i + len - 1] - dp[i - 1];

    if (days + p >= len)
    {
      return true;
    }
  }

  return false;
}

int binary_search()
{
  int s = 1 + p;
  int e = n + p;
  int m;

  while (s <= e)
  {
    m = (s + e) / 2;

    if (check(m))
    {
      s = m + 1;
    }
    else
    {
      e = m - 1;
    }
  }

  return s - 1;
}

void set_dp()
{
  int max_day = study[n - 1] + p + n;

  for (int i = 1; i <= max_day; i++)
  {
    if (dp[i] == 1)
    {
      dp[i] = dp[i - 1] + 1;
    }
    else
    {
      dp[i] = dp[i - 1];
    }
  }
}

void input()
{
  memset(study, 0, sizeof(study));
  memset(dp, 0, sizeof(dp));

  cin >> n >> p;

  for (int i = 0; i < n; i++)
  {
    cin >> study[i];

    int day = study[i];
    dp[day] = 1;
  }
}

int main(void)
{

  int T;

  cin >> T;

  for (int tc = 1; tc <= T; tc++)
  {

    input();

    set_dp();

    int ans = binary_search();

    printf("#%d %d\n", tc, ans);
  }

  return 0;
}