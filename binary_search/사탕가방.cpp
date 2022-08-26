#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>

using namespace std;

typedef long long ll;

ll n, m;
vector<ll> num;

ll binary_search()
{
  ll s = 1;
  ll e = 2 * 1e18;
  ll mid; // 가방 개수
  ll ret = 0;

  while (s <= e)
  {
    mid = (s + e) / 2;

    ll cnt = 0;
    for (int i = 0; i < num.size(); i++)
    {
      cnt += num[i] / mid;
    }

    // printf("%lld, %lld\n", mid, cnt);

    if (cnt < m)
    {
      e = mid - 1;
    }
    else
    {
      ret = max(ret, mid);
      s = mid + 1;
    }
  }
  return ret;
}

void input()
{
  num.clear();

  scanf("%lld %lld", &n, &m);

  for (int i = 0; i < n; i++)
  {
    ll x;
    scanf("%lld", &x);
    num.push_back(x);
  }
}

int main(void)
{

  int T;

  cin >> T;

  for (int tc = 1; tc <= T; tc++)
  {

    input();
    ll ans = binary_search();
    printf("#%d %lld\n", tc, ans);
  }

  return 0;
}