#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cstring>
using namespace std;

int heap[100001];
int cnt;

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void heapify()
{

  int child = cnt;
  int parent = child / 2;

  while (child > 1 && heap[child] > heap[parent])
  {
    swap(heap[child], heap[parent]);
    child = parent;
    parent = child / 2;
  }
}

void insert(int x)
{
  heap[++cnt] = x;

  int c = cnt;
  int p = c / 2;

  while (c > 1 && heap[c] > heap[p])
  {
    swap(heap[c], heap[p]);
    c = p;
    p = c / 2;
  }

  // heapify();
}

int remove()
{

  if (cnt == 0)
  {
    return -1;
  }

  int ret = heap[1];

  swap(heap[1], heap[cnt]);
  cnt--;

  int p = 1;
  int c = p * 2;

  if (c + 1 <= cnt)
  {
    // 왼쪽 자식, 오른쪽 자식 중 더 큰 자식의 인덱스
    c = (heap[c] > heap[c + 1]) ? c : c + 1;
  }

  while (c <= cnt && heap[c] > heap[p])
  {
    swap(heap[c], heap[p]);
    p = c;
    c = p * 2;

    if (c + 1 <= cnt)
    {
      c = (heap[c] > heap[c + 1]) ? c : c + 1;
    }
  }

  // heapify();

  return ret;
}

void print()
{
  for (int i = 0; i <= cnt; i++)
  {
    printf("%d ", heap[i]);
  }
  printf("\n");
}

vector<int> run()
{
  int N;
  int cmd;
  vector<int> ans;

  memset(heap, 0, sizeof(heap));
  cnt = 0;

  cin >> N;

  for (int i = 0; i < N; i++)
  {
    cin >> cmd;

    switch (cmd)
    {
    case 1:
      int x;
      cin >> x;
      insert(x);
      break;
    case 2:
      ans.push_back(remove());
      break;
    default:
      break;
    }
    // print();
  }
  return ans;
}

int main(void)
{

  int T;

  cin >> T;

  for (int tc = 1; tc <= T; tc++)
  {
    vector<int> ans = run();
    printf("#%d ", tc);
    for (int i = 0; i < ans.size(); i++)
    {
      printf("%d ", ans[i]);
    }
    printf("\n");
  }

  return 0;
}