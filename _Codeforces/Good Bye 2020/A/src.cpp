#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

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

const int maxN = 55;

int t, n, ans;
int x[maxN];
unordered_map<int, bool> M;

int main()
{
  //freopen("test.in", "r", stdin);

  cin >> t;
  for (int ti = 1; ti <= t; ti++) {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i];

    M.clear();
    ans = 0;

    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        int d = x[j] - x[i];

        if (!M[d]) ans++;
        M[d] = true;
      }
    }

    cout << ans << '\n';
  }


  return 0;
}
