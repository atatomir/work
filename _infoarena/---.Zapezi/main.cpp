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

#define maxN 10011

int n, i, x, y, d;
vector< pair<int, int> > list[maxN];
int ans;

bool us[maxN];
pair<int, int> best;


void dfs(int node, int v) {
    us[node] = true;
    best = max(best, mp(v, node));

    for (auto to : list[node])
        if (!us[to.first])
            dfs(to.first, v + to.second);
}

int main()
{
    freopen("zapezi.in","r",stdin);
    freopen("zapezi.out","w",stdout);

    scanf("%d%d", &n, &d);
    for (i = 1; i < n; i++) {
        scanf("%d%d%d", &x, &y, &d);
        list[x].pb(mp(y, d));
        list[y].pb(mp(x, d));
        ans += 2 * d;
    }

    memset(us, 0, sizeof(us));
    dfs(1, 0);

    memset(us, 0, sizeof(us));
    dfs(best.second, 0);

    printf("%d", ans - best.first);


    return 0;
}
