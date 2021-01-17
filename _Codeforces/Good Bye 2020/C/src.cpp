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

int t, n, curr[4], nxt[4];
char s[maxN];

void upd(int &a, int b) {
  a = min(a, b);
}

int main()
{
  //freopen("test.in", "r", stdin);

  scanf("%d\n", &t);
  for (int ti = 0; ti < t; ti++) {
    scanf("%s\n", s);
    n = strlen(s);

    curr[0] = curr[1] = curr[2] = curr[3] = 0;
    for (int i = 0; i < n; i++) {
      nxt[0] = nxt[1] = nxt[2] = nxt[3] = i + 1;

      for (int act = 0; act < 4; act++) {
        upd(nxt[(act >> 1) | 2], curr[act] + 1);

        if ((i == 0 || (act & 2) || s[i - 1] != s[i]) &&
            (i <= 1 || (act & 1) || s[i - 2] != s[i]))
          upd(nxt[act >> 1], curr[act]);
      }

      for (int act = 0; act < 4; act++) {
        curr[act] = nxt[act];
      //  cerr << curr[act] << ' ';
      }
      //cerr << "\n";
    }

    int ans = min(min(curr[0], curr[1]), min(curr[2], curr[3]));
    printf("%d\n", ans);

    memset(s, 0, n + 2);
  }


  return 0;
}
