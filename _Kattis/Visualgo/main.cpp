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

#define maxN 10011
#define inf (1 << 30) + 1

int n, m, i, x, y, c, s, d;
vector< pair<int, int> > list[maxN];

int dist[maxN];
int cnt[maxN];

priority_queue< pair< int, int > > H;

int solve() {
    int i;

    for (i = 1; i <= n; i++) dist[i] = inf, cnt[i] = 0;
    dist[s] = 0; cnt[s] = 1;
    H.push(mp(-0, s));

    while (!H.empty()) {
        auto act = H.top(); H.pop();
        int cost = -act.first;
        int node = act.second;

        if (dist[node] != cost) continue;

        for (auto to : list[node]) {
            int new_cost = dist[node] + to.second;

            if (new_cost > dist[to.first]) continue;
            if (new_cost == dist[to.first]) {
                cnt[to.first] += cnt[node];
            } else {
                cnt[to.first] = cnt[node];
                dist[to.first] = new_cost;
                H.push(mp(-new_cost, to.first));
            }
        }
    }

    return cnt[d];
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &c);
        x++; y++;
        list[x].pb(mp(y, c));
    }

    scanf("%d%d", &s, &d); s++; d++;
    printf("%d", solve());


    return 0;
}
