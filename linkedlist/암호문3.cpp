#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

int N; //원본 암호문의 길이 2000~4000
int M; //명령어 개수 250~500

struct node
{
  int data;
  node *prev;
  node *next;
};

node *front;
node *rear;
int cnt;

void init()
{
  cnt = 0;
  front = new node;
  rear = new node;
  front->prev = front->next = nullptr;
  rear->prev = rear->next = nullptr;
}

node *getNode(int data)
{
  node *nnode = new node;
  nnode->data = data;
  nnode->prev = nnode->next = nullptr;

  return nnode;
}

void print()
{
  node *curr = front->next;
  for (int i = 0; i < 10; i++)
  {
    printf("%d ", curr->data);
    curr = curr->next;
  }
  printf("\n");
}

void insertOne(int data)
{
  node *nnode = getNode(data);

  if (front->next == nullptr)
  {
    front->next = nnode;
    rear->prev = nnode;
    cnt++;
    return;
  }

  rear->prev->next = nnode;
  nnode->prev = rear->prev;
  rear->prev = nnode;
  cnt++;
}

void insert(int x, int y, vector<int> s)
{

  node *snode = getNode(s[0]);
  node *enode = snode;
  node *tnode = snode;
  for (int i = 1; i < y; i++)
  {
    node *nnode = getNode(s[i]);
    tnode->next = nnode;
    nnode->prev = tnode;
    tnode = nnode;

    if (i == y - 1)
    {
      enode = nnode;
    }
  }

  if (x == 0)
  {
    node *nextNode = front->next;
    front->next = snode;
    enode->next = nextNode;
    nextNode->prev = enode;
    cnt += y;
    return;
  }
  if (x == cnt)
  {
    snode->prev = rear->prev;
    rear->prev->next = snode;
    rear->prev = enode;
    cnt += y;
    return;
  }

  int temp = 1;
  node *curr = front->next;

  while (curr != nullptr)
  {
    if (temp == x)
    {
      if (curr->next == nullptr)
      {
        curr->next = snode;
        snode->prev = curr;
        rear->prev = enode;
      }
      else
      {
        curr->next->prev = enode;
        enode->next = curr->next;
        curr->next = snode;
        snode->prev = curr;
      }
      cnt += y;
      return;
    }
    curr = curr->next;
    temp++;
  }
}

void remove(int x, int y)
{
  if (front->next == nullptr)
  {
    return;
  }
  if (x == 0)
  {
    node *curr = front->next;
    for (int i = 0; i < y; i++)
    {
      curr->next->prev = nullptr;
      curr = curr->next;
      front->next = curr;
    }
    cnt -= y;
    return;
  }

  int temp = 1;
  node *curr = front->next;
  while (curr->next != nullptr)
  {
    if (temp == x)
    {
      node *temp = curr->next;
      for (int i = 0; i < y; i++)
      {
        temp = temp->next;
      }
      curr->next = temp;

      if (temp == nullptr)
      {
        rear->prev = curr;
      }
      else
      {
        temp->prev = curr;
      }

      cnt -= y;
      return;
    }
    curr = curr->next;
    temp++;
  }
}

void add(int y, vector<int> s)
{

  node *snode = getNode(s[0]);
  node *enode = snode;
  node *tnode = snode;
  for (int i = 1; i < y; i++)
  {
    node *nnode = getNode(s[i]);
    tnode->next = nnode;
    nnode->prev = tnode;
    tnode = nnode;

    if (i == y - 1)
    {
      enode = nnode;
    }
  }

  cnt += y;

  if (front->next == nullptr)
  {
    front->next = snode;
    rear->prev = enode;
    return;
  }

  rear->prev->next = snode;
  snode->prev = rear->prev;
  rear->prev = enode;
}

int main()
{
  int test_case;
  int T = 10;
  char c;
  int x, y;

  for (test_case = 1; test_case <= T; test_case++)
  {
    cin >> N;

    init();
    for (int i = 0; i < N; i++)
    {
      int data;
      cin >> data;
      insertOne(data);
    }

    cin >> M;
    for (int i = 0; i < M; i++)
    {
      vector<int> s;
      cin >> c;
      switch (c)
      {
      case 'I':
        cin >> x >> y;

        for (int i = 0; i < y; i++)
        {
          int tmp;
          cin >> tmp;
          s.push_back(tmp);
        }

        insert(x, y, s);
        break;
      case 'D':
        cin >> x >> y;
        remove(x, y);
        break;
      case 'A':
        cin >> y;

        for (int i = 0; i < y; i++)
        {
          int tmp;
          cin >> tmp;
          s.push_back(tmp);
        }
        add(y, s);
        break;
      default:
        break;
      }
    }

    printf("#%d ", test_case);
    print();
  }

  return 0;
}