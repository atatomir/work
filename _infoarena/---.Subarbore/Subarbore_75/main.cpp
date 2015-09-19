#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define inf 500000000
#define maxN 44
#define maxT 9

int n, m, t, i, j, k, x, y, cost;
int roy[maxN][maxN];

bool us[maxN];
vector<int> must;
vector<int> use;
int ans = inf;

int dad[maxN];
vector< pair<int, int> > edge;
int time_test = 0;

int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

bool Merge(int R1, int R2) {
    R1 = Find(R1);
    R2 = Find(R2);

    if (R1 != R2) {
        dad[R2] = R1;
        return true;
    }

    return false;
}

bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
    return roy[a.first][a.second] < roy[b.first][b.second];
}

void solve_tree() {
    for (auto e : must) dad[e] = e;

    edge.clear();
    for (int i = 0; i < must.size(); i++)
        for (int j = i + 1; j < must.size(); j++)
            edge.pb(mp(must[i], must[j]));

    sort(edge.begin(), edge.end(), cmp);

    int act = 0;
    for (auto e : edge) {
        if (Merge(e.first, e.second)) {
            act += roy[e.first][e.second];
            if (act >= ans) return;
        }
    }

    ans = min(ans, act);
}

void backTracking(int pas, int how) {
    if (pas == use.size()) {
        solve_tree();
        time_test++;
        return;
    }

    if (how > 0) {
        must.push_back(use[pas]);
        backTracking(pas + 1, how - 1);
        must.pop_back();
    }
    backTracking(pas + 1, how);
}

int main()
{
    freopen("subarbore.in","r",stdin);
    freopen("subarbore.out","w",stdout);

    scanf("%d%d", &n, &m, &k);

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            roy[i][j] = (i == j ? 0 : inf);

    for (i = 1; i <= m; i++) {
        scanf("%d%d%d",&x,&y,&cost);
        roy[x][y] = roy[y][x] = cost;
    }

    for (k = 1; k <= n; k++)
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                roy[i][j] = min(roy[i][j], roy[i][k] + roy[k][j]);

    scanf("%d", &t);
    for (i = 1; i <= t; i++) {
        scanf("%d", &x);
        must.pb(x);
        us[x] = true;
    }
    for (i = 1; i <= n; i++)
        if (!us[i]) use.pb(i);


    backTracking(0, t - 1);
    printf("%d", ans);

    cerr << time_test;

    return 0;
}
