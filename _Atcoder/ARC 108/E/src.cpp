#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
  cerr << "[";
  for (auto e : aux) cerr << e << ' ';
  cerr << "]";
  return cerr;
}

const int maxN = 2021;
const ll mod = 1000000007;

int n, a[maxN];
ll le[maxN][maxN], ri[maxN][maxN];
ll cnt[maxN][maxN], ans[maxN][maxN];

ll poww(ll a, ll b) {
  ll ans = 1;
  while (b > 0) {
    if (b & 1) ans = (ans * a) % mod;
    b >>= 1;
    a = (a * a) % mod;
  }
  return ans;
}

int zrs(int x) {
  return (x & (x - 1)) ^ x;
}

void add(ll *data, int pos, ll v) {
  while (pos <= n + 2) {
    data[pos] = (data[pos] + v) % mod;
    pos += zrs(pos);
  }
}

ll sum(ll *data, int pos) {
  ll ans = 0;
  while (pos > 0) {
    ans = (ans + data[pos]) % mod;
    pos -= zrs(pos);
  }
  return ans;
}

void compute(int l, int r) {
  if (a[l] > a[r]) return;
  ll k = sum(cnt[l], a[r]);

  if (k == 0) {
    ans[l][r] = 0;
    add(cnt[l], a[r], 1);
    return;
  } 

  ans[l][r] = sum(le[l], a[r]);
  ans[l][r] += mod + sum(ri[r], n + 1) - sum(ri[r], a[l]);
  ans[l][r] += k;
  ans[l][r] %= mod;
  ans[l][r] = (ans[l][r] * poww(k, mod - 2)) % mod;

  add(cnt[l], a[r], 1);
  add(le[l], a[r], ans[l][r]);
  add(ri[r], a[l], ans[l][r]);
}

int main()
{
  //freopen("test.in", "r", stdin);

  cin >> n;
  for (int i = 1; i <= n; i++) 
    cin >> a[i];

  a[0] = 0;
  a[n + 1] = n + 1;

  for (int i = 0; i <= n + 1; i++) a[i]++;

  for (int len = 1; len <= n + 1; len++) {
    for (int i = 0; i + len <= n + 1; i++) {
      compute(i, i + len);
    }
  } 

  cout << ans[0][n + 1];


  return 0;
}
