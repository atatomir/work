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

ll n, m, sum, x;

ll poww(ll a, ll b) {
  ll ans = 1;

  while (b > 0) {
    if (b & 1) ans = (ans * a) % mod;
    b >>= 1;
    a = (a * a) % mod;
  }

  return ans;
}

ll comb(ll n, ll k) {
  ll up = 1, down = 1;

  for (ll i = 0; i < k; i++) {
    up = (up * (n - i)) % mod;
    down = down * (i + 1) % mod;
  }

  return (up * poww(down, mod - 2)) % mod;
}

int main()
{
  //freopen("test.in", "r", stdin);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> x;
    sum += x;
  }

  cout << comb(n + m, sum + n);

  return 0;
}
