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

#define maxN 200011

int n, m, i, x, y, node, to;
vector<int> list[maxN];
int deg[maxN];
queue<int> Q;
int ans[maxN];

void clean(vector<int>& data) {
    int i;

    for (i = 0; i < data.size(); i++) {
        if (deg[data[i]] < 0) {
            data[i] = data.back();
            data.pop_back();
            i--;
            continue;
        }
    }
}

void add_sol(int x, int y) {
    if (x > y) swap(x, y);
    ans[x] = y - n;
}

int main()
{
    freopen("bal.in","r",stdin);
    freopen("bal.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y); y += n;
        deg[x]++; deg[y]++;
        list[x].pb(y);
        list[y].pb(x);
    }

    n <<= 1;
    for (i = 1; i <= n; i++) {
        if (deg[i] == 1)
        Q.push(i);
    }

    n >>= 1;
    while (!Q.empty()) {
        node = Q.front(); Q.pop();
        if (deg[node] < 1) continue;

        clean(list[node]);
        to = list[node][0];

        add_sol(node, to);

        deg[node] = deg[to] = -1;
        for (auto e : list[to]) {
            if (--deg[e] == 1)
                Q.push(e);
        }
    }

    for (i = 1; i <= n; i++)
        if (deg[i] >= 0)
            {printf("NU"); return 0;}

    printf("DA\n");
    for (i = 1; i <= n; i++) printf("%d\n", ans[i]);

    return 0;
}
