#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 55

int t, n, m, i, x, y;
vector<int> list[maxN];
bool us[maxN], isGood;
int dad[maxN];

int dp[maxN];
multiset<int> sons[maxN];

void dfs_tree(int node) {
    if (!isGood) return;

    us[node] = true;
    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i];

        if (dad[node] == to) {
            list[node][i] = list[node][ list[node].size() - 1 ];
            list[node].pop_back();
            i--;
            continue;
        }

        if (us[to]) {
            isGood = false;
            return;
        }

        dad[to] = node;
        dfs_tree(to);
    }
}

void dfs_set(int node) {
    dp[node] = 1;
    sons[node].clear();
    us[node] = true;

    for (auto to : list[node]) {
        dfs_set(to);

        dp[node] = max(dp[node], dp[to] + 1);
        sons[node].insert(dp[to]);
    }
}

void moveRoot(int R1, int R2) {
    sons[R1].erase(dp[R2]);

    if (sons[R1].size() > 0) {
        auto it = sons[R1].end(); it--;
        dp[R1] = *it + 1;
    } else {
        dp[R1] = 1;
    }

    sons[R2].insert(dp[R1]);

    auto it = sons[R2].end(); it--;
    dp[R2] = *it + 1;
}

void dfs_smen(int node) {
    if (!isGood) return;

    if (sons[node].size() >= 3) {
        auto it = sons[node].end();
        it--; it--; it--;

        if (*it >= 3) {
            isGood = false;
            return;
        }
    }

    for (auto to : list[node]) {
        moveRoot(node, to);
        dfs_smen(to);
        moveRoot(to, node);
    }
}

bool goodTree() {
    if (m > n - 1) return false;
    memset(us, 0, sizeof(us));

    for (i = 1; i <= n; i++) {
        if (us[i]) continue;

        dad[i] = 0;
        isGood = true;
        dfs_tree(i);

        if (!isGood) return false;
    }

    memset(us, 0, sizeof(us));
    isGood = true;
    for (i = 1; i <= n; i++) {
        if (us[i]) continue;

        dfs_set(i);
        dfs_smen(i);

        if (!isGood) return false;
    }

    return true;
}

int main()
{
    freopen("lesbulan.in","r",stdin);
    freopen("lesbulan.out","w",stdout);

    for (scanf("%d", &t); t > 0; t--) {
        scanf("%d%d", &n, &m);

        for (i = 1; i <= n; i++) list[i].clear();
        for (i = 1; i <= m; i++) {
            scanf("%d%d", &x, &y);
            list[x].pb(y);
            list[y].pb(x);
        }

        if (goodTree())
            printf("1\n");
        else
            printf("0\n");
    }

    return 0;
}
