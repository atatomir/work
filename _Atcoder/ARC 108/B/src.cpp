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

int n, u;
char s[maxN];

int main()
{
  //freopen("test.in", "r", stdin);

  scanf("%d\n%s", &n, s + 1);

  u = 0;
  for (int i = 1; i <= n; i++) {
    s[++u] = s[i];
    if (u >= 3 && s[u - 2] == 'f' && s[u - 1] == 'o' && s[u] == 'x')
      u -= 3;
  }

  printf("%d", u);


  return 0;
}
