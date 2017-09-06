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

#define maxN 21
#define mod 1000000007

int n, k, m, i, a, b, c, lim, conf;
int rest[maxN][maxN];

int bit;
ll dp[1 << maxN][maxN];

void add(ll &a, ll b) {
    a += b;
    if (a >= mod) a -= mod;
}

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

int set_one(int conf, int pos) {
    static ll aux;

    conf ^= 1 << pos;
    aux = conf >> (pos + 1);

    if (aux == 0) return conf;
    return conf ^ (zrs(aux) << (pos + 1));
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= k; i++) {
        scanf("%d%d%d", &a, &b, &c);
        rest[a][b] = c + 1;
    }

    lim = 1 << (n - 1);
    dp[0][0] = 1;
    for (int ray = 1; ray <= m; ray++) {

        for (i = 0; i <= n - 2; i++) {
            for (conf = 0; conf < lim; conf++) {
                if (dp[conf][i] == 0) continue;
                bit = (conf >> i) & 1;


                if (rest[ray][i + 1] == 0) {

                    if (bit == 1) {
                        add(dp[conf][i + 1], dp[conf][i]);
                    } else {
                        add(dp[conf][i + 1], dp[conf][i]);
                        add(dp[ set_one(conf, i) ][i + 1], dp[conf][i]);
                    }

                    continue;
                }

                if (rest[ray][i + 1] == 1) {

                    if (bit == 1) {
                        //! no way boss
                    } else {
                        add(dp[conf][i + 1], dp[conf][i]);
                    }

                    continue;
                }

                if (rest[ray][i + 1] == 2) {

                    if (bit == 1) {
                        add(dp[conf][i + 1], dp[conf][i]);
                    } else {
                        add(dp[ set_one(conf, i) ][i + 1], dp[conf][i]);
                    }

                    continue;
                }
            }
        }

        for (conf = 0; conf < lim; conf++) {
            dp[conf][0] = dp[conf][n - 1];
            //cerr << dp[conf][0] << ' ';
            for (i = 1; i < n; i++)
                dp[conf][i] = 0;
        }

        //cerr << '\n';
    }

    ll ans = 0;
    for (conf = 0; conf < lim; conf++)
        add(ans, dp[conf][0]);

    printf("%lld", ans);

    return 0;
}
