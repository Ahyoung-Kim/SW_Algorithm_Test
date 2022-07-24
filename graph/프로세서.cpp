#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

int N;
int processor[13][13];
bool visit[13][13];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

// first: 해당 방향으로 전선을 연결했을 때의 길이
// second: 방향 남 0, 북 1, 동 2, 서 3
typedef pair<int, int> dir;

struct core
{
  int x;
  int y;
  vector<dir> direction;

  void set(int px, int py)
  {
    x = px;
    y = py;

    for (int i = 0; i < 4; i++)
    {
      int tx = x + dx[i];
      int ty = y + dy[i];

      if (tx < 0 || tx >= N || ty < 0 || ty >= N)
      {
        direction.push_back({0, i});
        continue;
      }

      int len = 0;
      if (i == 0)
      { // south
        for (int j = ty; j < N; j++)
        {
          len++;
          if (processor[j][tx] == 1)
          {
            len = -1;
            break;
          }
        }
      }
      else if (i == 1)
      { // north
        for (int j = ty; j >= 0; j--)
        {
          len++;
          if (processor[j][tx] == 1)
          {
            len = -1;
            break;
          }
        }
      }
      else if (i == 2)
      { // east
        for (int j = tx; j < N; j++)
        {
          len++;
          if (processor[ty][j] == 1)
          {
            len = -1;
            break;
          }
        }
      }
      else
      { // west
        for (int j = tx; j >= 0; j--)
        {
          len++;
          if (processor[ty][j] == 1)
          {
            len = -1;
            break;
          }
        }
      }

      direction.push_back({len, i});
    }

    sort(direction.begin(), direction.end());
  }

  void print_core()
  {

    printf("좌표: (%d, %d)\n", x, y);
    printf("방향 - 0 남, 1 북, 2 동, 3 서\n");

    for (int i = 0; i < 4; i++)
    {
      printf("{%d, %d}, ", direction[i].first, direction[i].second);
    }
    printf("\n");
  }
};

vector<core> cores;

void print_cores()
{
  for (int i = 0; i < cores.size(); i++)
  {
    core temp = cores[i];
    temp.print_core();
  }
}

void print_map()
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      printf("%d ", processor[i][j]);
    }
    printf("\n");
  }
  printf("---------------------------------\n");
}

void input()
{

  vector<pair<int, int>> coord;

  cores.clear();
  memset(visit, false, sizeof(visit));

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      cin >> processor[i][j];

      if (processor[i][j] == 1)
      {
        coord.push_back({j, i});
      }
    }
  }

  for (int i = 0; i < coord.size(); i++)
  {
    core ncore;
    ncore.set(coord[i].first, coord[i].second);
    cores.push_back(ncore);
  }
}

int set_line(int x, int y, int _dir, int val, int size)
{
  int i;
  int cnt = 0;

  switch (_dir)
  {
  case 0: // south
    for (i = y + 1; i < N && cnt < size; i++)
    {
      if (processor[i][x] == 1)
        return cnt;

      if (val == -1 && processor[i][x] == -1)
        return cnt;

      processor[i][x] = val;
      cnt++;
    }
    break;
  case 1: // north
    for (i = y - 1; i >= 0 && cnt < size; i--)
    {
      if (processor[i][x] == 1)
        return cnt;

      if (val == -1 && processor[i][x] == -1)
        return cnt;
      processor[i][x] = val;
      cnt++;
    }
    break;
  case 2: // east
    for (i = x + 1; i < N && cnt < size; i++)
    {
      if (processor[y][i] == 1)
        return cnt;

      if (val == -1 && processor[y][i] == -1)
        return cnt;
      processor[y][i] = val;
      cnt++;
    }
    break;
  case 3: // west
    for (i = x - 1; i >= 0 && cnt < size; i--)
    {
      if (processor[y][i] == 1)
        return cnt;

      if (val == -1 && processor[y][i] == -1)
        return cnt;
      processor[y][i] = val;
      cnt++;
    }
    break;
  default:
    break;
  }

  return cnt;
}

int get_size(int x, int y, int _dir)
{
  switch (_dir)
  {
  case 0:
    return N - y - 1;
    break;
  case 1:
    return y;
    break;
  case 2:
    return N - x - 1;
    break;
  case 3:
    return x;
    break;
  default:
    break;
  }
}

vector<pair<int, core>> path;
bool flag;
int ans;
void dfs_search(core curr, int depth, int cnt, int _dir)
{

  if (flag)
    return;

  if (depth == cores.size() - 1)
  {
    flag = true;
    ans = cnt;

    /*printf("cnt: %d\n", cnt);
    for (int i = 0; i < path.size(); i++) {
      printf("direc: %d\n", path[i].first);
      path[i].second.print_core();
    }
    printf("----------------------------------------\n");*/
    printf("ans: %d\n", ans);
    print_map();

    return;
  }

  core next = cores[depth + 1];

  for (int i = 0; i < 4; i++)
  {
    if (flag)
      break;

    int len = next.direction[i].first;
    int direc = next.direction[i].second;

    if (len == -1)
    {
      continue;
    }

    int size = get_size(next.x, next.y, direc);
    int ret = set_line(next.x, next.y, direc, -1, size);

    if (ret != size)
    {
      set_line(next.x, next.y, direc, 0, ret);
      continue;
    }

    path.push_back({direc, next});
    dfs_search(next, depth + 1, cnt + len, direc);
    path.pop_back();
    set_line(next.x, next.y, direc, 0, ret);
  }
}

void dfs()
{

  flag = false;
  ans = 0;

  for (int i = 0; i < 4; i++)
  {

    if (flag)
      break;

    int len = cores[0].direction[i].first;
    int _dir = cores[0].direction[i].second;

    if (len == -1)
      continue;

    int size = get_size(cores[0].x, cores[0].y, _dir);
    int ret = set_line(cores[0].x, cores[0].y, _dir, -1, size);

    if (ret != size)
    {
      set_line(cores[0].x, cores[0].y, _dir, 0, ret);
      continue;
    }

    path.push_back({_dir, cores[0]});
    dfs_search(cores[0], 0, len, _dir);
    path.pop_back();
    set_line(cores[0].x, cores[0].y, _dir, 0, ret);
  }
}

int main(void)
{

  int T;

  cin >> T;

  for (int tc = 1; tc <= T; tc++)
  {

    cin >> N;

    input();

    // print_cores();

    dfs();

    printf("#%d %d\n", tc, ans);
  }

  return 0;
}