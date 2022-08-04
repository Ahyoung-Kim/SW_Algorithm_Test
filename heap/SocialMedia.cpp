#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdlib>

using namespace std;

static int mSeed;
static int pseudo_rand(void)
{
  mSeed = mSeed * 431345 + 2531999;
  return mSeed & 0x7FFFFFFF;
}

static int follow_status[1005][1005];
static int answer_score;
static int n; // n >= 2 && n <= 1000
static int end_timestamp;
static int follow_ratio;   // follow_ratio >= 1 && follow_ratio <= 10000
static int make_ratio;     // make_ratio >= 1 && make_ratio <= 10000
static int like_ratio;     // like_ratio >= 1 && like_ratio <= 10000
static int get_feed_ratio; // get_feed_ratio >= 1 && get_feed_ratio <= 10000
static int post_arr[200000];
static int total_post_cnt;
static int min_post_cnt;

struct post
{
  // int id;
  int like;
  int timestamp;
  bool flag;
};

struct compare
{
  bool operator()(post a, post b)
  {
  }
};

struct user
{
  // int id;
  //  해당 유저가 작성한 게시글 ID
  vector<int> posts;
  // 해당 유저가 팔로우한 사용자 ID
  vector<int> follows;
};

user users[1001];
post posts[100001];

void init(int N)
{
  for (int i = 0; i < N + 1; i++)
  {
    users[i].posts.clear();
    users[i].follows.clear();
  }

  memset(posts, 0, sizeof(posts));
}

void follow(int uID1, int uID2, int timestamp)
{
  users[uID1].follows.push_back(uID2);
}

void makePost(int uID, int pID, int timestamp)
{
  post npost;
  npost.like = 0;
  npost.timestamp = timestamp;
  npost.flag = false;

  posts[pID] = npost;
  users[uID].posts.push_back(pID);
}

void like(int pID, int timestamp)
{
  posts[pID].like++;
}

void print(int N)
{

  for (int i = 1; i <= N; i++)
  {
    user _user = users[i];
    printf("uID %d\n", i);

    printf("작성 게시글\n");
    for (int j = 0; j < _user.posts.size(); j++)
    {
      int pId = _user.posts[j];
      post _post = posts[pId];
      printf("like: %d, timestamp: %d\n", _post.like, _post.timestamp);
    }
    printf("팔로우\n");
    for (int j = 0; j < _user.follows.size(); j++)
    {
      int fId = _user.follows[j];
      user flw = users[fId];
      printf("팔로우 %d\n", fId);
      for (int k = 0; k < flw.posts.size(); k++)
      {
        int pId = flw.posts[k];
        post _post = posts[pId];
        printf("like: %d, timestamp: %d\n", _post.like, _post.timestamp);
      }
    }
  }
}

void getFeed(int uID, int timestamp, int pIDList[])
{
  user curr = users[uID];
  priority_queue<int> pq;

  for (int i = 0; i < curr.posts.size(); i++)
  {
  }
  for (int i = 0; i < curr.follows.size(); i++)
  {
  }

  for (int i = 0; i < 10; i++)
  {
  }
}

static bool run()
{
  int uId1, uId2, pId, pIdList[10], ans_pIdList[10], rand_val;
  bool ret = true;

  scanf("%d%d%d%d%d%d%d", &mSeed, &n, &end_timestamp, &follow_ratio, &make_ratio, &like_ratio, &get_feed_ratio);
  init(n); // n은 사용자 수

  for (int uId1 = 1; uId1 <= n; uId1++)
  {
    follow_status[uId1][uId1] = 1;

    // 1~10개까지만
    int m = n / 10 + 1;
    if (m > 10)
      m = 10;
    for (int i = 0; i < m; i++)
    {
      uId2 = uId1;
      while (follow_status[uId1][uId2] == 1)
      {
        uId2 = pseudo_rand() % n + 1;
      }
      // uID1이 uID2를 팔로우
      follow(uId1, uId2, 1);
      follow_status[uId1][uId2] = 1;
    }
  }
  min_post_cnt = total_post_cnt = 1;

  for (int timestamp = 1; timestamp <= end_timestamp; timestamp++)
  {
    rand_val = pseudo_rand() % 10000;
    if (rand_val < follow_ratio)
    {
      uId1 = pseudo_rand() % n + 1;
      uId2 = pseudo_rand() % n + 1;
      int lim = 0;
      while (follow_status[uId1][uId2] == 1 || uId1 == uId2)
      {
        uId2 = pseudo_rand() % n + 1;
        lim++;
        if (lim >= 5)
          break;
      }
      if (follow_status[uId1][uId2] == 0)
      {
        follow(uId1, uId2, timestamp);
        follow_status[uId1][uId2] = 1;
      }
    }
    rand_val = pseudo_rand() % 10000;

    if (rand_val < make_ratio)
    {
      uId1 = pseudo_rand() % n + 1;
      post_arr[total_post_cnt] = timestamp;

      makePost(uId1, total_post_cnt, timestamp);
      total_post_cnt += 1;
    }

    rand_val = pseudo_rand() % 10000;

    if (rand_val < like_ratio && total_post_cnt - min_post_cnt > 0)
    {
      while (post_arr[min_post_cnt] < timestamp - 1000 && min_post_cnt < total_post_cnt)
        min_post_cnt++;

      if (total_post_cnt != min_post_cnt)
      {
        pId = pseudo_rand() % (total_post_cnt - min_post_cnt) + min_post_cnt;
        like(pId, timestamp);
      }
    }

    rand_val = pseudo_rand() % 10000;
    if (rand_val < get_feed_ratio && total_post_cnt > 0)
    {
      uId1 = pseudo_rand() % n + 1;
      getFeed(uId1, timestamp, pIdList);

      for (int i = 0; i < 10; i++)
      {
        scanf("%d", ans_pIdList + i);
      }

      for (int i = 0; i < 10; i++)
      {
        if (ans_pIdList[i] == 0)
          break;

        if (ans_pIdList[i] != pIdList[i])
        {
          ret = false;
        }
      }
    }
  }

  // print(n);

  return ret;
}

int main()
{
  //	freopen("sample_input.txt", "r", stdin);
  setbuf(stdout, NULL);
  int tc;
  scanf("%d%d", &tc, &answer_score);

  for (int t = 1; t <= tc; t++)
  {
    int score;
    for (int i = 0; i < 1005; i++)
      for (int j = 0; j < 1005; j++)
        follow_status[i][j] = 0;

    if (run())
      score = answer_score;
    else
      score = 0;

    printf("#%d %d\n", t, score);
  }
  return 0;
}