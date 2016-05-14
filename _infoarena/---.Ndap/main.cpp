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

#define maxN 17
#define mod 30103

int n, m, i, x, y, lim;
vector< pair<int, int> > edges;
int poww[maxN * maxN];

vector<int> bits[1 << maxN];
int cnt[1 << maxN];

int dp[1 << maxN];

void compute_state(int state) {
    int i;
    int act_lim = 1 << bits[state].size();
    int mask;

    if (bits[state].size() == 1) {
        dp[state] = 1;
        return;
    }

    int ans = 0;

    //! first bit is always 1
    for (int conn = 1; conn < act_lim - 1; conn += 2) {
        mask = 0;
        for (i = 0; i < bits[conn].size(); i++)
            mask |= 1 << bits[state][bits[conn][i]];

        ans = (ans + dp[mask] * poww[ cnt[state ^ mask] ]) % mod;
    }

    dp[state] = (poww[cnt[state]] - ans + mod) % mod;
}

int main()
{
    freopen("ndap.in","r",stdin);
    freopen("ndap.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        edges.pb(mp(x, y));
    }

    poww[0] = 1;
    for (i = 1; i <= m ; i++) poww[i] = (poww[i - 1] * 2) % mod;

    lim = 1 << n;
    for (int state = 0; state < lim; state++) {
        for (i = 0; i < n; i++)
            if ( (state >> i) & 1 ) bits[state].pb(i);

        for (auto e : edges)
            if ( (state >> e.first) & 1 )
                if ( (state >> e.second) & 1 )
                    cnt[state]++;
    }

    for (int state = 1; state < lim; state++)
        compute_state(state);

    printf("%d", dp[lim - 1]);


    return 0;
}
