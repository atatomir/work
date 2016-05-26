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

#define maxN 3011

int n, k, i, x, y;
int id[maxN];
vector<int> list[maxN];

bool us[maxN];
int daddy[maxN];

bool on_path[maxN];

int l[maxN], r[maxN];
vector<int> adj[maxN];
vector<int> nodes_on_path;

int ans;





void dfs(int node) {
    us[node] = true;

    for (int to : list[node])
        if (!us[to])
            daddy[to] = node, dfs(to);
}

bool pairUp(int node) {
    if (us[node]) return false;
    us[node] = true;

    for (int to : adj[node])
        if (r[to] == 0)
            { l[node] = to; r[to] = node; return true; }

    for (int to : adj[node])
        if (pairUp(r[to]))
            { l[node] = to; r[to] = node; return true; }

    return false;
}



int main()
{
    freopen("posta3.in","r",stdin);
    freopen("posta3.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }
    for (i = 1; i <= n; i++) scanf("%d", &id[i]);

    dfs(1);
    for (int node = k; node != 1; node = daddy[node]) on_path[node] = true, nodes_on_path.pb(node);
    on_path[1] = true;
    nodes_on_path.pb(1);

    for (int node = k; node != 1; node = daddy[node]) {
        for (int dad = daddy[node]; dad != 0; dad = daddy[dad]) {
            for (int to : list[dad]) {
                if (on_path[to]) continue;
                if (id[to] < id[node]) continue;

                adj[node].pb(to);
            }
        }
    }

    bool need = true;
    while (need) {
        need = false;
        memset(us, 0, sizeof(us));

        for (int i : nodes_on_path)
            if (l[i] == 0)
                need |= pairUp(i);
    }


    for (i = 1; i <= n; i++)
        ans += (l[i] != 0 ? 1 : 0);

    printf("%d", ans);

    return 0;
}
