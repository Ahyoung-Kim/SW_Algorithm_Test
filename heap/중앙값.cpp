#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define MOD 20171109

int N, A;
int cnt;

long long solution()
{
  int x, y;
  long long ret = 0;
  priority_queue<int, vector<int>, greater<int>> minH;
  priority_queue<int, vector<int>, less<int>> maxH;

  cin >> N >> A;
  maxH.push(A);

  for (int i = 0; i < N; i++)
  {
    cin >> x >> y;
    minH.push(x);
    maxH.push(y);

    if (maxH.top() > minH.top())
    {
      int min = minH.top();
      minH.pop();
      int max = maxH.top();
      maxH.pop();

      minH.push(max);
      maxH.push(min);
    }

    ret += maxH.top();
  }

  return (ret % MOD);
}

int main(void)
{

  int T;

  cin >> T;

  for (int tc = 1; tc <= T; tc++)
  {
    long long ans = solution();

    printf("#%d %d\n", tc, ans);
  }

  return 0;
}