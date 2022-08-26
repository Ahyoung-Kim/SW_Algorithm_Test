#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef enum
{
  CMD_INIT,
  CMD_ADD,
  CMD_DELETE,
  CMD_CHANGE,
  CMD_SEARCH
} COMMAND;

typedef enum
{
  NAME,
  NUMBER,
  BIRTHDAY,
  EMAIL,
  MEMO
} FIELD;

typedef struct
{
  int count;
  char str[20];
} RESULT;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

struct info
{
  string name;
  string num;
  string birth;
  string email;
  string memo;
};

typedef pair<string, vector<info *>> p;
multimap<string, vector<info *>> db[5];

void print()
{

  for (int i = 0; i < 5; i++)
  {
    for (auto it = db[i].begin(); it != db[i].end(); it++)
    {
      string field = it->first;
      cout << field << ": ";
      for (int j = 0; j < it->second.size(); j++)
      {
        cout << it->second[j]->name << ", ";
      }
      cout << endl;
    }
    cout << "------------------------------------------" << endl;
  }
}

// DB 초기화
void InitDB()
{
  for (int i = 0; i < 5; i++)
  {
    db[i].clear();
  }
}

void addOne(int idx, string field, info *sinfo)
{

  auto it = db[idx].find(field);

  if (it != db[idx].end())
  {
    it->second.push_back(sinfo);
  }
  else
  { // 처음 추가
    vector<info *> temp;
    temp.push_back(sinfo);

    db[idx].insert(p(field, temp));
  }
}

// record 한 개 추가
void Add(char *name, char *number, char *birthday, char *email, char *memo)
{
  // cout << "add start" << endl;
  string temp[5] = {name, number, birthday, email, memo};

  info *sinfo = new info;
  sinfo->name = name;
  sinfo->num = number;
  sinfo->birth = birthday;
  sinfo->email = email;
  sinfo->memo = memo;

  for (int i = 0; i < 5; i++)
  {
    addOne(i, temp[i], sinfo);
  }

  // print();
  // cout << "add done" << endl;
}

// field 값이 str인 record 삭제 후, 삭제된 record 개수 출력, 없으면 0
int Delete(FIELD field, char *str)
{
  // cout << "delete start" << endl;
  auto it = db[field].find(str);

  if (it == db[field].end())
  {
    // cout << "delete done" << endl;
    return 0;
  }

  int ret = it->second.size();

  for (int i = 0; i < ret; i++)
  {
    info *dinfo = it->second[i];
    string temp[5];
    temp[0] = dinfo->name;
    temp[1] = dinfo->num;
    temp[2] = dinfo->birth;
    temp[3] = dinfo->email;
    temp[4] = dinfo->memo;

    for (int j = 0; j < 5; j++)
    {
      if (j == field)
      {
        continue;
      }

      auto fit = db[j].find(temp[j]);
      for (int k = 0; k < fit->second.size(); k++)
      {
        if (fit->second[k] == dinfo)
        {
          fit->second.erase(fit->second.begin() + k);
          break;
        }
      }
    }
  }

  db[field].erase(str);

  // print();
  // cout << "delete done" << endl;
  return ret;
}

// field 값이 str인 record를 찾고, 해당 record의 changefield 값을 changestr로 변경
// 변경한 record의 개수, 없으면 0
int Change(FIELD field, char *str, FIELD changefield, char *changestr)
{
  // cout << "change start" << endl;
  // print();

  auto it = db[field].find(str);

  if (it == db[field].end())
  {
    // cout << "change done" << endl;
    return 0;
  }

  int ret = it->second.size();
  string old;

  // cout << "change count: " << ret << endl;
  // cout << field << " " << str << " " << changefield << " " << changestr << endl;
  // print();

  for (int i = 0; i < ret; i++)
  {
    info *cinfo = it->second[i];

    switch (changefield)
    {
    case 0:
      old = cinfo->name;
      cinfo->name = changestr;
      break;
    case 1:
      old = cinfo->num;
      cinfo->num = changestr;
      break;
    case 2:
      old = cinfo->birth;
      cinfo->birth = changestr;
      break;
    case 3:
      old = cinfo->email;
      cinfo->email = changestr;
      break;
    case 4:
      old = cinfo->memo;
      cinfo->memo = changestr;
      break;
    default:
      break;
    }

    addOne(changefield, changestr, cinfo);

    if (field != changefield)
    {
      auto dit = db[changefield].find(old); // 예전 값을 찾아서
      for (int j = 0; j < dit->second.size(); j++)
      {
        if (dit->second[j] == cinfo)
        { // 기존 정보 삭제
          dit->second.erase(dit->second.begin() + j);
          break;
        }
      }
    }
  }

  if (field == changefield)
  {
    db[changefield].erase(old);
  }

  // print();
  // cout << "change done" << endl;

  return ret;
}

// field 값이 str인 record를 찾고 record 개수와 record의 returnfield 값을 반환
// result.str은 count 값이 0이거나 2 이상인 경우 무시
RESULT Search(FIELD field, char *str, FIELD ret_field)
{
  // cout << "search start" << endl;
  // print();
  RESULT result;
  result.count = 0;

  auto it = db[field].find(str);

  if (it == db[field].end())
  {
    // cout << "search done" << endl;
    return result;
  }

  result.count = it->second.size();

  if (result.count == 0 || result.count >= 2)
  {
    // cout << "search done" << endl;
    return result;
  }

  string ret;

  // cout << "[" << it->second[0]->name << ", ";
  // cout << it->second[0]->num << ", ";
  // cout << it->second[0]->birth << ", ";
  // cout << it->second[0]->email << ", ";
  // cout << it->second[0]->memo << "]" << endl;

  switch (ret_field)
  {
  case 0:
    ret = it->second[0]->name;
    break;
  case 1:
    ret = it->second[0]->num;
    break;
  case 2:
    ret = it->second[0]->birth;
    break;
  case 3:
    ret = it->second[0]->email;
    break;
  case 4:
    ret = it->second[0]->memo;
    break;
  default:
    break;
  }

  int i;
  for (i = 0; i < ret.size(); i++)
  {
    result.str[i] = ret[i];
  }
  result.str[i] = '\0';

  // cout << result.str << ", " << result.count << endl;
  // cout << "search done" << endl;
  return result;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

static int dummy[100];
static int Score, ScoreIdx;
static char name[20], number[20], birthday[20], email[20], memo[20];

static char lastname[10][5] = {"kim", "lee", "park", "choi", "jung", "kang", "cho", "oh", "jang", "lim"};
static int lastname_length[10] = {3, 3, 4, 4, 4, 4, 3, 2, 4, 3};

static int mSeed;
static int mrand(int num)
{
  mSeed = mSeed * 1103515245 + 37209;
  if (mSeed < 0)
    mSeed *= -1;
  return ((mSeed >> 8) % num);
}

static void make_field(int seed)
{
  int name_length, email_length, memo_length;
  int idx, num;

  mSeed = (unsigned int)seed;

  name_length = 6 + mrand(10);
  email_length = 10 + mrand(10);
  memo_length = 5 + mrand(10);

  num = mrand(10);
  for (idx = 0; idx < lastname_length[num]; idx++)
    name[idx] = lastname[num][idx];
  for (; idx < name_length; idx++)
    name[idx] = 'a' + mrand(26);
  name[idx] = 0;

  for (idx = 0; idx < memo_length; idx++)
    memo[idx] = 'a' + mrand(26);
  memo[idx] = 0;

  for (idx = 0; idx < email_length - 6; idx++)
    email[idx] = 'a' + mrand(26);
  email[idx++] = '@';
  email[idx++] = 'a' + mrand(26);
  email[idx++] = '.';
  email[idx++] = 'c';
  email[idx++] = 'o';
  email[idx++] = 'm';
  email[idx] = 0;

  idx = 0;
  number[idx++] = '0';
  number[idx++] = '1';
  number[idx++] = '0';
  for (; idx < 11; idx++)
    number[idx] = '0' + mrand(10);
  number[idx] = 0;

  idx = 0;
  birthday[idx++] = '1';
  birthday[idx++] = '9';
  num = mrand(100);
  birthday[idx++] = '0' + num / 10;
  birthday[idx++] = '0' + num % 10;
  num = 1 + mrand(12);
  birthday[idx++] = '0' + num / 10;
  birthday[idx++] = '0' + num % 10;
  num = 1 + mrand(30);
  birthday[idx++] = '0' + num / 10;
  birthday[idx++] = '0' + num % 10;
  birthday[idx] = 0;
}

static void cmd_init()
{
  scanf("%d", &ScoreIdx);

  InitDB();
}

static void cmd_add()
{
  int seed;
  scanf("%d", &seed);

  make_field(seed);

  Add(name, number, birthday, email, memo);
}

static void cmd_delete()
{
  int field, check, result;
  char str[20];
  scanf("%d %s %d", &field, str, &check);

  result = Delete((FIELD)field, str);
  if (result != check)
    Score -= ScoreIdx;
}

static void cmd_change()
{
  int field, changefield, check, result;
  char str[20], changestr[20];
  scanf("%d %s %d %s %d", &field, str, &changefield, changestr, &check);

  result = Change((FIELD)field, str, (FIELD)changefield, changestr);
  if (result != check)
    Score -= ScoreIdx;
}

static void cmd_search()
{
  int field, returnfield, check;
  char str[20], checkstr[20];
  scanf("%d %s %d %s %d", &field, str, &returnfield, checkstr, &check);

  RESULT result = Search((FIELD)field, str, (FIELD)returnfield);

  if (result.count != check || (result.count == 1 && (strcmp(checkstr, result.str) != 0)))
    Score -= ScoreIdx;
}

static void run()
{
  int N;
  scanf("%d", &N);
  for (int i = 0; i < N; i++)
  {
    int cmd;
    scanf("%d", &cmd);
    switch (cmd)
    {
    case CMD_INIT:
      cmd_init();
      break;
    case CMD_ADD:
      cmd_add();
      break;
    case CMD_DELETE:
      cmd_delete();
      break;
    case CMD_CHANGE:
      cmd_change();
      break;
    case CMD_SEARCH:
      cmd_search();
      break;
    default:
      break;
    }
  }
}

static void init()
{
  Score = 1000;
  ScoreIdx = 1;
}

int main()
{
  setbuf(stdout, NULL);
  freopen("input.txt", "r", stdin);

  int T;
  scanf("%d", &T);

  int TotalScore = 0;
  for (int tc = 1; tc <= T; tc++)
  {
    init();

    run();

    if (Score < 0)
      Score = 0;

    TotalScore += Score;
    printf("#%d %d\n", tc, Score);
  }
  printf("TotalScore = %d\n", TotalScore);

  return 0;
}