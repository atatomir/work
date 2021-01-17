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

ll S, P;

void ans(bool ok) {
  cout << (ok ? "Yes" : "No") << '\n';
  exit(0);
}

void subcheck(ll a) {
  if (a <= 0) return;
  ll b = S - a;
  if (b <= 0) return;
  if (a * b == P) ans(true);
}

void check(double approx) {
  ll x = floor(approx);

  for (int d = -10; d <= 10; d++)
    subcheck(x + d);
}

int main()
{
  //freopen("test.in", "r", stdin);

  cin >> S >> P;

  double delta = 1.0 * S * S - 4.0 * P;

  if (delta < 0) ans(false);
  double d = sqrt(1.00 * delta);
  double a1 = (-1.00 * S - d) / (-2.0);
  double a2 = (-1.00 * S + d) / (-2.0);

  check(a1);
  check(a2);
  ans(false);


  return 0;
}
