#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

int n, m;
unordered_set<string> set1;
vector<string> set2;

int solution()
{

  int ret = 0;

  for (int i = 0; i < set2.size(); i++)
  {
    string temp = set2[i];

    auto itr = set1.find(temp);

    if (itr == set1.end())
    {
      continue;
    }

    ret++;
  }

  return ret;
}

void input()
{
  string str;

  cin >> n >> m;
  set1.clear();
  set2.clear();

  for (int i = 0; i < n; i++)
  {
    cin >> str;
    set1.insert(str);
  }

  for (int i = 0; i < m; i++)
  {
    cin >> str;
    set2.push_back(str);
  }
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