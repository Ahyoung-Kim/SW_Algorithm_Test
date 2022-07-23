#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <queue>

using namespace std;

#define CMD_MKDIR 1
#define CMD_RM 2
#define CMD_CP 3
#define CMD_MV 4
#define CMD_FIND 5
#define CMD_PRINT 6

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

class Node
{
public:
  string name;
  vector<Node *> children;

  Node(char _name[7])
  {
    name = _name;
  }
  Node(string _name)
  {
    name = _name;
  }
};

Node *root;
int cnt;

Node *find_path(char path[PATH_MAXLEN + 1], bool rmFlag)
{

  Node *curr = root;
  string pathStr = path;
  string next;
  int prev = 1;

  for (int i = 1; i < pathStr.size(); i++)
  {
    if (pathStr[i] == '/')
    {
      next = pathStr.substr(prev, i - prev);
      prev = i + 1;

      for (int j = 0; j < curr->children.size(); j++)
      {
        if (curr->children[j] == nullptr)
          continue;

        Node *child = curr->children[j];
        if (child->name == next)
        {

          if (rmFlag && i == pathStr.size() - 1)
          {
            curr->children[j] = nullptr;
          }

          curr = child;
          break;
        }
      }
    }
  }

  return curr;
}

// 루트 디렉토리 생성
// n: 최대 디렉토리 개수 5~50000
void init(int n)
{
  char path[] = "/";
  root = new Node(path);
  cnt = 0;
}

// path 디렉토리 하위에 name 이름을 가진 디렉토리 생성
// path: 상위 디렉토리 경로 length: 1~1999
// name: 생성할 디렉토리 이름 length: 2~6
void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1])
{
  Node *nnode = new Node(name);

  Node *dest = find_path(path, false);

  cnt++;

  for (int i = 0; i < dest->children.size(); i++)
  {
    if (dest->children[i] == nullptr)
    {
      dest->children[i] = nnode;
      return;
    }
  }

  dest->children.push_back(nnode);
}

// path 디렉토리와 그 모든 하위 디렉토리 삭제
void cmd_rm(char path[PATH_MAXLEN + 1])
{

  Node *start = find_path(path, true);
  queue<Node *> dnodes;
  dnodes.push(start);

  while (!dnodes.empty())
  {
    Node *curr = dnodes.front();
    dnodes.pop();

    for (int i = 0; i < curr->children.size(); i++)
    {
      if (curr->children[i] == nullptr)
        continue;
      dnodes.push(curr->children[i]);
      curr->children[i] = nullptr;
    }

    delete curr;
    cnt--;
  }
}

// dstPath 디렉토리 하위에 srcPath의 디렉토리와 그 모든 하위 디렉토리 복사 1~1999
void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1])
{
  Node *destNode = find_path(dstPath, false); // dest 경로 마지막 노드
  Node *srcNode = find_path(srcPath, false);  // src 경로 마지막 노드

  queue<Node *> q;  // 기존 경로 노드 담을 큐
  queue<Node *> q2; // 복사할 경로 노드 담을 큐

  q.push(srcNode);

  Node *temp = new Node(srcNode->name); // 새로운 노드 생성
  destNode->children.push_back(temp);   // destNode 에 새로운 노드 연결
  q2.push(temp);

  while (!q.empty())
  {
    Node *curr = q.front();   // 기존 노드
    Node *curr2 = q2.front(); // 새 노드
    q.pop();
    q2.pop();

    for (int i = 0; i < curr->children.size(); i++)
    {
      if (curr->children[i] != nullptr)
      {
        Node *nnode = new Node(curr->children[i]->name); // 새노드 생성
        curr2->children.push_back(nnode);                // 자식 노드에 추가
        q.push(curr->children[i]);
        q2.push(nnode);
        cnt++;
      }
    }
  }
}

// dstPath 디렉토리 하위에 srtPath 의 디렉토리와 그 모든 하위 디렉토리 이동 1~1999
void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1])
{
  Node *src = find_path(srcPath, true);

  Node *dest = find_path(dstPath, false);

  dest->children.push_back(src);
}

// path 디렉토리의 모든 하위 디렉토리 개수 반환
int cmd_find(char path[PATH_MAXLEN + 1])
{
  Node *findNode = find_path(path, false);
  queue<Node *> q;
  q.push(findNode);
  int size = 0;

  while (!q.empty())
  {
    Node *curr = q.front();
    q.pop();
    size++;

    for (int i = 0; i < curr->children.size(); i++)
    {
      if (curr->children[i] != nullptr)
      {
        q.push(curr->children[i]);
      }
    }
  }
  size--;
  return size;
}

void cmd_print(Node *curr, Node *parent)
{
  cout << "parent: " << parent->name << endl;
  cout << "curr: " << curr->name;
  cout << ", childeren size: " << curr->children.size() << endl;
  for (int i = 0; i < curr->children.size(); i++)
  {
    if (curr->children[i] == nullptr)
      continue;
    cout << curr->children[i]->name << ", ";
  }
  cout << endl;

  for (int i = 0; i < curr->children.size(); i++)
  {
    if (curr->children[i] == nullptr)
      continue;
    cmd_print(curr->children[i], curr);
  }
}

static bool run(int m)
{

  bool isAccepted = true;
  int cmd;
  char name[NAME_MAXLEN + 1];
  char path1[PATH_MAXLEN + 1], path2[PATH_MAXLEN + 1];

  while (m--)
  {

    scanf("%d", &cmd);

    if (cmd == CMD_MKDIR)
    {
      scanf("%s%s", path1, name);
      cmd_mkdir(path1, name);
    }
    else if (cmd == CMD_RM)
    {
      scanf("%s", path1);
      cmd_rm(path1);
    }
    else if (cmd == CMD_CP)
    {
      scanf("%s%s", path1, path2);
      cmd_cp(path1, path2);
    }
    else if (cmd == CMD_MV)
    {
      scanf("%s%s", path1, path2);
      cmd_mv(path1, path2);
    }
    else if (cmd == CMD_PRINT)
    {
      cmd_print(root, root);
    }
    else
    {
      int ret;
      int answer;

      scanf("%s", path1);
      ret = cmd_find(path1);
      scanf("%d", &answer);

      isAccepted &= (ret == answer);
    }
  }

  return isAccepted;
}

int main(void)
{

  int test, T;
  int n, m;

  // freopen("sample_input.txt", "r", stdin);

  setbuf(stdout, NULL);

  scanf("%d", &T);

  for (test = 1; test <= T; ++test)
  {

    scanf("%d%d", &n, &m);

    init(n);

    if (run(m))
    {
      printf("#%d 100\n", test);
    }
    else
    {
      printf("#%d 0\n", test);
    }
  }

  /*char name[] = "/aa/hello/new/world/";
  string str = name;
  string str2;
  int prev = 1;
  printf("size: %d\n", str.size());

  for (int i = 1; i < str.size(); i++) {
    if (str[i] == '/') {
      printf("prev: %d. i: %d\n", prev, i);
      str2 = str.substr(prev, i - prev);
      prev = i + 1;
      cout << str2 <<", " << str2.size() << endl;
    }
  }

  string a = "hello";
  string b = "hello";
  string c = "world";
  char d[] = "hello";

  if (a == d) {
    cout << "같음" << endl;
  }
  if (a != c) {
    cout << "다름" << endl;
  }*/

  return 0;
}