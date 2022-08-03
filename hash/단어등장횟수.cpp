#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

string text;
string p;

// pi[i]: 0~i까지 prefix == suffix 최대 길이
vector<int> getPi()
{
  int j = 0;
  int n = p.size();
  vector<int> pi(n, 0);

  for (int i = 1; i < n; i++)
  {
    while (j > 0 && p[i] != p[j])
      j = pi[j - 1];

    if (p[i] == p[j])
      pi[i] = ++j;
  }

  return pi;
}

int kmp_algorithm()
{
  int ans = 0;
  vector<int> pi = getPi();

  int n = text.size();
  int m = p.size();
  int j = 0;

  for (int i = 0; i < n; i++)
  {
    while (j > 0 && text[i] != p[j])
      j = pi[j - 1];

    if (text[i] == p[j])
    {
      if (j == m - 1)
      {
        ans++;
        j = pi[j];
      }
      else
      {
        j++;
      }
    }
  }

  return ans;
}

int main(void)
{
  int T;

  cin >> T;

  for (int t = 1; t <= T; t++)
  {

    cin >> text;
    cin >> p;

    int ans = kmp_algorithm();

    printf("#%d %d\n", t, ans);
  }

  return 0;
}