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

#define maxN 200011

struct Ball {
    ll x, y;
};

int n, i, p1, p2;
Ball B[maxN];
ll maxi, mini, ans;

vector< pair<ll, int> > ord;
vector<ll> pos;

ll same(vector<int> alrdn) {
    int i, pp;
    ll limit;
    ll act, ans;

    ord.clear();
    act = 0;
    limit = 1LL << 30;

    for (i = 1; i <= n; i++) {
        if (i == p1 || i == p2) continue;

        limit = min(limit, B[i].y);

        ord.pb(mp(B[i].x, i));
        act = max(act, B[i].x);

        pos.pb(B[i].x);
        pos.pb(B[i].y);
    }

    sort(ord.begin(), ord.end());
    sort(pos.begin(), pos.end());
    pos.resize(unique(pos.begin(), pos.end()) - pos.begin());

    pp = 0; ans = 1LL << 30;
    for (auto e : pos) {
        if (e > limit) continue;

        while (pp < ord.size()) {
            if (ord[pp].first >= e) break;
            act = max(act, B[ord[pp].second].y);
            pp++;
        }

        ll aux_max = act;
        for (auto e : alrdn) aux_max = max(aux_max, 1LL * e);
        ll aux_min = e;
        for (auto e : alrdn) aux_min = min(aux_min, 1LL * e);

        ans = min(ans, (aux_max - aux_min));
    }

    return ans;
}

ll diff() {
    ll min1, min2;
    ll max1, max2;
    int i;

    min1 = mini; max1 = B[p2].x;
    max2 = maxi; min2 = B[p1].y;

    for (i = 1; i <= n; i++) {
        if (i == p1 || i == p2) continue;

        max1 = max(max1, B[i].x);
        min2 = min(min2, B[i].y);
    }

    return (max1 - min1) * (max2 - min2);
}

int main()
{
    freopen("test.in","r",stdin);

    maxi = 0;
    mini = 1LL << 50;

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lld%lld", &B[i].x, &B[i].y);
        if (B[i].x > B[i].y) swap(B[i].x, B[i].y);

        mini = min(mini, B[i].x);
        maxi = max(maxi, B[i].y);
    }

    for (p1 = 1; B[p1].x != mini; p1++);
    for (p2 = 1; B[p2].y != maxi; p2++);

    if (p1 == p2) {
        ans = (maxi - mini) * same({});
    } else {
        ans = (maxi - mini) * same({B[p1].y, B[p2].x});
        ans = min(ans, diff());
    }

    printf("%lld", ans);

    return 0;
}
