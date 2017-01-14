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

#define maxN 100011
#define mod 666013

int n, k, i, x, y;
bool coffee[maxN];
vector<int> list[maxN];
ll dp[maxN][2];

ll l[maxN], r[maxN];

void dfs(int node, int root) {

    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i];
        if (to != root) {
            dfs(to, node);
        } else {
            list[node][i] = list[node].back();
            list[node].pop_back();
            i--;
            continue;
        }
    }

    if (coffee[node]) {
        dp[node][0] = 0;
        dp[node][1] = 1;

        for (auto to : list[node])
            if (to != root)
                dp[node][1] = (dp[node][1] * (dp[to][0] + dp[to][1])) % mod;
    } else {
        dp[node][0] = 1;
        dp[node][1] = 0;

        for (auto to : list[node])
            if (to != root)
                dp[node][0] = (dp[node][0] * (dp[to][0] + dp[to][1])) % mod;

        for (int i = 0; i < list[node].size(); i++)
            l[i] = r[i] = (dp[ list[node][i] ][0] + dp[ list[node][i] ][1]);

        for (int i = 1; i < list[node].size(); i++)
            l[i] = (l[i - 1] * l[i]) % mod;

        for (int i = list[node].size() - 2; i >= 0; i--)
            r[i] = (r[i] * r[i + 1]) % mod;

        for (i = 0; i < list[node].size(); i++) {
            ll aux = dp[ list[node][i] ][1];
            if (i != 0) aux = (aux * l[i - 1]) % mod;
            if (i != list[node].size() - 1) aux = (aux * r[i + 1]) % mod;

            dp[node][1] += aux;
        }

        dp[node][1] %= mod;
    }
}

int main()
{
    freopen("karb2.in","r",stdin);
    freopen("karb2.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= k; i++) {
        scanf("%d", &x);
        coffee[x] = true;
    }

    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    dfs(1, 0);
    printf("%lld", dp[1][1]);
    cerr << dp[1][1];


    return 0;
}
