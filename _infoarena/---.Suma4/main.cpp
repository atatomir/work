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

#define maxN 65555
#define maxDim 333
#define inf 1000000000

int n, i, j, cnt, l, x, y;
int cost[maxN];
int lvl[maxN];

int sums[maxN];
int dp[maxN];

pair<int, int> get_pos(int id) {
    int aux = id;
    aux -= sums[ lvl[id] - 1 ];
    if (aux % lvl[id] == 0)
        return mp(aux / lvl[id], lvl[id]);
    else
        return mp(1 + (aux / lvl[id]), aux % lvl[id]);
}

int get_id(int l, int x, int y) {
    return sums[l - 1] + (x - 1) * l + y;
}

int main()
{
    freopen("suma4.in","r",stdin);
    freopen("suma4.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &cost[i]);

    for (i = cnt = 1; i <= n; i += cnt * cnt, cnt++) {
        for (j = 0; j < cnt * cnt; j++)
            lvl[i + j] = cnt;

        sums[cnt] = sums[cnt - 1] + cnt * cnt;
    }

    for (i = n; i > 0; i--) {
        if (lvl[i] == lvl[n]) {
            dp[i] = cost[i];
            continue;
        }

        l = lvl[i];
        auto pos = get_pos(i);
        x = pos.first;
        y = pos.second;

        dp[i] = inf;
        dp[i] = min(dp[i], dp[get_id(l + 1, x, y)]);
        dp[i] = min(dp[i], dp[get_id(l + 1, x + 1, y)]);
        dp[i] = min(dp[i], dp[get_id(l + 1, x, y + 1)]);
        dp[i] = min(dp[i], dp[get_id(l + 1, x + 1, y + 1)]);

        dp[i] += cost[i];
    }

    int act;

    printf("%d %d\n", lvl[n], dp[1]);
    for (act = 1; lvl[act] < lvl[n]; ) {
        printf("%d ", act);

        l = lvl[act];
        auto pos = get_pos(act);
        x = pos.first;
        y = pos.second;

        int aux = get_id(l + 1, x, y);
        if (dp[act] == cost[act] + dp[aux]) {
            act = aux;
            continue;
        }

        aux = get_id(l + 1, x, y + 1);
        if (dp[act] == cost[act] + dp[aux]) {
            act = aux;
            continue;
        }

        aux = get_id(l + 1, x + 1, y);
        if (dp[act] == cost[act] + dp[aux]) {
            act = aux;
            continue;
        }

        aux = get_id(l + 1, x + 1, y + 1);
        if (dp[act] == cost[act] + dp[aux]) {
            act = aux;
            continue;
        }

    }

    printf("%d\n", act);




    return 0;
}
