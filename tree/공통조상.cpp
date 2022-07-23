#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;

int V, E; // V: 10~10000
int u, w;

struct node
{
  int parent = 0;
  vector<int> child;
};

node tree[10001];
int parent;
int cnt;

void find_acsendant()
{
  vector<int> parents;
  node curr = tree[u];

  while (curr.parent != 0)
  {
    parents.push_back(curr.parent);
    curr = tree[curr.parent];
  }
  curr = tree[w];

  while (curr.parent != 0)
  {
    for (int i = 0; i < parents.size(); i++)
    {
      if (curr.parent == parents[i])
      {
        parent = curr.parent;
        return;
      }
    }
    curr = tree[curr.parent];
  }
}

void find_subset_num(node curr)
{

  cnt++;

  for (int i = 0; i < curr.child.size(); i++)
  {
    int childIdx = curr.child[i];
    find_subset_num(tree[childIdx]);
  }
}

void print()
{
  for (int i = 1; i <= V; i++)
  {
    node temp = tree[i];
    printf("%d의 부모: %d\n", i, temp.parent);
    printf("%d의 자식: ", i);
    for (int j = 0; j < temp.child.size(); j++)
    {
      printf("%d, ", temp.child[j]);
    }
    printf("\n=================================\n");
  }
}

int main(void)
{
  int T;

  cin >> T;

  for (int tc = 1; tc <= T; tc++)
  {
    cin >> V >> E >> u >> w;
    memset(tree, 0, sizeof(tree));
    parent = 1;
    cnt = 0;

    for (int i = 0; i < E; i++)
    {
      int x, y;
      cin >> x >> y;
      tree[x].child.push_back(y);
      tree[y].parent = x;
    }

    find_acsendant();
    find_subset_num(tree[parent]);

    printf("#%d %d %d\n", tc, parent, cnt);
  }

  return 0;
}