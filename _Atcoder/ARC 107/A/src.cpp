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

const ll mod = 998244353;

ll A, B, C, ans;

ll comp(ll x) {
  return ((x * (x + 1)) >> 1) % mod;
}

int main()
{
  //freopen("test.in", "r", stdin);

  cin >> A >> B >> C;
  ans = comp(A) * comp(B);
  ans %= mod;
  ans *= comp(C);
  ans %= mod;

  cout << ans;


  return 0;
}
