#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

#define MAXN 100005

int N; // 100000
vector<vector<int>> tree;
int depth[MAXN];
int dp[MAXN][23];
bool visit[MAXN];

void dfs(int d, int curr)
{

  depth[curr] = d;
  visit[curr] = true;

  for (int i = 0; i < tree[curr].size(); i++)
  {
    int next = tree[curr][i];

    if (visit[next])
      continue;
    visit[next] = true;
    dp[next][0] = curr;
    dfs(d + 1, next);
  }
}

void bfs_depth()
{
  queue<pair<int, int>> q;
  q.push({0, 0});
  visit[0] = true;

  while (!q.empty())
  {
    int num = q.front().first;
    int d = q.front().second;
    q.pop();

    depth[num] = d;

    for (int i = 0; i < tree[num].size(); i++)
    {
      int next = tree[num][i];
      if (!visit[next])
      {
        visit[next] = true;
        dp[next][0] = num;
        q.push({next, d + 1});
      }
    }
  }
}

void funct()
{
  for (int i = 1; i <= 20; i++)
  {
    for (int j = 0; j < N; j++)
    {
      dp[j][i] = dp[dp[j][i - 1]][i - 1];
    }
  }
}

int lca(int u, int v)
{
  if (depth[u] < depth[v])
    swap(u, v);

  for (int i = 19; i >= 0; i--)
  {
    if (depth[u] - depth[v] >= (1 << i))
      u = dp[u][i];
  }

  if (u == v)
    return u;

  for (int i = 19; i >= 0; i--)
  {
    if (dp[v][i] != dp[u][i])
    {
      u = dp[u][i];
      v = dp[v][i];
    }
  }

  return dp[u][0];
}

long long bfs()
{
  memset(visit, false, sizeof(visit));
  queue<int> q;
  vector<int> arr;
  q.push(0);
  long long cnt = 0;
  visit[0] = true;

  while (!q.empty())
  {
    int cur = q.front();
    q.pop();

    arr.push_back(cur);

    for (int i = 0; i < tree[cur].size(); i++)
    {
      int next = tree[cur][i];
      if (!visit[next])
      {
        visit[next] = true;
        q.push(next);
      }
    }
  }

  for (int i = 0; i < arr.size() - 1; i++)
  {
    int LCA = lca(arr[i], arr[i + 1]);
    long long tmp1 = depth[arr[i]] - depth[LCA];
    long long tmp2 = depth[arr[i + 1]] - depth[LCA];

    cnt += (tmp1 + tmp2);
  }

  return cnt;
}

void input()
{
  int parent;

  memset(depth, 0, sizeof(depth));
  memset(dp, 0, sizeof(dp));
  memset(visit, false, sizeof(visit));
  tree.clear();

  cin >> N;

  tree.resize(N + 3);
  for (int i = 1; i < N; i++)
  {
    cin >> parent;
    tree[parent - 1].push_back(i);
  }
  for (int i = 0; i < N; i++)
  {
    sort(tree[i].begin(), tree[i].end());
  }
}

int main(void)
{

  int T;

  cin >> T;

  for (int tc = 1; tc <= T; tc++)
  {

    input();

    // dfs(0, 0);
    bfs_depth();
    funct();

    long long ret = bfs();

    printf("#%d %ld\n", tc, ret);
  }

  return 0;
}