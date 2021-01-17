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

const int maxN = 100011;

int t, n, ans, last, x;

int main()
{
  //freopen("test.in", "r", stdin);

  cin >> t;
  for (int ti = 1; ti <= t; ti++) {
    ans = 0; last = -1;

    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> x;

      if (last < x) {
        last = x;
        ans++;
        continue;
      }

      if (last == x) {
        last = x + 1;
        ans++;
        continue;
      }
    }

    cout << ans << '\n';
  }


  return 0;
}
