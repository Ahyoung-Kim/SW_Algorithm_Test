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

typedef map<int, string> m;
typedef pair<int, string> p;
typedef m::iterator itr;
typedef pair<string, vector<int>> fp;
struct record
{
  m data;
};

map<int, record> info;
int id = 0;
map<string, map<int, int>> fmap[5];

void print()
{
  for (auto it = info.begin(); it != info.end(); it++)
  {
    cout << it->first << endl;
    m tmp = it->second.data;

    for (auto i = tmp.begin(); i != tmp.end(); i++)
    {
      cout << "[" << i->first << ", " << i->second << "] ";
    }
    cout << endl;
    cout << "-------------------------------" << endl;
  }

  for (int i = 0; i < 5; i++)
  {
    map<string, map<int, int>> tmp = fmap[i];

    for (auto it = tmp.begin(); it != tmp.end(); it++)
    {
      cout << "[" << it->first << ": ";
      for (auto k = it->second.begin(); k != it->second.end(); k++)
      {
        cout << k->first << " ";
      }
      cout << "]" << endl;
    }
    cout << "=====================" << endl;
  }
}

// DB 초기화
void InitDB()
{
  info.clear();
  id = 0;
  for (int i = 0; i < 5; i++)
  {
    fmap[i].clear();
  }
}

// record 한 개 추가
void Add(char *name, char *number, char *birthday, char *email, char *memo)
{
  string arr[5] = {name, number, birthday, email, memo};
  m tmp;
  /*tmp.insert(p(0, name));
  tmp.insert(p(1, number));
  tmp.insert(p(2, birthday));
  tmp.insert(p(3, email));
  tmp.insert(p(4, memo));*/
  for (int i = 0; i < 5; i++)
  {
    tmp.insert(p(i, arr[i]));
  }

  record addRecord;
  addRecord.data = tmp;
  info.insert(pair<int, record>(++id, addRecord));

  /*fmap[0].insert(fp(name, { id }));
  fmap[1].insert(fp(number, { id }));
  fmap[2].insert(fp(birthday, { id }));
  fmap[3].insert(fp(email, { id }));
  fmap[4].insert(fp(memo, { id }));*/

  // cout << "id: " << id << " -> ";
  for (int i = 0; i < 5; i++)
  {
    // cout << arr[i] << ", ";
    auto fit = fmap[i].find(arr[i]);
    if (fit != fmap[i].end())
    {
      fit->second.insert(pair<int, int>(id, 1));
    }
    else
    {
      map<int, int> tmp;
      tmp.insert(pair<int, int>(id, 1));
      fmap[i].insert(pair<string, map<int, int>>(arr[i], tmp));
    }
    /*auto fit = fmap[i].find(arr[i]);
    if (fit != fmap[i].end()) {
      printf("중복!\n");
      fit->second.insert(pair<int, int>(id, 1));
    }
    else {
      fmap[i].insert(fp(arr[i], { id }));
    }*/
  }
  // cout << endl;

  // print();
}

vector<int> find_id(FIELD field, char *str)
{
  // if(field == 2)
  // print();
  vector<int> ret;

  /*for (auto it = info.begin(); it != info.end(); it++) {
    m tmp = it->second.data;

    if (tmp.at(field) == str) {
      //cout << field << ", " << str << endl;
      ret.push_back(it->first);
    }
  }

  /*for (int i = 0; i < ret.size(); i++) {
    cout << ret[i] << " ";
  }
  cout << endl;*/

  auto fit = fmap[field].find(str);
  if (fit == fmap[field].end())
  {
    return ret;
  }

  // 아이디 맵
  map<int, int> id = fit->second;

  /*for (int i = 0; i < id.size(); i++) {
    int tmp = id[i];
    if (info.find(tmp) == info.end())
      continue;
    ret.push_back(tmp);
  }*/

  for (auto it = id.begin(); it != id.end(); it++)
  {
    int tmp = it->first;
    // cout << tmp << endl;

    // 삭제된 애면 건너 띠어
    if (info.find(tmp) == info.end())
      continue;

    ret.push_back(tmp);
  }

  return ret;
}

// field 값이 str인 record 삭제 후, 삭제된 record 개수 출력, 없으면 0
int Delete(FIELD field, char *str)
{
  vector<int> ret = find_id(field, str);

  if (ret.size() == 0)
    return 0;

  for (int i = 0; i < ret.size(); i++)
  {
    int id = ret[i];
    info.erase(id);
  }

  // cout << ret.size()<< endl;
  return ret.size();
}

// field 값이 str인 record를 찾고, 해당 record의 changefield 값을 changestr로 변경
// 변경한 record의 개수, 없으면 0
int Change(FIELD field, char *str, FIELD changefield, char *changestr)
{
  vector<int> ret = find_id(field, str);

  if (ret.size() == 0)
    return 0;

  for (int i = 0; i < ret.size(); i++)
  {
    int id = ret[i];
    string old = info.at(id).data[changefield];
    info.at(id).data[changefield] = changestr;

    // auto fit = fmap[changefield].find(old);
    fmap[changefield].at(old).erase(id);

    auto fit = fmap[changefield].find(changestr);
    if (fit != fmap[changefield].end())
    {
      fit->second.insert(pair<int, int>(id, 1));
    }
    else
    {
      map<int, int> tmp;
      tmp.insert(pair<int, int>(id, 1));
      fmap[changefield].insert(pair<string, map<int, int>>(changestr, tmp));
    }
  }

  // cout << ret.size() << endl;
  return ret.size();
}

// field 값이 str인 record를 찾고 record 개수와 record의 returnfield 값을 반환
// result.str은 count 값이 0이거나 2 이상인 경우 무시
RESULT Search(FIELD field, char *str, FIELD ret_field)
{
  RESULT result;
  result.count = 0;
  vector<int> ret = find_id(field, str);

  if (ret.empty())
  {
    return result;
  }

  result.count = ret.size();

  if (ret.size() == 1)
  {
    int id = ret.front();
    string ret_str = info.at(id).data[ret_field];
    int i;
    for (i = 0; i < ret_str.size(); i++)
    {
      result.str[i] = ret_str[i];
    }
    result.str[i] = '\0';
    // cout << result.str << endl;
  }

  // cout << result.count << " " << result.str << endl;
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

  /*map<string, vector<int>> temp;

  temp.insert(pair<string, vector<int>>("kim", { 1 }));

  string str = "lee";
  auto fit = temp.find(str);
  if (fit != temp.end()) {
    cout << "중복임" << endl;
    //fit->second.push_back(2);
    temp.erase(str);
  }
  else {
    cout << "중복 아님" << endl;
    temp.insert(pair<string, vector<int>>(str, { 2 }));
  }

  for (auto it = temp.begin(); it != temp.end(); it++) {
    cout << it->first << endl;
    for (int i = 0; i < it->second.size(); i++) {
      cout << it->second[i] << ", ";
    }
    cout << endl;
  }
  cout << endl;

  string n = "kim";
  string num = "1";
  string b = "1999";
  string e = "a.com";
  string memo = "aaa";
  map<string, string> m;
  m.insert(pair<string, string>("name", n));
  m.insert(pair<string, string>("number", num));
  m.insert(pair<string, string>("birthday", b));
  m.insert(pair<string, string>("email", e));
  m.insert(pair<string, string>("memo", memo));
  record rcd;
  rcd.m = m;

  sinfo.push_back(rcd);

  map<string, string> tmp = sinfo[0].m;
  for (auto it = tmp.begin(); it != tmp.end(); it++) {
    cout << it->first << ", " << it->second << endl;
  }*/

  return 0;
}