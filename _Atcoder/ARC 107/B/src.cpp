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

ll n, k;

ll sum(ll x) {
  return (x * (x + 1)) >> 1;
}

ll sumsq(ll x) {
  return (x * (x + 1) * (2LL * x + 1)) / 6;
}

ll comp(ll x) {
  ll lo = max(1LL, x - n);
  ll hi = min(n, x - 1);
  return hi - lo + 1;
}

int main()
{
  //freopen("test.in", "r", stdin);

  cin >> n >> k;
  if (k < 0) k = -k;

  ll ans = 0;

  for (ll x = 2; x <= 2LL * n - k; x++) {
    ans += comp(x) * comp(x + k);
  }

  cout << ans;


  return 0;
}
