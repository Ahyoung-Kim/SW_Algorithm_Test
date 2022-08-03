#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

#define MAX_INPUT 10000
#define MAX_NUM 30000

static int input[MAX_INPUT];

static unsigned int seed = 13410;

struct node
{
  int id;
  int income;
  node *link;
};

node *head;
int len;

void init()
{
  head = (node *)malloc(sizeof(node));
  head->link = nullptr;
  len = 0;
}

void addUser(int uID, int height)
{
  printf("insert: %d %d\n", uID, height);
  node *nnode = (node *)malloc(sizeof(node));
  nnode->id = uID;
  nnode->income = height;
  nnode->link = nullptr;

  if (len == 0)
  {
    head->link = nnode;
    len++;
    return;
  }

  node *curr = head;
  int cnt = 0;

  while (curr->link != nullptr)
  {
    if (
        (curr->link->income < height) ||
        ((curr->link->income == height) && (curr->link->id > uID)))
    {
      nnode->link = curr->link;
      curr->link = nnode;
      len++;

      if (len > 10)
      {
        while (cnt < 10)
        {
          // printf("curr: %d, %d\n", curr->id, curr->income);
          curr = curr->link;
          cnt++;
        }
        curr->link = nullptr;
        len = 10;
      }

      return;
    }

    curr = curr->link;
    cnt++;
  }

  if (cnt < 10)
  {
    curr->link = nnode;
    len++;
  }
}

void print()
{
  node *curr = head->link;

  while (curr != nullptr)
  {
    printf("(%d, %d) ", curr->id, curr->income);
    curr = curr->link;
  }
  printf("\n");
}

int getTop10(int result[10])
{
  node *curr = head->link;
  int i = 0;
  int ans = 0;

  while (curr != nullptr)
  {
    result[i] = curr->id;
    ans += curr->id;
    i++;
    curr = curr->link;
  }

  printf("ans: %d\n", ans);
  return i;
}

static unsigned int pseudoRand()
{
  seed = seed * 214013 + 2531011;
  return (unsigned int)(seed >> 11) % MAX_NUM;
}

static void makeInput(int inputLen)
{
  for (int i = 0; i < inputLen; i++)
  {
    input[i] = pseudoRand();
  }
}

static int run()
{
  int N, userNum, uID = 0;
  int score = 100, result[10], cnt;
  int sum, check;
  scanf("%d", &N);
  for (int i = 0; i < N; i++)
  {
    scanf("%d", &userNum);
    makeInput(userNum);
    for (int j = 0; j < userNum; j++)
    {
      addUser(uID++, input[j]);
    }
    print();
    cnt = getTop10(result);

    sum = 0;
    for (int j = 0; j < cnt; j++)
      sum += result[j];
    scanf("%d", &check);
    if (check != sum)
      score = 0;
  }
  return score;
}

int main(void)
{
  setbuf(stdout, NULL);
  // freopen("partial_sort_input.txt", "r", stdin);
  int T;
  scanf("%d", &T);
  for (int tc = 1; tc <= T; tc++)
  {
    init();
    printf("#%d %d\n", tc, run());
  }
  return 0;
}