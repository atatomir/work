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

#define maxN 5011
#define inf 1111111111

int n, i, x, k;
vector<int> nodes;
vector< pair<int, int> > list[maxN];
bool alrdn[maxN];

int cost[maxN];
priority_queue< pair<int, int> > H;

int ans = 0;

int main()
{
    freopen("banuti.in","r",stdin);
    freopen("banuti.out","w",stdout);

    scanf("%d", &n); nodes.resize(n);
    for (i = 1; i <= n; i++) scanf("%d", &nodes[i - 1]);

    nth_element(nodes.begin(), nodes.begin(), nodes.end());
    k = nodes[0];

    for (int e : nodes) {
        if (alrdn[e % k]) continue;
        alrdn[e % k] = true;

        for (i = 0; i < k; i++) {
            int to = (i + e) % k;
            list[i].pb(mp(to, e));
        }
    }

    for (i = 1; i < k; i++) cost[i] = inf;
    H.push(mp(0, 0));

    while (!H.empty()) {
        auto e = H.top(); H.pop();

        if (cost[e.first] != -e.second) continue;
        for (auto to : list[e.first]) {
            int new_cost = cost[e.first] + to.second;
            if (cost[to.first] > new_cost) {
                cost[to.first] = new_cost;
                H.push(mp(to.first, -cost[to.first]));
            }
        }
    }

    for (i = 0; i < k; i++) ans = max(ans, cost[i]);
    if (ans == inf) ans = k - 1; else ans = max(ans, 1);
    printf("%d", ans - k);

    return 0;
}
