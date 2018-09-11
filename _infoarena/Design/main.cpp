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

const int maxN = 503;
const int maxK = 6;

int n, k, i, j, p, x;
vector<int> list[maxN];
int cnt[maxN][maxK];

int sol[maxN];
int mask, limit, total, conf;
bool ok;

int up[maxN][maxK]; //! ce culoare poate avea i daca mai sus obliga in j
int data[1 << maxK];
int help[maxN][1 << maxK];

void run_sos() {
    int i, j;

    for (i = 0; i < k; i++)
        for (j = 0; j < limit; j++)
            if ((j >> i) & 1)
                data[j] += data[j ^ (1 << i)];
}

int marriage(int node) {
    int ans = mask;
    int conf, i;
    int here;

    total = data[mask];

    for (conf = 1; conf < limit; conf++) {
        here = help[node][conf];

        if (here > total - data[mask ^ conf] + 1) return -1;
        if (here == total - data[mask ^ conf] + 1)
            ans &= conf;
    }

    return ans;
}

int strict(int node) {
    int ans = mask;
    int conf, i;
    int here;

    total = data[mask];

    for (conf = 1; conf < limit; conf++) {
        here = help[node][conf];
        if (here > total - data[mask ^ conf]) return -1;
    }

    return ans;
}

void dfs(int node, int root) {
    int col, i, j;
    bool any;

    for (auto to : list[node]) {
        if (to != root) {
            dfs(to, node);
            if (!ok) return;
        }
    }

    any = false;
    for (col = 0; col < k; col++) {
        if (sol[node] != -1 && sol[node] != col) continue;
        memset(data, 0, sizeof(data));

        for (auto to : list[node])
            if (to != root)
                data[ up[to][col] ]++;

        run_sos();
        int possib = (node == 1 ? strict(node) : marriage(node));

        if (possib == -1)
            continue;

        if (possib > 0) any = true;

        for (i = 0; i < k; i++)
            if ((possib >> i) & 1)
                up[node][i] |= 1 << col;
    }

    if (!any)
        ok = false;
}

bool check() {
    int i, j;

    for (i = 0; i <= n; i++)
        for (j = 0; j < k; j++)
            up[i][j] = 0;

    ok = true;
    dfs(1, 0);
    return ok;
}

int main()
{
    freopen("design.in","r",stdin);
    freopen("design.out","w",stdout);

    scanf("%d%d", &n, &k);
    limit = 1 << k;
    mask = limit - 1;

    for (i = 1; i <= n; i++) {
        sol[i] = -1;

        scanf("%d", &p);
        for (j = 1; j <= p; j++) {
            scanf("%d", &x);
            cnt[i][x - 1]++;
        }

        for (j = 1; j <= p; j++) {
            scanf("%d", &x);
            list[i].pb(x);
        }
    }

    for (i = 1; i <= n; i++) {
        for (conf = 1; conf < limit; conf++) {
            for (j = 0; j < k; j++)
                if ((conf >> j) & 1)
                    help[i][conf] += cnt[i][j];
        }
    }

    for (i = 1; i <= n; i++) {
        for (j = 0; true; j++) {
            sol[i] = j;
            if (check()) break;
        }
    }

    for (i = 1; i <= n; i++) printf("%d ", sol[i] + 1);


    return 0;
}
