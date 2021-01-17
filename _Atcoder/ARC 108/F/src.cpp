#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

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

const int maxN = 200011;
const ll mod = 1000000007;

struct states {
  vector<ll> dp;
  ll mult;

  states() {
    dp = {0};
    mult = 1;
  }

  int depth() {
    return dp.size() - 1;
  }

  void expand() {
    dp.pb(0);
  }

  ll& operator[](int pos) {
    assert(pos <= depth());
    return dp[depth() - 1 - pos];
  }
};

int n, x, y;
vector<int> adj[maxN];

int best;
int dist[maxN], distX[maxN];
vector<int> vals;
ll ans;

ll poww(ll a, ll b) {
  ll ans = 1;
  while (b > 0) {
    if (b & 1) ans = (ans * a) % mod;
    b >>= 1;
    a = (a * a) % mod;
  }
  return ans;
}

void dfs(int node) {
  for (auto to: adj[node]) {
    if (dist[to]) continue;
    dist[to] = dist[node] + 1;
    if (dist[to] > dist[best]) best = to;
    dfs(to);
  }
}

int main()
{
  //freopen("test.in", "r", stdin);

  cin >> n;
  for (int i = 1; i < n; i++) {
    cin >> x >> y;
    adj[x].pb(y);
    adj[y].pb(x);
  }

  dist[1] = best = 1;
  dfs(1);

  x = best;
  memset(dist, 0, sizeof(dist));
  dist[x] = 1;
  best = x;
  dfs(x);

  y = best;
  memcpy(distX, dist, sizeof(dist));
  memset(dist, 0, sizeof(dist));

  dist[y] = 1; 
  best = y;
  dfs(y);

  for (int i = 1; i <= n; i++) {
    dist[i]--; distX[i]--;
    //cerr << dist[i] << ' ' << distX[i] << '\n';
  }

  ans = poww(2, n - 2) * dist[best];
  ans %= mod;

  best = 0;
  for (int i = 1; i <= n; i++) {
    if (i == x || i == y) continue;

    int mini = min(distX[i], dist[i]);
    int maxi = max(distX[i], dist[i]);

    vals.pb(maxi);
    best = max(best, mini);
  }

  /*cerr << best << '\n';
  for (auto e: vals) cerr << e << ' ';
  cerr << '\n';
  */

  sort(vals.begin(), vals.end());
  int pos = -1;

  ll last = 0;
  for (; best <= n; best++) {
    while (pos + 1 < vals.size() && vals[pos + 1] <= best)
      pos++;

    ll curr = poww(2, pos + 1);
    ans += (curr + mod - last) * best;
    ans %= mod;
    last = curr;

    //cerr << ans << '\n';
  } 

  ans = (ans * 2) % mod;
  cout << ans;

  return 0;
}
