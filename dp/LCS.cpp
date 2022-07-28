#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAX 1001

string str1;
string str2;
int LCS[MAX][MAX];

int solution()
{
  int ret = 0;

  for (int i = 1; i <= str1.size(); i++)
  {
    for (int j = 1; j <= str2.size(); j++)
    {
      if (str1[i - 1] == str2[j - 1])
      {
        LCS[i][j] = LCS[i - 1][j - 1] + 1;
      }
      else
      {
        LCS[i][j] = max(LCS[i][j - 1], LCS[i - 1][j]);
      }
      ret = max(LCS[i][j], ret);
    }
  }

  return ret;
}

void input()
{

  cin >> str1;
  cin >> str2;

  int n1 = str1.size();
  int n2 = str2.size();

  memset(LCS, 0, sizeof(LCS));
}

void print()
{

  for (int i = 0; i <= str1.size(); i++)
  {
    for (int j = 0; j <= str2.size(); j++)
    {
      printf("%d ", LCS[i][j]);
    }
    printf("\n");
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
    // int ans = 0;
    print();

    printf("#%d %d\n", tc, ans);
  }

  return 0;
}