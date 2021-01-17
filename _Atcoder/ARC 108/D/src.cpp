#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

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

const ll mod = 1000000007;
const int maxN = 1011;

int n;
char aa, ab, ba, bb;
ll dp[maxN];

void ans(ll x) {
  cout << x << '\n';
  exit(0);
}

ll poww(ll a, ll b) {
  ll ans = 1;
  while (b > 0) {
    if (b & 1) ans = (ans * a) % mod;
    b >>= 1;
    a = (a * a) % mod;
  }
  return ans;
}

int main()
{
  //freopen("test.in", "r", stdin);

  scanf("%d\n%c\n%c\n%c\n%c", &n, &aa, &ab, &ba, &bb);
  if (n == 2) ans(1);

  dp[0] = 1;
  for (int i = 2; i <= n; i++) {
    for (int j = 0; j <= i - 2; j++)
      dp[i] = (dp[i] + dp[j]) % mod;
    //cerr << i << ' ' << dp[i] << '\n';
  }

  if (ab == 'A') {
    if (aa == 'A') {
      ans(1);
    } else {
      if (ba == 'B') {
        ans(poww(2, n - 3));
      } else { 
        ans(dp[n]); 
      }
    }
  } else {
    if (bb == 'B') {
      ans(1);
    } else {
      if (ba == 'A') {
        ans(poww(2, n - 3));
      } else {
        ans(dp[n]);
      }
    }
  }


  return 0;
}
