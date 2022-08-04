#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int N, K;
vector<int> arr;

typedef pair<int, int> p;
struct compare
{
  bool operator()(p a, p b)
  {
    if (a.first == b.first)
      return a.second > b.second;
    return a.first > b.first;
  }
};

int bfs()
{
  // frist: cnt, second: num
  priority_queue<p, vector<p>, compare> pq;

  pq.push({0, K});

  while (!pq.empty())
  {
    int cnt = pq.top().first;
    int num = pq.top().second;
    pq.pop();

    // printf("curr: %d %d\n", cnt, num);

    if (num == 0)
    {
      return cnt;
    }

    bool flag = false;
    for (int i = 0; i < arr.size(); i++)
    {
      if (num >= arr[i])
      {
        int nextN = num / arr[i];
        pq.push({cnt + (num % arr[i]), nextN});
        flag = true;
      }
    }

    if (!flag)
    {
      pq.push({cnt + num, 0});
    }
  }

  return -1;
}

void input()
{
  arr.clear();
  cin >> N;

  for (int i = 0; i < N; i++)
  {
    int x;
    cin >> x;
    arr.push_back(x);
  }

  cin >> K;
}

int main(void)
{

  int T;

  cin >> T;

  for (int tc = 1; tc <= T; tc++)
  {

    input();
    int ans = bfs();
    printf("#%d %d\n", tc, ans);
  }

  return 0;
}