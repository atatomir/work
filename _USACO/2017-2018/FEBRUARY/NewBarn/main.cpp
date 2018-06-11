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
#define maxLog 21

struct query {
    int tp, node;
};

int n, q, i, j, x, act_id;
char s;
query Q[maxN];
vector<int> list[maxN];
int lvl[maxN];
int dad[maxLog][maxN];
int id[maxN], ids;

int n1[maxN], n2[maxN], act_dist[maxN];

int find_lca(int x, int y) {
    if (lvl[x] > lvl[y]) swap(x, y);

    for (int i = maxLog - 1; i >= 0; i--)
        if (lvl[dad[i][y]] >= lvl[x])
            y = dad[i][y];

    if (x == y) return x;
    for (int i = maxLog - 1; i >= 0; i--)
        if (dad[i][x] != dad[i][y])
            x = dad[i][x], y = dad[i][y];

    return dad[0][x];
}

int get_dist(int x, int y) {
    int lca = find_lca(x, y);
    return lvl[x] + lvl[y] - 2 * lvl[lca] + 1;
}

void dfs(int node) {
    id[node] = ids;

    for (auto to : list[node])
        if (id[to] == 0)
            dfs(to);
}

int main()
{
    freopen("newbarn.in","r",stdin);
    freopen("newbarn.out","w",stdout);

    scanf("%d\n", &q);
    for (i = 1; i <= q; i++) {
        scanf("%s%d\n", &s, &x);
        if (s == 'B') {
            n++;
            Q[i] = {1, n};

            lvl[n] = 1;
            if (x != -1) {
                list[x].pb(n);
                list[n].pb(x);
                dad[0][n] = x;
                lvl[n] = lvl[x] + 1;
            }
        } else {
            Q[i] = {2, x};
        }
    }

    for (i = 1; i < maxLog; i++)
        for (j = 1; j <= n; j++)
            dad[i][j] = dad[i - 1][dad[i - 1][j]];

    for (i = 1; i <= n; i++) {
        if (id[i] != 0) continue;
        ids++;
        dfs(i);

        n1[ids] = n2[ids] = i;
        act_dist[ids] = 1;
    }

    //cerr << get_dist(6, 8) << '\n';

    for (i = 1; i <= q; i++) {
        if (Q[i].tp == 1) {
            act_id = id[Q[i].node];

            int d1 = get_dist(n1[act_id], Q[i].node);
            int d2 = get_dist(n2[act_id], Q[i].node);

            if (d1 >= d2 && d1 > act_dist[act_id]) {
                n2[act_id] = Q[i].node;
                act_dist[act_id] = d1;
            }

            if (d2 >= d1 && d2 > act_dist[act_id]) {
                n1[act_id] = Q[i].node;
                act_dist[act_id] = d2;
            }
        } else {
            act_id = id[Q[i].node];

            int d1 = get_dist(n1[act_id], Q[i].node);
            int d2 = get_dist(n2[act_id], Q[i].node);

            printf("%lld\n", max(d1, d2) - 1);
        }
    }




    return 0;
}
