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
#define maxK 28
#define inf 1000000000

int n, k, i, x, y, d;
bool us[maxN];
int dp_full[maxN][maxK];
int dp_just[maxN][maxK];

vector< pair<int, int> > list[maxN];
int from_top[maxN];

int aux[maxN][maxK];
int aux_2[maxN][maxK];
int aux_3[maxK], aux_4[maxK];

void dfs(int node) {
    us[node] = true;
    for (int i = 0; i < list[node].size(); i++) {
        if (us[ list[node][i].first ]) {
            list[node][i] = list[node][ list[node].size() - 1 ];
            list[node].pop_back();
            i--;
            continue;
        }

        from_top[ list[node][i].first ] = from_top[node] + list[node][i].second;
        dfs(list[node][i].first);
    }
}

void merge_them(int *dest, int *s1, int *s2) {
    static int i, j;

    for (i = 0; i <= k; i++) dest[i] = inf;
    for (i = 0; i <= k; i++) {
        int limit = k - i;
        for (j = 0; j <= limit; j++) {
            dest[i + j] = min(dest[i + j], s1[i] + s2[j]);
        }
    }
}

void test_best(int id) {
    for (int i = 0; i <= k; i++)
        dp_just[id][i] = min(dp_just[id][i], aux_4[i]);
}

void compute(int node) {
    int i;

    if (list[node].empty()) return;

    for (auto e : list[node]) {
        compute(e.first);

        for (i = 0; i <= k; i++) dp_just[e.first][i] += e.second;

        dp_full[e.first][0] = dp_full[e.first][0] + 2 * e.second;
        for (i = 1; i <= k; i++)
            dp_full[e.first][i] = min(dp_full[e.first][i] + 2 * e.second,
                                      dp_just[e.first][i - 1] + from_top[node]);
    }

    int how = list[node].size();
    memset(aux[0], 0, sizeof(aux[0]));
    memset(aux[how + 1], 0, sizeof(aux[0]));
    memset(aux_2[0], 0, sizeof(aux[0]));
    memset(aux_2[how + 1], 0, sizeof(aux[0]));

    for (i = 0; i < how; i++)
        merge_them(aux[i + 1], aux[i], dp_full[ list[node][i].first ]);
    for (i = how - 1; i >= 0; i--)
        merge_them(aux_2[i + 1], aux_2[i + 2], dp_full[ list[node][i].first ]);

    memcpy(dp_full[node], aux[how], sizeof(aux[how]));

    for (i = 0; i <= k; i++) dp_just[node][i] = dp_full[node][i];
    for (i = 0; i < list[node].size(); i++) {
        merge_them(aux_3, aux[i], aux_2[i + 2]);
        merge_them(aux_4, aux_3, dp_just[ list[node][i].first ]);

        test_best(node);
    }
}

int main()
{
    freopen("camion2.in","r",stdin);
    freopen("camion2.out","w",stdout);

    scanf("%d%d", &n, &k); k--;
    for (i = 1; i < n; i++) {
        scanf("%d%d%d", &x, &y, &d);
        list[x].pb(mp(y, d));
        list[y].pb(mp(x, d));
    }

    dfs(1);
    compute(1);
    printf("%d", dp_just[1][k]);

    return 0;
}
