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

#define maxN 1577
#define mod 104659
#define eps 0.000000001
#define inf 1e60

int n, m, i, x, y, c;
vector< pair<int, double> > list[maxN];

double dist[maxN];
int cnt[maxN];
priority_queue< pair<double, int> > H;

bool equal(double a, double b) {
    return -eps <= a - b && a - b <= eps;
}

int main()
{
    freopen("dmin.in","r",stdin);
    freopen("dmin.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &c);
        list[x].pb(mp(y, log(1.00 * c)));
    }

    for (i = 1; i <= n; i++) dist[i] = inf;
    dist[1] = 0.00;
    cnt[1] = 1;
    H.push(mp(-0.00, 1));

    while (!H.empty()) {
        auto topp = H.top(); H.pop();
        if (!equal(-topp.first, dist[topp.second])) continue;

        int node = topp.second;
        for (auto to : list[node]) {
            double new_dist = dist[node] + to.second;

            if (new_dist < dist[to.first] - eps) {
                dist[to.first] = new_dist;
                cnt[to.first] = 0;
                H.push(mp(-dist[to.first], to.first));
            }

            if (equal(new_dist, dist[to.first])) {
                cnt[to.first] += cnt[node];
                if (cnt[to.first] >= mod) cnt[to.first] -= mod;
            }
        }
    }

    for (i = 2; i <= n; i++) printf("%d ", cnt[i]);



    return 0;
}
