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

#define maxN 200011

int n, d, i, x;
vector<int> list[maxN];
vector< pair<int, int> > ord;

int ans;
int marked[maxN];


void dfs(int node, int root, int lvl) {
    ord.pb(mp(lvl, node));

    for (auto to : list[node]) {
        if (to == root) continue;
        dfs(to, node, lvl + 1);
    }
}

void mark(int node, int root, int d) {
    if (d == 0) return;
    if (marked[node] >= d) return;
    marked[node] = d;

    for (auto to : list[node]) {
        if (to == root) continue;
        mark(to, node, d - 1);
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &d);
    for (i = 2; i <= n; i++) {
        scanf("%d", &x);
        list[x + 1].pb(i);
        list[i].pb(x + 1);
    }

    dfs(1, 0, 0);
    sort(ord.begin(), ord.end());
    reverse(ord.begin(), ord.end());

    for (auto e : ord) {
        if (marked[e.second]) continue;
        ans++;
        mark(e.second, 0, d);
    }

    printf("%d", ans);


    return 0;
}
