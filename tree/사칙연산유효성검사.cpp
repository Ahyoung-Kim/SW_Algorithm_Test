#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
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
node tree[201];
int full;
int leaf;
int one;

bool is_digit(char c)
{
  if (48 <= c && c <= 57)
    return true;
  return false;
}

void input_node()
{
  int num;
  string data;
  int l, r;

  if (N % 2 == 0)
  {
    full = (N / 2) - 1;
    leaf = N / 2;
    one = 1;
  }
  else
  {
    // N == 9 일 때, full = 4, leaf = 5, one = 0
    full = N / 2;
    leaf = (N / 2) + 1;
    one = 0;
  }

  for (int i = 1; i <= N; i++)
  {
    node nnode;
    cin >> num;
    cin >> data;

    nnode.set(data[0]);

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

void inorder(node curr, int idx)
{
  if (curr.left != 0)
    inorder(tree[curr.left], curr.left);
  printf("(%d, %c) ", idx, curr.data);
  if (curr.right != 0)
    inorder(tree[curr.right], curr.right);
}

vector<char> expression;

void solution(node curr, int dir, int depth)
{
  if (curr.left != 0)
    solution(tree[curr.left], -1, depth + 1);
  else if (curr.left == 0 && dir == -1)
  {
    for (int i = 0; i < depth - 1; i++)
    {
      // printf("( ");
      expression.push_back('(');
    }
  }

  // printf("%c ", curr.data);
  expression.push_back(curr.data);

  if (curr.right != 0)
    solution(tree[curr.right], 1, depth + 1);
  else if (curr.right == 0 && dir == 1)
  {
    // printf(") ");
    expression.push_back(')');
  }
}

bool is_possible()
{
  // (
  char prev = expression[0];

  for (int i = 1; i < expression.size(); i++)
  {
    char next = expression[i];
    // printf("next: %c, is_digit: %d\n", next, is_digit(next));

    if (next == '(' || next == ')')
    {
      prev = next;
      continue;
    }

    if (prev == '(')
    {
      if (!is_digit(next))
      {
        return false;
      }
    }
    else if (!is_digit(prev) && prev != ')')
    {
      if (!is_digit(next))
      {
        return false;
      }
    }
    else if (is_digit(prev))
    {
      if (is_digit(next))
      {
        return false;
      }
    }

    prev = next;
  }
  return true;
}

int main()
{
  int test_case;
  int T = 10;

  for (test_case = 1; test_case <= T; test_case++)
  {
    cin >> N;
    expression.clear();
    input_node();

    solution(tree[1], 0, 0);
    int ret = is_possible();
    printf("#%d %d\n", test_case, ret);
  }

  return 0;
}