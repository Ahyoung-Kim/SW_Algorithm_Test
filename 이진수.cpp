#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>

using namespace std;

int n, m;

bool solution()
{

  for (int i = 0; i < n; i++)
  {
    if (m & (1 << i))
    {
      continue;
    }
    else
    {
      return false;
    }
  }

  return true;
}

int main(void)
{

  int T;

  cin >> T;

  for (int tc = 1; tc <= T; tc++)
  {
    cin >> n >> m;

    int ret = solution();

    printf("#%d ", tc);

    if (ret)
    {
      printf("ON\n");
    }
    else
    {
      printf("OFF\n");
    }
  }

  return 0;
}