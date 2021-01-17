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

const int maxN = 3011;
ll mod = 998244353;

int n, k;
ll dp[maxN][maxN]; // i frac, j value

void add(ll& a, ll b) {
  a += b;
  if (a >= mod) a -= mod;
}

int main()
{
  //freopen("test.in", "r", stdin);

  cin >> n >> k;

  dp[n][k] = 1;
  for (int i = n; i >= 1; i--) {
    for (int j = 1; j <= i; j++) {
      if (dp[i][j] == 0) continue;

      add(dp[i - 1][j - 1], dp[i][j]);
      if (2 * j <= i)
        add(dp[i][2 * j], dp[i][j]);

      //cerr << i << ' ' << j << ' ' << dp[i][j] << '\n';
    }
  }

  cout << dp[0][0];

  return 0;
}
