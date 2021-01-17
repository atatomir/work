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

int n, x, y, c, m;
int col[maxN];
vector< pair<int, int> > adj[maxN];
vector<int> tree[maxN];
vector<int> deny[maxN];

void dfs(int node) {
  for (auto e: adj[node]) {
    int to = e.first;
    int nxt = e.second;

    if (col[to] != 0) continue;
    if (nxt == col[node]) {
      col[to] = -1;
    } else {
      col[to] = nxt;
    }

    tree[node].pb(to);
    tree[to].pb(node);

    dfs(to);
  }
}

int main()
{
  //freopen("test.in", "r", stdin);

  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> x >> y >> c;
    adj[x].pb(mp(y, c));
    adj[y].pb(mp(x, c));
  }

  col[1] = -1;
  dfs(1);

  for (int i = 1; i <= n; i++) {
    if (col[i] != -1) continue;

    for (auto &e: tree[i])
      e = col[e];

    sort(tree[i].begin(), tree[i].end());

    int val, pos;
    for (val = 1, pos = 0; true; val++) {
      while (pos < tree[i].size() && tree[i][pos] < val)
        pos++;

      if (pos == tree[i].size()) break;
      if (tree[i][pos] > val) break;
    }

    col[i] = val;
  }

  for (int i = 1; i <= n; i++)
    cout << col[i] << '\n';


  return 0;
}
