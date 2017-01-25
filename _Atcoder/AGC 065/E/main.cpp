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

struct point {
    ll x, y;
    int id;

    bool operator<(const point& who)const {
        return mp(x, y) < mp(who.x, who.y);
    }
};

int n, a, b, i;
ll x, y, D;
point P[maxN];

vector<int> list[maxN];
ll cnt[maxN];
int addit[maxN];

ll ans;
bool us[maxN];

ll abss(ll x) {
    if (x < 0)
        return -x;
    return x;
}

void add_edge(int x, int y) {
    list[x].pb(y);
    list[y].pb(x);
}

void solve(ll DX, ll DY) {
    int i;

    sort(P + 1, P + n + 1);
    memset(addit, 0, sizeof(addit));

    for (i = 1; i <= n; i++) {
        int posl = lower_bound(P + 1, P + n + 1, (point){P[i].x - DX, P[i].y - DY, -1}) - P;
        int posr = upper_bound(P + 1, P + n + 1, (point){P[i].x - DX, P[i].y + DY, -1}) - P;

        if (posl >= posr) continue;

        cnt[P[i].id] += posr - posl;

        add_edge(P[i].id, P[posl].id);
        addit[posl]++;
        addit[posr - 1]--;
    }

    for (i = 1; i <= n; i++) {
        addit[i] += addit[i - 1];
        if (addit[i] == 0) continue;

        add_edge(P[i].id, P[i + 1].id);
    }
}

void dfs(int node) {
    us[node] = true;
    ans += cnt[node];

    for (auto to : list[node])
        if (!us[to])
            dfs(to);
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%d", &n, &a, &b);
    for (i = 1; i <= n; i++) {
        scanf("%lld%lld", &x, &y);
        P[i] = {x - y, x + y, i};
    }

    D = max(abss(P[a].x - P[b].x), abss(P[a].y - P[b].y));

    solve(D, D);

    for (i = 1; i <= n; i++)
        swap(P[i].x, P[i].y);

    solve(D, D - 1);

    dfs(a);
    printf("%lld", ans);

    return 0;
}
