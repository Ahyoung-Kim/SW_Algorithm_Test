#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

int N;
bool visit[401][401];
vector<pair<int, int>> num;

void check_visit(int idx)
{

  int prev = num[idx].second;

  for (int i = idx + 1; i < num.size(); i++)
  {
    int from = num[i].first;
    int to = num[i].second;

    if (visit[from][to])
    {
      continue;
    }

    if (from > prev)
    {
      visit[from][to] = true;
      prev = to;

      if (prev % 2 != 0)
        prev++;
    }
  }
}

int solution()
{

  int ret = 0;

  for (int i = 0; i < num.size(); i++)
  {
    int from = num[i].first;
    int to = num[i].second;

    if (!visit[from][to])
    {
      visit[from][to] = true;
      check_visit(i);
      ret++;
    }
  }

  return ret;
}

void input()
{
  cin >> N;
  int to, from;
  num.clear();
  memset(visit, false, sizeof(visit));

  for (int i = 0; i < N; i++)
  {
    cin >> from >> to;
    if (from > to)
      num.push_back({to, from});
    else
      num.push_back({from, to});
  }
  sort(num.begin(), num.end());
}

int main(void)
{

  int T;

  cin >> T;

  for (int tc = 1; tc <= T; tc++)
  {
    input();
    int ans = solution();
    printf("#%d %d\n", tc, ans);
  }

  return 0;
}