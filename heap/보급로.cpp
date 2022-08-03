#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cstring>
using namespace std;

int N;
char map[101][101];
bool visit[101][101];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

struct node
{
  int x;
  int y;
  int cnt;
};

struct compare
{
  bool operator()(node a, node b)
  {
    return a.cnt > b.cnt;
  }
};

int bfs()
{
  priority_queue<node, vector<node>, compare> pq;

  visit[0][0] = true;
  pq.push({0, 0, 0});

  while (!pq.empty())
  {
    node curr = pq.top();
    pq.pop();

    if (curr.x == N - 1 && curr.y == N - 1)
    {
      return curr.cnt;
    }

    for (int i = 0; i < 4; i++)
    {
      int tx = curr.x + dx[i];
      int ty = curr.y + dy[i];

      if (tx < 0 || tx >= N || ty < 0 || ty >= N)
        continue;
      if (visit[ty][tx])
        continue;

      visit[ty][tx] = true;
      int _cnt = map[ty][tx] - 48;
      pq.push({tx, ty, curr.cnt + _cnt});
    }
  }
}

void input()
{
  cin >> N;

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      cin >> map[i][j];
    }
  }

  memset(visit, false, sizeof(visit));
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