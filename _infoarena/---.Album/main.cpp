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
#define maxM 55

#define _equal 0
#define _smaller 1
#define _greater 2

int n, m, i, j;
int h[maxN][maxM];

int l[maxN];
int r[maxN];
vector<int> list[maxN];
bool us[maxN];

bool comp(int id1, int id2) {
    for (int i = 1; i <= m; i++)
        if (h[id1][i] >= h[id2][i])
            return false;
    return true;
}

bool pairUp(int node) {
    if (us[node])
        return false;
    us[node] = true;

    for (auto to : list[node]) {
        if (!r[to]) {
            l[node] = to;
            r[to] = node;
            return true;
        }
    }

    for (auto to : list[node]) {
        if (pairUp(r[to])) {
            l[node] = to;
            r[to] = node;
            return true;
        }
    }

    return false;
}

int main()
{
    freopen("album.in","r",stdin);
    freopen("album.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++)
            scanf("%d", &h[i][j]);
        sort(h[i] + 1, h[i] + m + 1);
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (i == j) continue;

            if (comp(i, j))
                list[i].pb(j);
        }
    }

    bool need = true;
    while (need) {
        need = false;
        memset(us, 0, sizeof(us));

        for (i = 1; i <= n; i++)
            if (!l[i])
                need |= pairUp(i);
    }

    int ans = n;
    for (i = 1; i <= n; i++)
        if (l[i] != 0)
            ans--;

    printf("%d", ans);

    return 0;
}
