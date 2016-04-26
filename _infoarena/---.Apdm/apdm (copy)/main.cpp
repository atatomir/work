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

#define maxN 177

int n, m, i, x, y;
vector<int> list[maxN];
int ans = maxN;

bool us[maxN];
queue<int> Q;
vector<int> adj[maxN];

int dist[maxN];
vector< pair<int, int> > edg;

int get_deep(int node) {
    int i;
    int best;

    memset(dist, 0, sizeof(dist));
    dist[node] = 1;
    Q.push(node);

    while (!Q.empty()) {
        node = Q.front(); Q.pop();

        for (int to : adj[node])
            if (dist[to] == 0)
                dist[to] = dist[node] + 1, Q.push(to);
    }

    return dist[node] - 1;
}

void check(int node) {
    int i, R;

    R = node;
    memset(us, 0, sizeof(us));
    us[node] = true;
    Q.push(node);

    for (i = 1; i <= n; i++) adj[i].clear();

    while (!Q.empty()) {
        node = Q.front(); Q.pop();
        for (int to : list[node])
            if (!us[to])
                us[to] = true, Q.push(to), adj[node].pb(to), adj[to].pb(node);
    }

    ans = min(ans, get_deep(node));
}

void check2(int node, int node2) {
    int i, R;

    R = node;
    memset(us, 0, sizeof(us));
    us[node] = true; us[node2] = true;
    Q.push(node); Q.push(node2);


    for (i = 1; i <= n; i++) adj[i].clear();
    adj[node].pb(node2);
    adj[node2].pb(node);

    while (!Q.empty()) {
        node = Q.front(); Q.pop();
        for (int to : list[node])
            if (!us[to])
                us[to] = true, Q.push(to), adj[node].pb(to), adj[to].pb(node);
    }


    ans = min(ans, get_deep(node));
}

int main()
{
    freopen("apdm.in","r",stdin);
    freopen("apdm.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
        edg.pb(mp(x, y));
    }

    random_shuffle(edg.begin(), edg.end());
    edg.resize(edg.size() / 2);

    for (i = 1; i <= n; i++) check(i);
    for (auto e : edg) check2(e.first, e.second);
    printf("%d", ans);

    return 0;
}
