#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#define MAX_NODE 10000

enum
{
  ADD_HEAD = 1,
  ADD_TAIL,
  ADD_NUM,
  REMOVE,
  PRINT,
  END = 99
};

void init();
void addNode2Head(int data);
void addNode2Tail(int data);
void addNode2Num(int data, int num);
void removeNode(int data);
int getList(int output[MAX_NODE]);

static void run()
{
  while (1)
  {
    int cmd, data, num, cnt, i;
    int output[MAX_NODE] = {0};

    scanf("%d", &cmd);
    switch (cmd)
    {
    case ADD_HEAD: // 1
      scanf("%d", &data);
      addNode2Head(data);
      break;
    case ADD_TAIL: // 2
      scanf("%d", &data);
      addNode2Tail(data);
      break;
    case ADD_NUM: // 3
      scanf("%d %d", &data, &num);
      addNode2Num(data, num);
      break;
    case REMOVE: // 4
      scanf("%d", &data);
      removeNode(data);
      break;
    case PRINT: // 5
      cnt = getList(output);
      i = 0;
      while (cnt--)
        printf("%d ", output[i++]);
      printf("\n");
      break;
    case END: // 99
      return;
    }
  }
}

int main(void)
{
  // setbuf(stdout, NULL);
  // freopen("sll_input.txt", "r", stdin);

  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; t++)
  {
    printf("#%d\n", t);
    init();
    run();
    printf("\n");
  }

  return 0;
}

struct Node
{
  int data;
  Node *next;
};

Node node[MAX_NODE];
int nodeCnt;
Node *head;

Node *getNode(int data)
{
  node[nodeCnt].data = data;
  node[nodeCnt].next = nullptr;
  return &node[nodeCnt++];
}

void init()
{
  head = (Node *)malloc(sizeof(Node));
  head->next = nullptr;
}

void addNode2Head(int data)
{
  Node *nnode = getNode(data);
  nnode->next = head->next;
  head->next = nnode;
}

void addNode2Tail(int data)
{
  Node *nnode = getNode(data);

  if (head->next == nullptr)
  {
    head->next = nnode;
    return;
  }

  Node *curr = head->next;

  while (curr->next != nullptr)
  {
    curr = curr->next;
  }
  curr->next = nnode;
}

void addNode2Num(int data, int num)
{
  if (num == 1)
  {
    addNode2Head(data);
    return;
  }

  Node *nnode = getNode(data);

  int temp = 1;
  Node *curr = head->next;
  while (curr != nullptr)
  {
    if (temp + 1 == num)
    {
      nnode->next = curr->next;
      curr->next = nnode;
      nodeCnt++;
      return;
    }
    curr = curr->next;
    temp++;
  }
}

void removeNode(int data)
{
  if (head->next == nullptr)
  {
    return;
  }

  if (head->next->data == data)
  {
    head->next = head->next->next;
    return;
  }

  Node *curr = head->next;
  while (curr->next != nullptr)
  {
    if (curr->next->data == data)
    {
      curr->next = curr->next->next;
      return;
    }
    curr = curr->next;
  }
  return;
}

int getList(int output[MAX_NODE])
{
  if (head->next == nullptr)
  {
    return 0;
  }

  Node *curr = head->next;
  int i = 0;

  while (curr != nullptr)
  {
    output[i] = curr->data;
    curr = curr->next;
    i++;
  }

  return i;
}