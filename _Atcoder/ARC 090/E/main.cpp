#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstdlib>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011
#define mod 1000000007

const ll inf = (1LL << 60);

int n, m, i, S, T, u, v, d;
vector< pair<int, ll> > list[maxN];
pair<ll, ll> dist[2][maxN];
priority_queue< pair<ll, int>, vector< pair<ll, int> >, greater< pair<ll, int> > > H;

ll ans;

ll p2(ll x) {
    x %= mod;
    x *= x;
    x %= mod;
    return x;
}

void dijk(pair<ll, ll>* data, int S) {
    int i, j;

    for (i = 1; i <= n; i++) data[i] = mp(inf, 0);
    while (!H.empty()) H.pop();
    data[S] = mp(0, 1);
    H.push(mp(data[S].first, S));

    while (!H.empty()) {
        int node = H.top().second;
        ll dd = H.top().first;
        H.pop();

        if (data[node].first != dd) continue;

        for (auto to : list[node]) {
            if (data[to.first].first > data[node].first + to.second) {
                data[to.first].first = data[node].first + to.second;
                data[to.first].second = 0;
                H.push(mp(data[to.first].first, to.first));
            }

            if (data[to.first].first == data[node].first + to.second) {
                data[to.first].second += data[node].second;
                if (data[to.first].second >= mod) data[to.first].second -= mod;
            }
        }
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%d%d", &n, &m, &S, &T);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &d);
        list[u].pb(mp(v, d));
        list[v].pb(mp(u, d));
    }

    dijk(dist[0], S);
    dijk(dist[1], T);

    ans = p2(dist[0][T].second);
    for (i = 1; i <= n; i++) {
        if (dist[0][i].first + dist[1][i].first == dist[0][T].first) {
            if (dist[0][i].first == dist[1][i].first) {
                ans += mod - p2(1LL * dist[0][i].second * dist[1][i].second);
                if (ans >= mod) ans -= mod;
            }
        }

        for (auto to : list[i]) {
            if (dist[0][i].first + to.second + dist[1][to.first].first == dist[0][T].first) {
                if (2LL * dist[0][i].first < dist[0][T].first &&
                    2LL * (dist[0][i].first + to.second) > dist[0][T].first) {

                    ans += mod - p2(1LL * dist[0][i].second * dist[1][to.first].second);
                    if (ans >= mod) ans -= mod;
                }
            }
        }
    }

    printf("%lld", ans);

    return 0;
}
