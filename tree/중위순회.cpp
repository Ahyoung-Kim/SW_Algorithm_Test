#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

typedef struct node
{
  char data;
  int left;
  int right;

  void set(char _data)
  {
    data = _data;
    left = right = 0;
  }
};

int N; // 정점 개수 1~100
node tree[101];
int full;
int leaf;
int one;

void input_node()
{
  int num;
  char c;
  int l, r;

  if (N % 2 == 0)
  {
    full = (N / 2) - 1;
    leaf = N / 2;
    one = 1;
  }
  else
  {
    full = N / 2;
    leaf = (N / 2) + 1;
    one = 0;
  }

  for (int i = 1; i <= N; i++)
  {
    node nnode;
    // printf("%d ", i);
    cin >> num;
    cin >> c;

    nnode.set(c);
    if (1 <= i && i <= full)
    {
      cin >> l >> r;
      nnode.left = l;
      nnode.right = r;
    }
    else if (full < i && (i - full) <= one)
    {
      cin >> l;
      nnode.left = l;
    }

    tree[i] = nnode;
  }
}

void inorder(node curr)
{
  if (curr.left != 0)
    inorder(tree[curr.left]);
  printf("%c", curr.data);
  if (curr.right != 0)
    inorder(tree[curr.right]);
}

int main()
{
  int test_case;
  int T = 10;

  for (test_case = 1; test_case <= T; test_case++)
  {
    cin >> N;
    input_node();

    printf("#%d ", test_case);
    inorder(tree[1]);
    printf("\n");
  }

  return 0;
}