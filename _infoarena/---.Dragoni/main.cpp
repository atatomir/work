#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <functional>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 888

const int inf = 1000000007;

int op, n, m, i, x, y, z;
int drag[maxN];
vector< pair<int, int> > list[maxN];
vector< pair<int, int> > ord;

priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > H;
int dist[maxN], global_dist[maxN];
int limit;

int main()
{
    freopen("dragoni.in","r",stdin);
    freopen("dragoni.out","w",stdout);

    scanf("%d%d%d", &op, &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d", &drag[i]);
        ord.pb(mp(drag[i], i));
    }

    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        list[x].pb(mp(y, z));
        list[y].pb(mp(x, z));
    }

    sort(ord.begin(), ord.end());

    for (i = 1; i <= n; i++) global_dist[i] = inf;
    global_dist[1] = 0;

    for (auto e : ord) {
        int node = e.second;
        limit = e.first;

        if (global_dist[node] >= inf) continue;

        for (i = 1; i <= n; i++) dist[i] = inf;
        dist[node] = global_dist[node];
        H.push(mp(dist[node], node));

        while (!H.empty()) {
            int act = H.top().second;
            int vv = H.top().first;
            H.pop();

            if (dist[act] != vv) continue;
            for (auto to : list[act]) {
                if (dist[act] + to.second >= dist[to.first]) continue;
                if (to.second > limit) continue;

                dist[to.first] = dist[act] + to.second;
                H.push(mp(dist[to.first], to.first));
            }
        }

        for (i = 1; i <= n; i++) global_dist[i] = min(global_dist[i], dist[i]);


        if (op == 1) break;
    }

    if (op == 1) {
        int ans = -1;
        for (i = 1; i <= n; i++)
            if (global_dist[i] < inf)
                ans = max(ans, drag[i]);

        printf("%d", ans);

        return 0;
    }

    printf("%d", global_dist[n]);


    return 0;
}
