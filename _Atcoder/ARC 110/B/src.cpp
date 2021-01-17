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

const int maxN = 200011;

int n;
char s[maxN];
ll ans;

void check(int m) {
  for (int i = 0; i < n; i++) {
    char want = ((i + m) % 3 < 2 ? '1' : '0');
    if (s[i] != want) return;
  }

  int groups = (n + m + 2) / 3;
  ans += 10000000000 - groups + 1; 
}

int main()
{
  //freopen("test.in", "r", stdin);

  scanf("%d\n%s", &n, s);
  check(0);
  check(1);
  check(2);

  cout << ans;

  return 0;
}
