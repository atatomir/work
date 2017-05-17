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

int n, m, i, x, y, z, ans;
ll len;
vector< pair<int, ll> > list[maxN];

void dfs(int node, int root, ll act) {
    if (act < 0) return;
    ans++;

    for (auto to : list[node])
        if (to.first != root)
            dfs(to.first, node, act - to.second);
}

int main()
{
    freopen("test.in","r",stdin);
    freopen("test.ok","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i < n; i++) {
        scanf("%d%d%d", &x, &y, &z);
        list[x].pb(mp(y, z));
        list[y].pb(mp(x, z));
    }

    for (i = 1; i <= m; i++) {
        scanf("%d%lld", &x, &len);
        ans = 0;
        dfs(x, 0, len);

        printf("%d\n", ans);
    }


    return 0;
}
