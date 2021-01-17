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

const int maxN = 1000011;
const ll mod = 1000000007;

int n;
char s[maxN];
ll dp[maxN];
int nxt[maxN][4], last[maxN], xsum[maxN], ans;

int main()
{
  //freopen("test.in", "r", stdin);

  scanf("%d\n%s", &n, s + 1);

  for (int i = 1; i <= n; i++) 
    xsum[i] = xsum[i - 1] ^ (s[i] - 'A' + 1);

  last[n] = n + 1;
  for (int i = n - 1; i >= 1; i--) 
    last[i] = (s[i] == s[i + 1] ? last[i + 1] : i + 1);

  nxt[n + 1][0] = nxt[n + 1][1] = nxt[n + 1][2] = nxt[n + 1][3] = n + 1;
  for (int i = n; i >= 1; i--) {
    memcpy(nxt[i], nxt[i + 1], sizeof(nxt[i]));
    nxt[i][xsum[i]] = i;
  }

  if (last[1] == n + 1) {
    cout << 1;
    return 0;
  }

  dp[0] = 1;
  for (int i = 0; i < n; i++) {
    int bg = last[i + 1];

    for (int act = 1; act <= 3; act++) {
      int src = act ^ xsum[i];
      int pos = nxt[bg][src];

      if (act == (s[i + 1] - 'A' + 1)) 
        pos = i + 1;

      dp[pos] = (dp[pos] + dp[i]) % mod;
    } 

    if (xsum[i] != xsum[n]) {
      ans = (1LL * ans + dp[i]) % mod;
      //cerr << i << ' ' << dp[i] << '\n';
    }
  }


  printf("%d", ans);


  return 0;
}
