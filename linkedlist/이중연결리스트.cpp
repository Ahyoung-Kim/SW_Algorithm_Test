#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

#define MAX_NODE 10000

enum
{
  ADD_HEAD = 1,
  ADD_TAIL,
  ADD_NUM,
  FIND,
  REMOVE,
  PRINT,
  PRINT_REVERSE,
  END = 99
};

void init();
void addNode2Head(int data);
void addNode2Tail(int data);
void addNode2Num(int data, int num);
int findNode(int data);
void removeNode(int data);
int getList(int output[MAX_NODE]);
int getReversedList(int output[MAX_NODE]);

static void run()
{
  while (1)
  {
    int cmd, data, num, cnt, i = 0;
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
    case FIND: // 4
      scanf("%d", &data);
      num = findNode(data);
      printf("%d\n", num);
      break;
    case REMOVE: // 5
      scanf("%d", &data);
      removeNode(data);
      break;
    case PRINT: // 6
      cnt = getList(output);
      while (cnt--)
        printf("%d ", output[i++]);
      printf("\n");
      break;
    case PRINT_REVERSE: // 7
      cnt = getReversedList(output);
      while (cnt--)
        printf("%d ", output[i++]);
      printf("\n");
      break;
    case END:
      return;
    }
  }
}

int main(void)
{
  // setbuf(stdout, NULL);
  // freopen("dll_input.txt", "r", stdin);

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
  Node *prev;
  Node *next;
};

Node node[MAX_NODE];
int nodeCnt;
Node *head;

Node *getNode(int data)
{
  node[nodeCnt].data = data;
  node[nodeCnt].prev = nullptr;
  node[nodeCnt].next = nullptr;
  return &node[nodeCnt++];
}

void init()
{
  head = (Node *)malloc(sizeof(Node));
  head->prev = head->next = nullptr;
}

void addNode2Head(int data)
{
  Node *nnode = getNode(data);

  if (head->next == nullptr)
  {
    head->next = nnode;
    return;
  }

  head->next->prev = nnode;
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
  nnode->prev = curr;
  return;
}

void addNode2Num(int data, int num)
{
  if (num == 1)
  {
    addNode2Head(data);
  }

  Node *nnode = getNode(data);
  int temp = 1;
  Node *curr = head->next;
  while (curr != nullptr)
  {
    if (temp + 1 == num)
    {
      if (curr->next == nullptr)
      {
        curr->next = nnode;
        nnode->prev = curr;
      }
      else
      {
        curr->next->prev = nnode;
        nnode->next = curr->next;
        nnode->prev = curr;
        curr->next = nnode;
      }
      return;
    }
    curr = curr->next;
    temp++;
  }
}

int findNode(int data)
{
  if (head->next == nullptr)
  {
    return 0;
  }
  int i = 1;
  Node *curr = head->next;
  while (curr != nullptr)
  {
    if (curr->data == data)
    {
      return i;
    }
    curr = curr->next;
    i++;
  }
  return 0;
}

void removeNode(int data)
{
  if (head->next == nullptr)
  {
    return;
  }
  if (head->next->data == data)
  {
    head->next->prev = nullptr;
    head->next = head->next->next;
    return;
  }

  Node *curr = head->next;
  while (curr->next != nullptr)
  {
    if (curr->next->data == data)
    {
      curr->next->prev = curr;
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
    return 0;

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

int getReversedList(int output[MAX_NODE])
{
  if (head->next == nullptr)
    return 0;

  Node *curr = head->next;
  int i = 0;
  while (curr->next != nullptr)
  {
    curr = curr->next;
  }

  while (curr != nullptr)
  {
    output[i] = curr->data;
    curr = curr->prev;
    i++;
  }

  return i;
}