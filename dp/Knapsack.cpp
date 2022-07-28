#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

typedef pair<int, int> p;

int N, K;
vector<p> bag;
int dp[101][1001];

void solution()
{

  for (int i = 1; i <= N; i++)
  {
    for (int v = 1; v <= K; v++)
    {
      if (bag[i].first <= v)
      {
        dp[i][v] = max(dp[i - 1][v], bag[i].second + dp[i - 1][v - bag[i].first]);
      }
      else
      {
        dp[i][v] = dp[i - 1][v];
      }
    }
  }
}

void input()
{
  int v, c;

  bag.clear();
  bag.push_back({0, 0});
  memset(dp, 0, sizeof(dp));

  cin >> N >> K;

  for (int i = 0; i < N; i++)
  {
    cin >> v >> c;
    bag.push_back({v, c});
  }
}

int main(void)
{

  int T;

  cin >> T;

  for (int tc = 1; tc <= T; tc++)
  {
    input();
    solution();

    int ans = dp[N][K];

    printf("#%d %d\n", tc, ans);
  }

  return 0;
}