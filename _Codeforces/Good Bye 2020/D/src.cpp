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

int t, n, x, y;
pair<int, int> w[maxN];
ll ans;

int main()
{
  //freopen("test.in", "r", stdin);

  scanf("%d", &t);
  for (int ti = 1; ti <= t; ti++) {
    scanf("%d", &n);
    ans = 0;

    for (int i = 1; i <= n; i++) {
      scanf("%d", &w[i].first);
      w[i].second = 0;

      ans += 1LL * w[i].first;
    }

    for (int i = 1; i < n; i++) {
      scanf("%d%d", &x, &y);
      w[x].second++;
      w[y].second++;
    }

    sort(w + 1, w + n + 1);
    reverse(w + 1, w + n + 1);
    printf("%lld ", ans);

    int pos = 1;
    for (int i = 2; i < n; i++) {
      while (w[pos].second == 1) pos++;
      w[pos].second--;
      ans += 1LL * w[pos].first;

      printf("%lld ", ans);
    }

    printf("\n");
  }


  return 0;
}
