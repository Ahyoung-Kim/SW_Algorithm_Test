#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

string num;
int n;
int ans = 0;

void swap(int i, int j)
{
  char temp = num[i];
  num[i] = num[j];
  num[j] = temp;
}

char get_max(int s)
{

  char maxC = num[s];

  for (int i = s + 1; i < num.size(); i++)
  {
    if (maxC < num[i])
    {
      maxC = num[i];
    }
  }

  return maxC;
}

void dfs(int depth, int idx)
{

  if (depth == n)
  {
    // cout << num << endl;
    ans = max(ans, stoi(num));
    return;
  }

  if (idx == num.size() - 2 && depth < n)
  {
    int tmp1 = num.size() - 1;
    int tmp2 = num.size() - 2;

    if (num[tmp2] == num[tmp2 - 1])
    {
      dfs(n, tmp2);
      return;
    }

    for (int i = 0; i < n - depth; i++)
    {
      swap(tmp1, tmp2);
    }
    dfs(n, tmp1);
    return;
  }

  char c = get_max(idx);

  if (c == num[idx])
  {
    dfs(depth, idx + 1);
  }
  else
  {
    for (int i = idx + 1; i < num.size(); i++)
    {
      if (c == num[i])
      {
        swap(idx, i);
        dfs(depth + 1, idx + 1);
        swap(idx, i);
      }
    }
  }
}

void solution()
{

  // int midx = get_max_idx(0);
  dfs(0, 0);
}

int main(void)
{
  int T;

  cin >> T;

  for (int t = 1; t <= T; t++)
  {
    ans = 0;
    cin >> num >> n;

    solution();

    printf("#%d %d\n", t, ans);
  }

  return 0;
}