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
const int maxN = 55;

int n, sum, cnt;
int a[maxN][maxN];
vector<int> adj[maxN];
bool used[maxN];

ll fact(ll n) {
  ll ans = 1;

  for (ll i = 1; i <= n; i++)
    ans = (ans * i) % mod;

  return ans;
}

void dfs(int node) {
  used[node] = true;
  cnt++;

  for (auto to: adj[node])
    if (!used[to])
      dfs(to);
}

ll solve() {
  for (int i = 1; i <= n; i++)
    adj[i].clear();

  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      bool ok = true;

      for (int k = 1; k <= n; k++)
        ok &= (a[i][k] + a[j][k] <= sum);

      if (ok) {
        adj[i].pb(j);
        adj[j].pb(i);
      }
    }
  }

  memset(used, 0, sizeof(used));
  ll ans = 1;
  for (int i = 1; i <= n; i++) {
    cnt = 0;

    if (used[i]) continue;
    dfs(i);

    ans *= fact(cnt);
    ans %= mod;
  }

  return ans;
}

int main()
{
  //freopen("test.in", "r", stdin);

  cin >> n >> sum;
  for (int i = 1; i <= n; i++) 
    for (int j = 1; j <= n; j++)
      cin >> a[i][j];

  ll ans = solve();

  for (int i = 1; i <= n; i++)
    for (int j = 1; j < i; j++)
      swap(a[i][j], a[j][i]);

  ans *= solve();
  ans %= mod;

  cout << ans;

  return 0;
}
