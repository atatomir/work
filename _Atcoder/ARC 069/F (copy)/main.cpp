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

#define maxN 10011

struct aib {
    int n;
    vector<int> data;

    void init(int _n) {
        n = _n;
        data = vector<int>(n + 11, 0);
    }

    int zrs(int x) {
        return (x ^ (x - 1)) & x;
    }

    void add(int pos, int v) {
        while (pos <= n) {
            data[pos] += v;
            pos += zrs(pos);
        }
    }

    int sum(int pos) {
        int ans = 0;
        while (pos > 0) {
            ans += data[pos];
            pos -= zrs(pos);
        }
        return ans;
    }

    int cb(int x) {
        int ans = 0;

        for (int step = 1 << 15; step > 0; step >>= 1)
            if (ans + step <= n)
                if (data[ans + step] <= x)
                    ans += step, x -= data[ans];

        return ans;
    }
};

int n, i;
pair<int, int> p[maxN];
int posx[maxN], posy[maxN];
pair<int, int> overx[maxN], overy[maxN];

int lx[maxN], rx[maxN], ly[maxN], ry[maxN];
int tp[maxN];

aib wh, bl;
aib xwh, ybl;
vector< pair<int, int> > changed;
bool ok;

void col_bl(int node);

void col_wh(int node) {
    if (tp[node] == 2) ok = false;
    if (!ok) return;

    if (tp[node] == 1) return;

    int pos = posx[node];
    int l = lx[pos];
    int r = rx[pos];

    tp[node] = 1;

    wh.add(pos, -1);
    bl.add(posy[node], -1);

    xwh.add(pos, +1);

    while (ok) {
        int src = wh.sum(r);
        int he = wh.cb(src - 1) + 1;

        if (he < l) break;
        if (src == 0) break;

        col_bl(overx[he].second);
    }

    if (xwh.sum(r) - xwh.sum(l - 1) != 1)
        ok = false;
}

void col_bl(int node) {
    if (tp[node] == 1) ok = false;
    if (!ok) return;

    if (tp[node] == 2) return;


    int pos = posy[node];
    int l = ly[pos];
    int r = ry[pos];

    tp[node] = 2;
    changed.pb(mp(node, 2));

    bl.add(pos, -1);
    wh.add(posx[node], -1);

    ybl.add(pos, +1);

    while (ok) {
        int src = bl.sum(r);
        int he = bl.cb(src - 1) + 1;

        if (he < l) break;
        if (src == 0) break;

        col_wh(overy[he].second);
    }

    if (ybl.sum(r) - ybl.sum(l - 1) != 1)
        ok = false;

}

void refr(int node) {
    if (tp[node] == 1) {
        int pos = posx[node];

        wh.add(pos, +1);
        bl.add(posy[node], +1);
        xwh.add(pos, -1);
    }

    if (tp[node] == 2) {
        int pos = posy[node];

        bl.add(pos, +1);
        wh.add(posx[node], +1);
        ybl.add(pos, -1);
    }

    tp[node] = 0;
}

bool check(int d) {
    int i;

    wh.init(n); xwh.init(n);
    bl.init(n); ybl.init(n);


    for (i = 1; i <= n; i++) {
        tp[i] = 0;

        wh.add(i, +1);
        bl.add(i, +1);

        lx[i] = lower_bound(overx + 1, overx + n + 1, mp(overx[i].first - d, 0)) - overx;
        rx[i] = upper_bound(overx + 1, overx + n + 1, mp(overx[i].first + d, 0)) - overx - 1;

        ly[i] = lower_bound(overy + 1, overy + n + 1, mp(overy[i].first - d, 0)) - overy;
        ry[i] = upper_bound(overy + 1, overy + n + 1, mp(overy[i].first + d, 0)) - overy - 1;
    }

    //if (d == 3)
    //    cerr << 'd';


    for (i = 1; i <= n; i++) {
        if (tp[i] != 0) continue;

        changed.clear();
        ok = true;
        col_bl(i);
        if (ok) continue;

        for (auto e : changed)
            refr(e.first);

        /*for (auto e : changed) {
            if (e.second == 1)
                col_wh(e.first);
            else
                col_bl(e.first);
        }*/

        changed.clear();
        ok = true;
        col_wh(i);
        if (ok) continue;

        return false;
    }

    return true;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &p[i].first, &p[i].second);
        overx[i] = mp(p[i].first, i);
        overy[i] = mp(p[i].second, i);
    }

    sort(overx + 1, overx + n + 1);
    sort(overy + 1, overy + n + 1);

    for (i = 1; i <= n; i++) {
        posx[ overx[i].second ] = i;
        posy[ overy[i].second ] = i;
    }

    ll ans = -1;
    for (ll step = 1LL << 30; step > 0; step >>= 1)
        if (ans + step <= 1000000000)
            if (check(ans + step))
                ans += step;

    printf("%lld", ans + 1);



    return 0;
}
