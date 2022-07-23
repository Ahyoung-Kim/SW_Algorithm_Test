#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;

typedef struct node
{
  string data;
  int left;
  int right;

  void set(string _data)
  {
    data = _data;
    left = right = 0;
  }
};

int N; // 정점 개수 1~1000
node tree[1001];
vector<string> arr;

bool is_digit(string str)
{
  char c = str[0];

  if (c == '+' || c == '-' || c == '/' || c == '*')
    return false;
  return true;
}

void input()
{
  int num;
  string data;
  int l, r;

  for (int i = 0; i < N; i++)
  {
    node nnode;
    cin >> num;
    cin >> data;

    nnode.set(data);

    if (!is_digit(data))
    {
      cin >> l >> r;
      nnode.left = l;
      nnode.right = r;
    }

    tree[num] = nnode;
  }
}

void set_arr(node curr)
{
  if (curr.left != 0)
  {
    set_arr(tree[curr.left]);
  }
  if (curr.right != 0)
  {
    set_arr(tree[curr.right]);
  }
  arr.push_back(curr.data);
}

int solution()
{
  double ret;
  double p1, p2;
  vector<double> s;

  for (int i = 0; i < arr.size(); i++)
  {
    string temp = arr[i];

    if (is_digit(temp))
    {
      s.push_back(stod(temp));
      continue;
    }

    p1 = s.back();
    s.pop_back();
    p2 = s.back();
    s.pop_back();

    switch (temp[0])
    {
    case '+':
      s.push_back(p2 + p1);
      break;
    case '-':
      s.push_back(p2 - p1);
      break;
    case '/':
      s.push_back(p2 / p1);
      break;
    case '*':
      s.push_back(p2 * p1);
      break;
    default:
      break;
    }
  }

  ret = s.back();
  return (int)ret;
}

int main()
{
  int test_case;
  int T = 10;

  for (test_case = 1; test_case <= T; test_case++)
  {
    cin >> N;
    arr.clear();
    input();

    set_arr(tree[1]);

    int ret = solution();

    printf("#%d %d\n", test_case, ret);
  }

  return 0;
}