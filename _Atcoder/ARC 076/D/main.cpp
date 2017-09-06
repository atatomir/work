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

struct pct {
    ll x, y, id;
};

int n, i;
pct P[maxN];
vector< pair<ll, pair<int, int> > > ord;
int dad[maxN];
ll ans;

int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

bool Merge(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x == y) return false;
    dad[x] = y;
    return true;
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++) cin >> P[i].x >> P[i].y, P[i].id = i;

    sort(P + 1, P + n + 1, [](const pct& a, const pct& b)->bool const {
        return a.x < b.x;
    });

    for (i = 2; i <= n; i++) ord.pb(mp(P[i].x - P[i - 1].x, mp(P[i - 1].id, P[i].id)));

    sort(P + 1, P + n + 1, [](const pct& a, const pct& b)->bool const {
        return a.y < b.y;
    });

    for (i = 2; i <= n; i++) ord.pb(mp(P[i].y - P[i - 1].y, mp(P[i - 1].id, P[i].id)));

    sort(ord.begin(), ord.end());
    for (i = 1; i <= n; i++) dad[i] = i;

    for (auto e : ord) {
        if (Merge(e.second.first, e.second.second))
            ans += e.first;
    }

    cout << ans;


    return 0;
}
