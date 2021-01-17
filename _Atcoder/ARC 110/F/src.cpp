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

const int maxN = 111;

int n;
int p[maxN];
int id[maxN];
vector<int> sol;

void dfs(int node, int curr) {
  if (id[node]) return;

  id[node] = curr;
  dfs(p[node], curr);
}

int main()
{
  //freopen("test.in", "r", stdin);

  cin >> n;
  for (int i = 0; i < n; i++) 
    cin >> p[i];

  int ids = 2;
  while (ids > 1) {
    ids = 0;
    memset(id, 0, sizeof(id));

    for (int i = 0; i < n; i++) {
      if (id[i]) continue;
      dfs(i, ++ids);
    } 

    if (ids > 1) {
      bool any = false;

      for (int i = 0; i < n; i++) {
        int nxt = (i + p[i]) % n;
        if (id[i] != id[nxt]) {
          swap(p[i], p[nxt]);
          sol.pb(i);
          any = true;
          break;
        }
      }

      assert(any == true);
    }
  }

  for (int i = 1; i < n; i++)
    sol.pb(0);

  cout << sol.size() << '\n';
  for (auto e: sol) cout << e << '\n';

  return 0;
}
