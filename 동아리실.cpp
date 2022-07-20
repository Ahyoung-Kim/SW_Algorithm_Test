#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>

using namespace std;

#define MOD 1000000007

int n;
long long cnt;
char str[10001];

void printSubsets(char arr[], int n)
{
  // arr[4] = { 'A', 'B', 'C', 'D' }, n = 4

  // 1 << n : 원소 n 개의 조합 개수
  // n이 4일 때 i: 0~15 : 0000 ~ 1111
  for (int i = 0; i < (1 << n); ++i)
  {
    printf("{ ");
    // & 연산자로 비트마킹
    for (int j = 0; j < n; ++j)
    {
      // 1 << j: 인덱스 j번째 비트마킹 0번째면 0001
      if (i & (1 << j))
        printf("%c ", arr[j]);
    }
    printf("}\n");
  }
}

void printBin(int num)
{
  printf("{ ");
  for (int i = 3; i >= 0; i--)
  {
    if (1 & (num >> i))
    {
      printf("1 ");
    }
    else
    {
      printf("0 ");
    }
  }
  printf(" }, ");
}

void dfs(int depth, int num)
{
  if (depth == n)
  {
    cnt++;
    return;
  }

  int next = 8 >> (str[depth] - 65);

  for (int i = next; i < 16; i++)
  {
    if ((num & i) && (next & i))
    {
      dfs(depth + 1, i);
    }
  }
}

void solution()
{

  // 첫째날은 A가 키를 가지고 있음
  // start = 1000
  int start = 8;

  // A = 0  -> 1000  -> 8 >> 0
  // B = 1  -> 0100  -> 8 >> 1
  // C = 2  -> 0010  -> 8 >> 2
  // D = 3  -> 0001  -> 8 >> 3
  int first = 8 >> (str[0] - 65);

  int num = start | first;

  for (int i = num; i < 16; i++)
  {
    if ((start & i) && (first & i))
    {
      dfs(1, i);
    }
  }

  cnt %= MOD;
}

int main(void)
{
  int T;

  cin >> T;

  for (int tc = 1; tc <= T; tc++)
  {
    cin >> str;
    n = strlen(str);
    cnt = 0;

    solution();

    printf("#%d %d\n", tc, cnt);
  }

  return 0;
}