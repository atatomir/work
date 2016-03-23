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

#define maxN 555
#define pii pair<int, int>
#define piii pair<int, pii>
#define inf 1000000000

int n, m, i;
int x, y, w;
vector< pii > list[maxN];
vector< piii > edges;
vector< pii > not_used[maxN];

int dad[maxN];
int ans;
int ans2 = inf;

bool us[maxN];
int dist[maxN];


int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

bool Merge(int R1, int R2) {
    R1 = Find(R1);
    R2 = Find(R2);

    if (R1 == R2) return false;

    dad[R2] = R1;
    return true;
}

void dfs(int node) {
    us[node] = true;

    for (auto to : list[node]) {
        if (us[to.first]) continue;

        dist[to.first] = max(dist[node], to.second);
        dfs(to.first);
    }
}

void solve(int node) {
    int i;

    for (i = 1; i <= n; i++) {
        us[i] = false;
        dist[i] = 0;
    }

    dfs(node);

    for (auto to : not_used[node])
        ans2 = min(ans2, ans + to.second - dist[to.first]);
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &w);
        edges.pb(mp(w, mp(x, y)));
    }

    for (i = 1; i <= n; i++) dad[i] = i;

    sort(edges.begin(), edges.end());
    for (auto e : edges) {
        int n1 = e.second.first;
        int n2 = e.second.second;

        if (Merge(n1, n2)) {
            ans += e.first;
            list[n1].pb(mp(n2, e.first));
            list[n2].pb(mp(n1, e.first));
        } else {
            not_used[n1].pb(mp(n2, e.first));
            not_used[n2].pb(mp(n1, e.first));
        }
    }

    printf("Cost: %d\n", ans);

    if (n == m + 1) {
        printf("Cost: -1\n");
        return 0;
    }

    for (i = 1; i <= n; i++)
        solve(i);

    printf("Cost: %d\n", ans2);


    return 0;
}
