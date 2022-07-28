#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <queue>
using namespace std;

int N;
int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
char map[301][301];
bool visit[301][301];

typedef pair<int, int> p;

void print()
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      printf("%c ", map[i][j]);
    }
    printf("\n");
  }
}

char check(int x, int y)
{
  int ret = 0;

  for (int i = 0; i < 8; i++)
  {
    int tx = x + dx[i];
    int ty = y + dy[i];

    if (tx < 0 || tx >= N || ty < 0 || ty >= N)
      continue;

    if (map[ty][tx] == '*')
      ret++;
  }
  return ret + 48;
}

void bfs(int x, int y)
{

  queue<p> q;

  visit[y][x] = true;
  q.push({x, y});

  while (!q.empty())
  {
    p curr = q.front();
    q.pop();
    char star = check(curr.first, curr.second);
    // map[curr.second][curr.first] = star;
    // printf("{(%d, %d), %c} ", curr.first, curr.second, star);

    if (star != '0')
    {
      continue;
    }

    for (int i = 0; i < 8; i++)
    {
      int tx = curr.first + dx[i];
      int ty = curr.second + dy[i];

      if (tx < 0 || tx >= N || ty < 0 || ty >= N || visit[ty][tx])
        continue;

      visit[ty][tx] = true;
      q.push({tx, ty});
    }
  }

  // printf("\n");
}

int solution()
{
  int ret = 0;

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      if (map[i][j] == '.' && !visit[i][j])
      {
        char temp = check(j, i);

        if (temp == '0')
        {
          // printf("bfs start\n");
          // map[i][j] = temp;
          bfs(j, i);
          ret++;
        }
      }
    }
  }

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      if (map[i][j] == '.' && !visit[i][j])
      {
        // char temp = check(j, i);
        // map[i][j] = temp;
        ret++;
      }
    }
  }

  return ret;
}

void input()
{
  memset(visit, false, sizeof(visit));

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      cin >> map[i][j];
    }
  }
}

int main(void)
{
  int T;

  cin >> T;

  for (int tc = 1; tc <= T; tc++)
  {

    cin >> N;
    int ans = 0;

    input();
    ans = solution();
    // print();

    printf("#%d %d\n", tc, ans);
  }

  return 0;
}