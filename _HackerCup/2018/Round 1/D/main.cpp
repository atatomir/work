#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const ll mod = 1000000007;
const ll maxN = 3011;

int t, ti;
ll n, m, i, j, Y, H, total;
ll a[maxN], b[maxN];
ll zombie[maxN];

ll best[maxN][maxN], cnt[maxN][maxN];
ll dp[maxN][maxN];

void add(ll &a, ll b) {
    a += b;
    if (a >= mod) a -= mod;
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

ll more(ll pos, ll x) {
    if (pos == 0) return 1;
    if (b[pos] <= x) return 0;
    return b[pos] - max(a[pos] - 1, x);
}

ll at_most(ll pos, ll x) {
    if (pos == 0) return 1;
    if (x < a[pos]) return 0;
    return min(b[pos], x) - a[pos] + 1;
}

ll solve() {
    ll i, j, p, k, aux, aux2;

    for (i = 0; i <= n; i++) {
        for (j = 0; j <= n; j++) {
            best[i][j] = 0;
            dp[i][j] = 0;
            cnt[i][j] = 0;
        }
    }

    for (p = 1; p <= n; p++) {
        if (zombie[p] == 0) continue;
        aux = 1;

        for (i = p; i > 0; i--) {
            if (zombie[i] >= zombie[p] && i != p) break;

            aux2 = aux;
            for (j = p; j <= n; j++) {
                if (zombie[j] > zombie[p]) break;

                best[i][j] = p;
                cnt[i][j] = aux2;
                aux2 = (aux2 * at_most(j, zombie[p])) % mod;
            }

            aux = (aux * at_most(i - 1, zombie[p])) % mod;
        }
    }

    dp[0][0] = 1;
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= i; j++) {
            if (dp[i][j] == 0) continue;

            for (k = i + 1; k <= n; k++) {
                if (best[i + 1][k] == 0) continue;

                aux = (dp[i][j] * cnt[i + 1][k]) % mod;
                aux = (aux * more(i, max(zombie[j], zombie[ best[i + 1][k] ]))) % mod;

                add(dp[k][ best[i + 1][k] ], aux);
            }
        }
    }

    ll sol = 0;
    for (i = 1; i <= n; i++) add(sol, dp[n][i]);

    sol = (total - sol + mod) % mod;
    sol = (sol * poww(total, mod - 2)) % mod;

    return sol;
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out", "w", stdout);

    scanf("%d", &t);
    cerr << "Solve " << t << " tests\n";

    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << '\n';

        total = 1;
        scanf("%lld%lld", &n, &m);

        for (i = 1; i <= n; i++) {
            zombie[i] = 0;
            a[i] = b[i] = 0;
        }

        for (i = 1; i < n; i++) {
            scanf("%lld%lld", &a[i], &b[i]);
            total *= b[i] - a[i] + 1;
            total %= mod;
        }

        for (i = 1; i <= m; i++) {
            scanf("%lld%lld", &Y, &H);
            zombie[Y] = max(zombie[Y], H);
        }

        printf("Case #%d: %lld\n", ti, solve());
    }


    return 0;
}
