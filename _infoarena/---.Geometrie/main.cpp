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

#define maxN 100011

struct Point {
    ll x, y;

    bool operator<(const Point& who) const {
        return mp(x, y) < mp(who.x, who.y);
    }
};

struct query {
    ll x, y;
    int id;

    bool operator<(const query& who) const {
        return mp(x, y) < mp(who.x, who.y);
    }
};

int n, i, q, pos;
Point P[maxN];
query Q[maxN];

vector< pair<Point, ll> > up, down;
Point zero;
ll ans[maxN];


ll cross(Point A, Point B, Point C) {
    B.x -= A.x;
    B.y -= A.y;

    C.x -= A.x;
    C.y -= A.y;

    return B.x * C.y - B.y * C.x;
}

void add(Point P) {
    while (up.size() >= 2) {
        int sz = up.size();
        if (cross(up[sz - 2].first, up[sz - 1].first, P) < 0) break;
        up.pop_back();
    }

    if (up.empty())
        up.pb(mp(P, 0));
    else
        up.pb(mp(P, up.back().second + cross(zero, up.back().first, P)));

    while (down.size() >= 2) {
        int sz = down.size();
        if (cross(down[sz - 2].first, down[sz - 1].first, P) > 0) break;
        down.pop_back();
    }

    if (down.empty())
        down.pb(mp(P, 0));
    else
        down.pb(mp(P, down.back().second + cross(zero, P, down.back().first)));
}

ll solve(Point P) {
    if (up.size() < 2) return 0;

    int ansl = -1;
    for (int step = (1 << 18); step > 0; step >>= 1)
        if (ansl + step + 1 < up.size())
            if (cross(up[ansl + step].first, up[ansl + step + 1].first, P) < 0)
                ansl += step;

    int ansr = -1;
    for (int step = (1 << 18); step > 0; step >>= 1)
        if (ansr + step + 1 < down.size())
            if (cross(down[ansr + step].first, down[ansr + step + 1].first, P) > 0)
                ansr += step;

    ansl++; ansr++;
    ll sol = up[ansl].second + down[ansr].second;
    sol += cross(up[ansl].first, P, zero) + cross(P, down[ansr].first, zero);

    if (sol < 0) return -sol;
    return sol;
}

int main()
{
    freopen("geometrie.in","r",stdin);
    freopen("geometrie.out","w",stdout);

    scanf("%d%d", &n, &q);
    for (i = 1; i <= n; i++) scanf("%lld%lld", &P[i].x, &P[i].y);
    for (i = 1; i <= q; i++) scanf("%lld%lld", &Q[i].x, &Q[i].y), Q[i].id = i;

    sort(P + 1, P + n + 1);
    sort(Q + 1, Q + q + 1);

    zero = {0, 0};

    pos = 1;
    for (i = 1; i <= q; i++) {
        while (P[pos].x < Q[i].x && pos <= n) {
            add(P[pos]);
            pos++;
        }

        ans[Q[i].id] = solve((Point){Q[i].x, Q[i].y});
    }

    for (i = 1; i <= q; i++)
        printf("%lld.%lld\n", (ans[i] * 5) / 10, (ans[i] * 5) % 10);


    return 0;
}
