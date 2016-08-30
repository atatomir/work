#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 10011
#define maxT 41

#define base 1003
#define moddoo 1000000007
#define mod 9907

int n, t, i, j;
int dim[maxT];
int dad[maxT][maxN];
map<int, bool> deny;
vector< pair<int, int> > ord;

int dp[maxN];
vector<int> list[maxN];

int dont_use[maxN];
ll cnt[maxN];
ll full[maxN];



void dfs(int node) {
    dp[node] = 1;

    for (int to : list[node]) {
        dfs(to);
        dp[node] = (1LL * dp[node] * base + dp[to]) % moddoo;
    }
}

void solve(int id) {
    int i;

    for (i = 1; i <= dim[id]; i++) list[i].clear();
    for (i = 2; i <= dim[id]; i++)
        list[ dad[id][i] ].pb(i);
    for (i = 1; i <= dim[id]; i++)
        sort(list[i].begin(), list[i].end());

    dfs(1);
    for (i = 1; i <= dim[id]; i++)
        if (deny[dp[i]])
            return;

    dont_use[ dim[id] ]++;
    deny[dp[1]] = true;
}

int main()
{
    freopen("arbnr.in","r",stdin);
    freopen("arbnr.out","w",stdout);

    scanf("%d%d", &n, &t);
    for (i = 1; i <= t; i++) {
        scanf("%d", &dim[i]);
        dad[i][1] = 0;
        for (j = 2; j <= dim[i]; j++) scanf("%d", &dad[i][j]);
        ord.pb(mp(dim[i], i));
    }

    sort(ord.begin(), ord.end());
    for (auto e : ord)
        solve(e.second);

    cnt[1] = 1; full[1] = 1;
    for (i = 2; i <= n; i++) {
        full[i] = 0;

        for (j = 1; j < i; j++)
            full[i] += full[j] * cnt[i - j];

        full[i] %= mod;
        cnt[i] = (mod + full[i] - dont_use[i]) % mod;
    }

    printf("%d", cnt[n]);

    return 0;
}
