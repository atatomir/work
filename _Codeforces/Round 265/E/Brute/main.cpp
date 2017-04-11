#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <functional>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011
#define mod 1000000007

int n, m, i, s, t, x, y, z;
vector< pair<int, int> > list[maxN];
ll dist[maxN];
int prov[maxN];

priority_queue< pair<ll, int>, vector< pair<ll, int> >, greater< pair<ll, int> > > H;
vector<int> ans;


int main()
{
    freopen("test.in","r",stdin);
    freopen("test.ok","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        list[x].pb(mp(y, z));
        list[y].pb(mp(x, z));
    }
    scanf("%d%d", &s, &t);

    for (i = 1; i <= n; i++) dist[i] = 1LL << 60;
    dist[s] = 0;
    H.push(mp(dist[s], s));

    while (!H.empty()) {
        int node = H.top().second;
        ll dd = H.top().first;
        H.pop();

        if (node == t) break;
        if (dist[node] != dd) continue;

        for (auto to : list[node]) {
            if (dist[to.first] > dist[node] + (1LL << to.second)) {
                dist[to.first] = dist[node] + (1LL << to.second);
                prov[to.first] = node;
                H.push(mp(dist[to.first], to.first));
            }
        }
    }

    if (prov[t] == 0) {
        printf("-1");
        return 0;
    }

    for (int node = t; node != s; node = prov[node]) ans.pb(node);
    ans.pb(s);
    reverse(ans.begin(), ans.end());

    printf("%lld\n", dist[t] % mod);
    printf("%d\n", ans.size());
    for (auto e : ans) printf("%d ", e);


    return 0;
}
