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
const ll mod = 1000000007;

int n, m, x, y, k, alone;
int dad[maxN];
vector<int> sol;

int Find(int x) {
  if (dad[x] == x) return x;
  dad[x] = Find(dad[x]);
  return dad[x];
}

bool Merge(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x == y) return false;
  dad[x] = y;
  return true;
}

int main()
{
  //freopen("test.in", "r", stdin);

  scanf("%d%d", &n, &m);
  alone = m + 1;
  for (int i = 1; i <= alone; i++) dad[i] = i;

  for (int i = 1; i <= n; i++) {
    scanf("%d", &k);

    if (k == 1) {
      scanf("%d", &x);
      y = alone;
    } else {
      scanf("%d%d", &x, &y);
    }

    if (Merge(x, y)) sol.pb(i);
  }

  ll ans = 1;
  for (int i = 1; i <= sol.size(); i++)
    ans = (ans * 2) % mod;

  printf("%lld %d\n", ans, sol.size());
  for (auto e : sol) printf("%d ", e);
  printf("\n");

  return 0;
}
