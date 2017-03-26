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

#define maxN 1024

int t, ti;
int n, i, D, C, V, x, y, P;
vector<int> list[maxN];
vector<int> way;

bool good[maxN];
bool on_way[maxN];
int distC[maxN], distD[maxN], distV[maxN];

void dfs(int node, int root) {
    way.pb(node);
    if (way.back() == D) return;

    for (auto to : list[node]) {
        if (to == root)
            continue;

        dfs(to, node);
        if (way.back() == D) return;
    }

    way.pop_back();
}

void dfs2(int node, int root) {
    if (on_way[node] && P == 0)
        P = node;

    for (auto to : list[node]) {
        if (to == root)
            continue;

        distV[to] = distV[node] + 1;
        dfs2(to, node);
    }
}

bool solve() {
    int i;

    way.clear();
    dfs(C, 0);

    memset(good, 0, sizeof(good));
    memset(on_way, 0, sizeof(on_way));
    memset(distC, 0, sizeof(distC));
    memset(distD, 0, sizeof(distD));
    memset(distV, 0, sizeof(distV));

    for (i = 1; i + 1 < way.size(); i++)
        if (list[way[i]].size() > 2)
            good[way[i]] = true;

    for (auto e : way)
        on_way[e] = true;

    for (i = 0; i < way.size(); i++) {
        distC[way[i]] = i;
        distD[way[i]] = way.size() - 1 - i;
    }

    P = 0;
    dfs2(V, 0);

    if (P == C)
        return true;

    if (P == D)
        return false;

    for (auto e : way)
        distV[e]++;
    distV[P] = 0;

    if (V == P)
        distV[P] = 1;

    for (auto e : way) {
        if (good[e] && distV[e] <= distC[e] && distC[e] <= distD[e])
            return true;
    }

    return false;
}

int main()
{
    freopen("fantasy.in","r",stdin);
    freopen("fantasy.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%d%d%d", &n, &D, &C, &V);
        for (i = 1; i < n; i++) {
            scanf("%d%d", &x, &y);
            list[x].pb(y);
            list[y].pb(x);
        }

        if (solve())
            printf("DA\n");
        else
            printf("NU\n");

        for (i = 1; i <= n; i++)
            list[i].clear();
    }


    return 0;
}
