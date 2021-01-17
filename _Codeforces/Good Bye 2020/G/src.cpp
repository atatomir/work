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
#define prev myprev

ostream& operator<<(ostream& cerr, vector<ll> aux) {
  cerr << "[";
  for (auto e : aux) cerr << e << ' ';
  cerr << "]";
  return cerr;
}

const int maxN = 5000011;
const int maxM = 1000011;
const int sigma = 26;
const ll mod = 1000000007;

int n, q, stage, k, sz;
char s[maxN], t[maxM], aux[maxN];
int len[maxM], prev[maxM], ap[maxM];
int sum[maxM][sigma];
vector<int> rem;

void build_kmp() {
  int u = 0;
  prev[1] = 0;

  for (int i = 2; i <= sz; i++) {
    while (u != 0 && aux[u + 1] != aux[i]) 
      u = prev[u];

    if (aux[u + 1] == aux[i]) u++;
    prev[i] = u;
  }
}

int run_kmp(int l, int r) {
  int u = 0;
  int ans = 0;

  for (int i = l; i <= r; i++) {
    while (u != 0 && s[i] != aux[u + 1])
      u = prev[u];

    if (s[i] == aux[u + 1]) u++;
    //cerr << l << ' ' << r << ' ' << i << ' ' << u << '\n';
    if (u == sz) {
      ans++;
      u = prev[u];
    }
    //cerr << u << '\n';
  }

  rem.clear();
  while (u > 0) {
    rem.pb(u);
    u = prev[u];
  }
  rem.pb(0);

  return ans;
}

ll poww(ll a, ll b) {
  ll ans = 1;

  while (b > 0) {
    if (b & 1) ans = (ans * a) % mod;
    b >>= 1;
    a = (a * a) % mod;
  }

  return ans;
}

ll solve() {
  build_kmp();
  ap[0] = run_kmp(1, len[0]);
  for (int i = 1; i <= stage && i <= k; i++) {
    int mid = len[i] / 2 + 1;
    int l = max(1, mid - sz + 1);
    int r = min(len[i], mid + sz - 1);

    //cerr << i << ' ' << l << ' ' << r << '\n';

    ap[i] = run_kmp(l, r);
  }

  ll ans = 0;
  for (int i = 0; i <= stage && i <= k; i++) {
    //cerr << ap[i] << ' ';
    ans += ap[i] * poww(2, k - i);
    ans %= mod;
  }

  if (k <= stage) return ans;

  int r = len[stage];
  int l = r - sz;
  run_kmp(l, r);
  
  vector<int> suff = rem;

  reverse(aux + 1, aux + sz + 1);
  build_kmp();
  reverse(s + 1, s + sz + 1);

  l = 1;
  r = sz;
  run_kmp(l, r);
  vector<int> pref = rem;

  reverse(s + 1, s + sz + 1);
  reverse(aux + 1, aux + sz + 1);

  reverse(suff.begin(), suff.end());
  int pos = 0;

  for (auto e: suff) {
    while (e + pref[pos] + 1 > sz) pos++;
    if (e + pref[pos] + 1 == sz) {
      ans += sum[k][aux[e + 1] - 'a'];
      ans %= mod;
    }
  }

  return ans;
}

int main()
{
  //freopen("test.in", "r", stdin);

  scanf("%d%d\n%s\n%s", &n, &q, s + 1, t + 1);
  len[0] = strlen(s + 1);

  for (stage = 0; len[stage] < 1000000 && stage < n; stage++) {
    len[stage + 1] = len[stage] * 2 + 1;

    memcpy(s + len[stage] + 2, s + 1, len[stage]);
    s[len[stage] + 1] = t[stage + 1];
  }

  for (int i = stage + 1; i <= n; i++) {
    memcpy(sum[i], sum[i - 1], sigma * sizeof(sum[i][0]));
    for (int c = 0; c < sigma; c++)
      sum[i][c] = (sum[i][c] * 2) % mod;

    sum[i][t[i] - 'a']++;
    sum[i][t[i] - 'a'] %= mod;
  }

  for (int qi = 1; qi <= q; qi++) {
    scanf("%d %s", &k, aux + 1);
    sz = strlen(aux + 1);
    printf("%lld\n", solve());
    memset(aux, 0, sz + 3);
  }


  return 0;
}
