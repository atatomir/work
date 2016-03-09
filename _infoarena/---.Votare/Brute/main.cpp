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

int n, i, x, y, op;
vector< pair<ll, ll> > Points;

int find_points(pair<ll, ll> act) {
    for (int i = 0; i < Points.size(); i++)
        if (Points[i] == act)
            return i;

    return -1;
}

int main()
{
    freopen("votare.in","r",stdin);
    freopen("votare.ok","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d%d", &op, &x, &y);

        if (op == 0) {
            int id = find_points(mp(x, y));
            if (id == -1)
                Points.pb(mp(x, y));
        }

        if (op == 1) {
            int id = find_points(mp(x, y));
            if (id != -1)
                Points.erase(Points.begin() + id);
        }

        if (op == 2) {
            if (Points.size() == 0) {
                printf("-1\n");
            } else {
                ll dist = 1LL << 60;

                for (auto e : Points)
                    dist = min(dist, 1LL * (x - e.first) * (x - e.first) + 1LL * (y - e.second) * (y - e.second));

                printf("%lld\n", dist);
            }
        }
    }


    return 0;
}
