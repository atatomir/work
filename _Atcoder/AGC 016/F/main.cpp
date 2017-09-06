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

#define maxN 16
#define mod 1000000007

int n, m, x, y, i, limit;
int adj[maxN], pre[1 << maxN];
ll dp[1 << maxN];
bool us[1 << maxN];

ll poww[maxN * maxN];


int any(int conf) {
    int i;
    int ans = 0;

    for (i = 0; i < n; i++) {
        if (conf & (1 << i)) {
            ans += pre[adj[i] & conf];
        }
    }

    return poww[ans];
}

int solve(int conf) {
    int act, act2, i;
    ll aux;
    if (us[conf]) return dp[conf];
    us[conf] = true;

    dp[conf] = 1;
    for (act = conf; act > 0; act = (act - 1) & conf) {
        act2 = conf ^ act;
        aux = 1;

        if ((act & 3) != 3 && (act & 3) != 0) continue;

        for (i = 0; i < n; i++) {
            if (act & (1 << i)) {
                aux *= poww[ pre[adj[i] & act2] ] + mod - 1;
                aux %= mod;
            }
        }

        for (i = 0; i < n; i++) {
            if (act2 & (1 << i)) {
                aux *= poww[ pre[adj[i] & act] ];
                aux %= mod;
            }
        }

        if (aux == 0) continue;

        if (act & 3)
            dp[conf] += aux * solve(act);
        else
            dp[conf] += aux * any(act);

        dp[conf] %= mod;
    }

    dp[conf] %= mod;
    return dp[conf];
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    poww[0] = 1;
    for (i = 1; i <= n * n; i++) poww[i] = (poww[i - 1] * 2) % mod;

    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        x--; y--;
        adj[x] |= 1 << y;
    }

    limit = 1 << n;
    for (i = 0; i < limit; i++) pre[i] = __builtin_popcount(i);

    cout << (poww[m] + mod - solve(limit - 1)) % mod;


    return 0;
}
