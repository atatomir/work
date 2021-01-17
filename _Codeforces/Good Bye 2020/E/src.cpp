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
const int maxBits = 61;
const ll mod = 1000000007;

int t, n;
ll x[maxN], cnt[maxBits];


int main()
{
  //freopen("test.in", "r", stdin);

  scanf("%d", &t);
  for (int ti = 1; ti <= t; ti++) {
    for (int i = 0; i < maxBits; i++)
      cnt[i] = 0;
  
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%lld", &x[i]);

      for (int bit = 0; bit < maxBits; bit++)
        if (x[i] & (1LL << bit))
          cnt[bit]++;
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
      ll sumAnd = 0;
      ll sumOr = 0;

      for (int bit = 0; bit < maxBits; bit++) {
        ll aux = 1LL << bit;

        if (x[i] & aux) {
          sumAnd += 1LL * cnt[bit] * (aux % mod);
          sumAnd %= mod;

          sumOr += 1LL * n * (aux % mod);
          sumOr %= mod;
        } else {
          sumOr += 1LL * cnt[bit] * (aux % mod);
          sumOr %= mod;
        }
      }

      ans += sumAnd * sumOr;
      ans %= mod;
    }

    printf("%lld\n", ans);
  }


  return 0;
}
