#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1024

int n, i, m, x, y, ammo;
vector<int> list[maxN];
vector<int> c_list[maxN];

bool alive[maxN];
bool us[maxN];
bool onCycle;
int from;

void dfs_cycle(int node) {
    if (onCycle) return;

    us[node] = true;
    for (int i = 0; i < c_list[node].size(); i++) {
        int to = c_list[node][i];

        if (from == to) {
            onCycle = true;
            return;
        }
        if (us[to]) continue;

        dfs_cycle(to);
    }
}

bool onZeroCycle(int node) {
    if (!alive[node]) return false;

    memset(us, 0, sizeof(us));
    onCycle = false;
    from = node;

    dfs_cycle(node);
    return onCycle;
}

bool dfs(int node) {
    alive[node] = false;

    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i];

        if (!alive[to]) continue;

        dfs(to);
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d %d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &ammo);
        list[x].pb(y);

        if (ammo == 0)
            c_list[x].pb(y);
    }

    for (i = 1; i <= n; i++) alive[i] = true;
    for (i = 1; i <= n; i++) {
        if (onZeroCycle(i))
            dfs(i);
    }

    for (i = 1; i <= n; i++)
        printf("%d\n", (alive[i] ? 1 : 0) );

    return 0;
}
