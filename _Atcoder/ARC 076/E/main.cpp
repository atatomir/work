#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011

ll R, C, n, i;
ll x, y, xx, yy;
vector< pair<ll, ll> > ord;
set<ll> S;

bool on_edge(ll x, ll y) {
    if (x == 0 || y == 0) return true;
    if (x == R || y == C) return true;
    return false;
}

ll get_pos(ll x, ll y) {
    if (y == 0) return x;
    if (x == R) return R + y;
    if (y == C) return R + C + (R - x);
    if (x == 0) return R + C + R + (C - y);
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> R >> C >> n;
    for (i = 1; i <= n; i++) {
        cin >> x >> y >> xx >> yy;
        if (!on_edge(x, y)) continue;
        if (!on_edge(xx, yy)) continue;

        ll p1 = get_pos(x, y);
        ll p2 = get_pos(xx, yy);
        if (p2 < p1) swap(p1, p2);
        if (p2 - p1 > 2LL * (R + C) - (p2 - p1)) {
            swap(p1, p2);
            p2 += 2LL * (R + C);
        }

        ord.pb(mp(p1, p2));
        ord.pb(mp(p1 + 2LL * (R + C), p2 + 2LL * (R + C)));
        ord.pb(mp(p1 + 4LL * (R + C), p2 + 4LL * (R + C)));
    }


    sort(ord.begin(), ord.end());
    for (auto e : ord) {
        auto it = S.lower_bound(e.first + 1);
        if (it != S.end()) {
            if (*it < e.second) {
                printf("NO");
                return 0;
            }
        }
        S.insert(e.second);
    }

    printf("YES");



    return 0;
}
