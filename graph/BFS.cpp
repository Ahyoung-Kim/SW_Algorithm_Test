#include <stdio.h>
#include <malloc.h>

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
bool **visit;
int **maze;
int n;

struct node
{
  int x;
  int y;
  int depth;
  node *link;

  void set(int _x, int _y, int d)
  {
    x = _x;
    y = _y;
    depth = d;
    link = nullptr;
  }
};

node *front;
node *rear;
int cnt;

void init()
{
  cnt = 0;
  front = rear = (node *)malloc(sizeof(node));
  front = rear = nullptr;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      visit[i][j] = false;
    }
  }
}

bool is_empty()
{
  if (cnt == 0)
    return true;
  return false;
}

void push(int x, int y, int depth)
{
  node *nnode = new node;
  nnode->set(x, y, depth);

  if (cnt == 0)
  {
    front = rear = nnode;
    cnt++;
    return;
  }

  rear->link = nnode;
  rear = nnode;
  cnt++;
}

void pop()
{
  node *dnode = front;
  front = front->link;
  cnt--;
  delete dnode;
}

node *get_front()
{
  return front;
}

void print_queue()
{
  node *curr = front;
  while (curr != nullptr)
  {
    printf("(%d, %d, %d), ", curr->x, curr->y, curr->depth);
    curr = curr->link;
  }
  printf("\n");
}

void bfs_init(int map_size, int map[10][10])
{

  n = map_size;

  visit = new bool *[map_size + 1];
  maze = new int *[map_size + 1];
  for (int i = 0; i < map_size; i++)
  {
    visit[i] = new bool[map_size + 1];
    maze[i] = new int[map_size + 1];
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      maze[i][j] = map[i][j];
      visit[i][j] = false;
    }
  }
}

int bfs(int x1, int y1, int x2, int y2)
{

  init();

  visit[y1 - 1][x1 - 1] = true;
  push(x1 - 1, y1 - 1, 0);

  while (!is_empty())
  {
    node *curr = get_front();

    if (curr->x == x2 - 1 && curr->y == y2 - 1)
    {
      printf("%d\n", curr->depth);
      return curr->depth;
    }

    for (int i = 0; i < 4; i++)
    {
      int tx = curr->x + dx[i];
      int ty = curr->y + dy[i];

      if (tx < 0 || tx >= n || ty < 0 || ty >= n)
      {
        continue;
      }
      if (visit[ty][tx] || maze[ty][tx] == 1)
      {
        continue;
      }

      visit[ty][tx] = true;
      push(tx, ty, curr->depth + 1);
    }
    pop();
  }

  printf("-1\n");
  return -1;
}