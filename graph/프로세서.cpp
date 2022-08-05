#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

int N;
int map[13][13];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
vector<pair<int, int>> cores;

int maxC;
int minL;

int check(int x, int y, int tx, int ty, int val, int right)
{
  int i, j;
  int ret = 0;

  if (x == tx)
  { // y축 방향으로 이동
    if (y < ty)
    { //남
      for (i = y + 1; i < N; i++)
      {
        if (map[i][x] != right)
        {
          for (j = i - 1; j > y; j--)
          {
            map[j][x] = right;
          }
          return 0;
        }
        map[i][x] = val;
        ret++;
      }
    }
    else
    { // 북
      for (i = y - 1; i >= 0; i--)
      {
        if (map[i][x] != right)
        {
          for (j = i + 1; j < y; j++)
          {
            map[j][x] = right;
          }
          return 0;
        }
        map[i][x] = val;
        ret++;
      }
    }
  }
  else if (y == ty)
  { // x축 방향으로 이동
    if (x < tx)
    { // 동
      for (i = x + 1; i < N; i++)
      {
        if (map[y][i] != right)
        {
          for (j = i - 1; j > x; j--)
          {
            map[y][j] = right;
          }
          return 0;
        }
        map[y][i] = val;
        ret++;
      }
    }
    else
    { // 서
      for (i = x - 1; i >= 0; i--)
      {
        if (map[y][i] != right)
        {
          for (j = i + 1; j < x; j++)
          {
            map[y][j] = right;
          }
          return 0;
        }
        map[y][i] = val;
        ret++;
      }
    }
  }

  return ret;
}

void dfs(int idx, int cnum, int lnum)
{

  if (idx == cores.size())
  {

    if (maxC < cnum)
    {
      maxC = cnum;
      minL = lnum;
    }
    else if (maxC == cnum)
    {
      if (minL > lnum)
      {
        minL = lnum;
      }
    }
    return;
  }

  bool flag = false;
  pair<int, int> curr = cores[idx];

  for (int i = 0; i < 4; i++)
  {
    int tx = curr.first + dx[i];
    int ty = curr.second + dy[i];

    if (map[ty][tx])
      continue;

    int len = check(curr.first, curr.second, tx, ty, 2, 0);
    if (len != 0)
    {
      flag = true;
      dfs(idx + 1, cnum + 1, lnum + len);
      check(curr.first, curr.second, tx, ty, 0, 2);
    }
  }

  if (!flag)
  { // 네 방향 중 전선을 어디에도 잇지 못할 때
    dfs(idx + 1, cnum, lnum);
  }
}

void input()
{
  cin >> N;

  cores.clear();

  maxC = 0;
  minL = 1000000000;

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      cin >> map[i][j];

      if (i == 0 || j == 0 || i == N - 1 || j == N - 1)
        continue;

      if (map[i][j] == 1)
      {
        cores.push_back({j, i});
      }
    }
  }
}

int main(void)
{

  int T;

  cin >> T;

  for (int tc = 1; tc <= T; tc++)
  {

    input();

    dfs(0, 0, 0);

    printf("#%d %d\n", tc, minL);
  }

  return 0;
}