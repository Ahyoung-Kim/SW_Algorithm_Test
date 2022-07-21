#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

int N; // 수열의 길이 5~1000
int M; // 추가 횟수 1~1000
int L; // 출력할 인덱스 번호 6~N+M
int arr[1001] = {
    0,
};
int cnt = 0;

void insert(int idx, int data)
{

  for (int i = cnt; i > idx; i--)
  {
    arr[i] = arr[i - 1];
  }
  arr[idx] = data;
  cnt++;
}
void remove(int idx)
{

  for (int i = idx; i < cnt; i++)
  {
    arr[i] = arr[i + 1];
  }
  arr[cnt - 1] = 0;
  cnt--;
}
void change(int idx, int data)
{
  arr[idx] = data;
}
// int argc, char** argv
int main()
{
  int test_case;
  int T;
  char c;
  int idx, data;

  cin >> T;

  for (test_case = 1; test_case <= T; test_case++)
  {
    cin >> N >> M >> L;
    cnt = N;

    for (int i = 0; i < N; i++)
    {
      cin >> arr[i];
    }

    for (int i = 0; i < M; i++)
    {
      cin >> c;
      switch (c)
      {
      case 'I':
        cin >> idx >> data;
        insert(idx, data);
        break;
      case 'D':
        cin >> idx;
        remove(idx);
        break;
      case 'C':
        cin >> idx >> data;
        change(idx, data);
        break;
      default:
        break;
      }
    }

    int ret = -1;

    if (arr[L] != 0)
    {
      ret = arr[L];
    }

    printf("#%d %d\n", test_case, ret);
    for (int i = 0; i < cnt; i++)
    {
      arr[i] = 0;
    }
  }

  return 0;
}