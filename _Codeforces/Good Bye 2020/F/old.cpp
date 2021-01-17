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

const int maxN = 500011;
const int alone = maxN - 2;
const ll mod = 1000000007;

int n, m, x, y, k;
vector< pair<int, int> > links[maxN];
vector<int> sol;

void add_link(int x, int y, int id) {
  if (x > y) swap(x, y);
  links[x].pb(mp(id, y));
}

void swipe(int node) {
  if (links[node].empty()) return;

  for (int i = 1; i < links[node].size(); i++)
    if (links[node][0] > links[node][i])
      swap(links[node][0], links[node][i]);

  sol.pb(links[node][0].first);

  for (int i = 1; i < links[node].size(); i++) {
    int x = links[node][0].second;
    int y = links[node][i].second;
    int id = links[node][i].first;

    if (x == y) continue;
    add_link(x, y, id);
  }
}

int main()
{
  freopen("test.in", "r", stdin);

  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &k);

    if (k == 1) {
      scanf("%d", &x);
      links[x].pb(mp(i, alone));
    } else {
      scanf("%d%d", &x, &y);
      add_link(x, y, i);
    }
  }

  for (int i = 1; i <= m; i++)
    swipe(i);

  ll ans = 1;
  for (int i = 1; i <= sol.size(); i++)
    ans = (ans * 2) % mod;

  printf("%lld %d\n", ans, sol.size());
  for (auto e : sol) printf("%d ", e);
  printf("\n");

  return 0;
}
