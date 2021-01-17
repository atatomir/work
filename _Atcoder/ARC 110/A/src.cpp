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

ll n, ans;

ll gcd(ll a, ll b) {
  if (a < b) swap(a, b);

  while (b > 0) {
    a %= b;
    swap(a, b);
  }

  return a;
}

int main()
{
  //freopen("test.in", "r", stdin);

  cin >> n;
  ans = 1;

  for (ll i = 2; i <= n; i++) {
    ans = (ans / gcd(ans, i)) * i;
  }

  cout << ans + 1;


  return 0;
}
