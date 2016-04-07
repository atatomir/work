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

#define maxN 5110

struct Edge {
    pair<int, int> bg;
    pair<int, int> en;
    ll diff;

    Edge() {}

    Edge(pair<int, int> _bg, pair<int, int> _en, ll _diff) {
        bg = _bg;
        en = _en;
        diff = _diff;
    }

    bool operator<(const Edge& b) const{
        return diff < b.diff;
    }
};

int n, m, A, B, i, j, v;
vector<int> vx, vy;
ll ans;
vector<Edge> E;

pair<int, int> dad[maxN][maxN];

pair<int, int> Find(pair<int, int> p) {
    if (dad[p.first][p.second] == p) return p;
    dad[p.first][p.second] = Find(dad[p.first][p.second]);
    return dad[p.first][p.second];
}

bool _Merge(pair<int, int> p1, pair<int, int> p2) {
    p1 = Find(p1);
    p2 = Find(p2);

    if (p1 != p2) dad[p1.first][p1.second] = p2;
    return p1 != p2;
}

int main()
{
    freopen("fencedin.in","r",stdin);
    freopen("fencedin.out","w",stdout);

    scanf("%d%d%d%d", &A, &B, &n, &m);

    vx.pb(0);
    vx.pb(A);

    vy.pb(0);
    vy.pb(B);

    for (i = 1; i <= n; i++) {
        scanf("%d", &v);
        vx.pb(v);
    }
    sort(vx.begin(), vx.end());

    for (i = 1; i <= m; i++) {
        scanf("%d", &v);
        vy.pb(v);
    }
    sort(vy.begin(), vy.end());

    for (i = 1; i < vx.size(); i++) {
        for (j = 1; j < vy.size(); j++) {
            if (i != vx.size() - 1) E.pb( Edge(mp(i, j), mp(i + 1, j), vy[j] - vy[j - 1]) );
            if (j != vy.size() - 1) E.pb( Edge(mp(i, j), mp(i, j + 1), vx[i] - vx[i - 1]) );
            dad[i][j] = mp(i, j);
        }
    }

    sort(E.begin(), E.end());
    for (auto e : E) {
        if (_Merge(e.bg, e.en)) {
            ans += 1LL * e.diff;
        }
    }

    printf("%lld", ans);


    return 0;
}
