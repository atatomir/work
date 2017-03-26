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

#define maxN 3011
#define maxH 1000000005
#define mod 666013

int n, m, i, j, x, y, aux, pi, pj;
int h[maxN];
vector<int> list[maxN];
vector< pair<int, int> > ord;

short dp[maxN][maxN];
ll ans;

int main()
{
    freopen("casute.in","r",stdin);
    freopen("casute.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
        ord.pb(mp(h[i], i));
    }

    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
    }

    sort(ord.begin(), ord.end());
    reverse(ord.begin(), ord.end());

    h[0] = maxH;

    for (i = 0; i < ord.size(); i++) {
        pi = ord[i].second;
        dp[pi][pi] = pi;

        for (j = 0; j < i; j++) {
            pj = ord[j].second;

            aux = 0;
            for (auto to : list[pi]) {
                if (h[ dp[to][pj] ] < h[aux])
                    aux = dp[to][pj];
            }

            dp[pi][pj] = dp[pj][pi] = aux;
        }
    }

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            ans = (ans * (n + 1)) + dp[i][j];
            ans %= mod;
        }
    }

    printf("%lld", ans);


    return 0;
}
