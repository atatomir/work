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
#define inf 1000000000

struct Line {
    ll a, b;
    ll best_from;

    Line() {}
    Line(ll _a, ll _b, ll _st) {
        a = _a; b = _b;
        best_from = _st;
    }

    ll compute(ll x) {
        return a * x + b;
    }
};


int n, i, x, y, c;
ll delay[maxN], v[maxN], depth[maxN], cost[maxN];
vector< pair<int, int> > list[maxN];
bool us[maxN];

int cnt;
Line S[maxN], aux;

vector< pair<int, Line> > recov;


ll get_best(ll speed) {
    int ans = 0;

    for (int step = 1 << 17; step > 0; step >>= 1)
        if (ans + step <= cnt)
            if (S[ans + step].best_from <= speed)
                ans += step;

    return S[ans].compute(speed);
}

void add_line(Line aux) {
    int ans = 0;

    //! binary search the last available Line
    for (int step = 1 << 17; step > 0; step >>= 1)
        if (ans + step <= cnt)
            if (S[ans + step].compute(S[ans + step].best_from) < aux.compute(S[ans + step].best_from))
                ans += step;

    //! you need this informaion to recover data later
    ans++;
    recov.pb(mp(cnt, S[ans]));
    S[ans] = aux;
    cnt = ans;

    if (cnt == 1) return;

    //! now compute aux.best_from
    ans = 0;

    for (int step = 1 << 30; step > 0; step >>= 1)
        if (S[cnt - 1].compute(ans + step) < S[cnt].compute(ans + step))
            ans += step;

    S[cnt].best_from = ans + 1;
}

void dfs(int node) {
    us[node] = true;

    for (auto act : list[node]) {
        int to = act.first;
        ll pay = act.second;
        if (us[to]) continue;

        //! compute values for son
        depth[to] = depth[node] + pay;
        cost[to] = delay[to] + v[to] * depth[to] + get_best(v[to]);

        //! add new line
        aux = Line(-depth[to], cost[to] , 0);
        add_line(aux);

        dfs(to);

        //! recover information
        S[cnt] = recov.back().second;
        cnt = recov.back().first;
        recov.pop_back();
    }
}

int main()
{
    freopen("harbingers.in","r",stdin);
    freopen("harbingers.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i < n; i++) {
        scanf("%d%d%d", &x, &y, &c);
        list[x].pb(mp(y, c));
        list[y].pb(mp(x, c));
    }

    for (i = 2; i <= n; i++) scanf("%lld%lld", &delay[i], &v[i]);

    S[++cnt] = Line(0, 0, -inf);
    dfs(1);

    for (i = 2; i <= n; i++) printf("%lld ", cost[i]);


    return 0;
}
