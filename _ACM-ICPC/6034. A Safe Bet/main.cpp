#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 400011

struct aib {
    vector<int> data;
    int n;

    void init(int _n) {
        n = _n;
        data = vector<int>(n + 10, 0);
    }

    int zrs(int x) {
        return (x ^ (x - 1)) & x;
    }

    int sum(int x) {
        int ans = 0;

        while (x > 0) {
            ans += data[x];
            x -= zrs(x);
        }

        return ans;
    }

    void add(int pos, int v) {
        while (pos <= n) {
            data[pos] += v;
            pos += zrs(pos);
        }
    }

    int cb(int v) {
        int ans = 0;

        for (int step = 1 << 18; step > 0; step >>= 1)
            if (ans + step <= n)
                if (data[ans + step] < v)
                    v -= data[ans += step];

        return ans + 1;
    }
};

struct mirror {
    int tp;
    int x, y;
};

struct ray {
    int pos, l, r;
};

struct event {
    int x, y, v;
};

int test;
int n, m, a, b, i, x, y;
vector<mirror> M;
vector<int> xx, yy;

vector<ray> ho1, ho2, ve1, ve2;
vector< pair<int, int> > ids_ln[maxN], ids_co[maxN];

aib work;
vector<event> E;
ll ans;
pair<int, int> sm;



void norm_them() {
    map<int, int> mp;

    xx = {0, 1, n, n + 1};
    yy = {0, 1, m, m + 1};
    for (auto e : M) {
        xx.pb(e.x);
        yy.pb(e.y);
    }

    sort(xx.begin(), xx.end());
    xx.resize(unique(xx.begin(), xx.end()) - xx.begin());
    mp.clear();
    for (i = 0; i < xx.size(); i++) mp[xx[i]] = i;
    n = xx.size() - 2;
    for (i = 0; i < M.size(); i++)
        M[i].x = mp[M[i].x];

    sort(yy.begin(), yy.end());
    yy.resize(unique(yy.begin(), yy.end()) - yy.begin());
    mp.clear();
    for (i = 0; i < yy.size(); i++) mp[yy[i]] = i;
    m = yy.size() - 2;
    for (i = 0; i < M.size(); i++)
        M[i].y = mp[M[i].y];
}

bool get_ray(vector<ray>& h, vector<ray>& v, int step) {
    int x, y, i, id, dir;

    h.clear();
    v.clear();

    for (i = 0; i <= n + 1; i++) ids_ln[i].clear();
    for (i = 0; i <= m + 1; i++) ids_co[i].clear();

    id = 0;
    for (auto e : M) {
        ids_ln[e.x].pb(mp(e.y, id));
        ids_co[e.y].pb(mp(e.x, id));
        id++;
    }

    for (i = 0; i <= n + 1; i++) sort(ids_ln[i].begin(), ids_ln[i].end());
    for (i = 0; i <= m + 1; i++) sort(ids_co[i].begin(), ids_co[i].end());

    if (step == 0) {
        x = 1; y = 0;
        dir = 0;
    } else {
        x = n; y = m + 1;
        dir = 2;
    }

    while (true) {
        if (dir == 0) {
            auto it = lower_bound(ids_ln[x].begin(), ids_ln[x].end(), mp(y + 1, 0));
            if (it == ids_ln[x].end()) {
                h.pb({x, y + 1, m});
                return (x == n);
            }

            h.pb({x, y + 1, it->first - 1});
            x = M[it->second].x;
            y = M[it->second].y;
            dir = (M[it->second].tp == 0 ? 3 : 1);
        }

        if (dir == 1) {
            auto it = lower_bound(ids_co[y].begin(), ids_co[y].end(), mp(x + 1, 0));
            if (it == ids_co[y].end()) {
                v.pb({y, x + 1, n});
                return false;
            }

            v.pb({y, x + 1, it->first - 1});
            x = M[it->second].x;
            y = M[it->second].y;
            dir = (M[it->second].tp == 0 ? 2 : 0);
        }

        if (dir == 2) {
            auto it = lower_bound(ids_ln[x].begin(), ids_ln[x].end(), mp(y, 0));
            if (it == ids_ln[x].begin()) {
                h.pb({x, 1, y - 1});
                return false;
            }
            it--;

            h.pb({x, it->first + 1, y - 1});
            x = M[it->second].x;
            y = M[it->second].y;
            dir = (M[it->second].tp == 0 ? 1 : 3);

        }

        if (dir == 3) {
            auto it = lower_bound(ids_co[y].begin(), ids_co[y].end(), mp(x, 0));
            if (it == ids_co[y].begin()) {
                v.pb({y, 1, x - 1});
                return false;
            }
            it--;

            v.pb({y, it->first + 1, x - 1});
            x = M[it->second].x;
            y = M[it->second].y;
            dir = (M[it->second].tp == 0 ? 0 : 2);

        }

    }

}

void get_intersections(vector<ray>& h, vector<ray>& v) {
    int i;

    sort(h.begin(), h.end(), [](const ray& a, const ray& b)->bool const {
        return a.pos < b.pos;
    });

    E.clear();
    for (auto e : v) {
        E.pb({e.l, e.pos, +1});
        E.pb({e.r + 1, e.pos, -1});
    }

    sort(E.begin(), E.end(), [](const event& a, const event& b)->bool const {
        return a.x > b.x;
    });

    work.init(m + 3);

    for (auto e : h) {
        while (!E.empty()) {
            if (E.back().x > e.pos) break;
            work.add(E.back().y, E.back().v);
            E.pop_back();
        }

        ll cnt = work.sum(e.r) - (e.l - 1 > 0 ? work.sum(e.l - 1) : 0);
        if (cnt == 0) continue;

        ans += cnt;
        if (e.pos <= sm.first) {
            int bg = (e.l - 1 > 0 ? work.sum(e.l - 1) : 0);
            sm = min(sm, mp(e.pos, work.cb(bg + 1)));
        }
    }
}


int main()
{
    freopen("test.in","r",stdin);

    while (scanf("%d%d%d%d", &n, &m, &a, &b) == 4) {
        printf("Case %d: ", ++test);

        M.clear();
        for (i = 1; i <= a; i++) {
            scanf("%d%d", &x, &y);
            M.pb({0, x, y});
        }

        for (i = 1; i <= b; i++) {
            scanf("%d%d", &x, &y);
            M.pb({1, x, y});
        }

        norm_them();
        bool already = get_ray(ho1, ve1, 0);
        get_ray(ho2, ve2, 1);

        if (already) {
            printf("0\n");
            continue;
        }

        ans = 0;
        sm = mp(maxN << 2, maxN << 2);

        get_intersections(ho1, ve2);
        get_intersections(ho2, ve1);

        if (ans == 0) {
            printf("impossible");
        } else {
            printf("%lld %d %d", ans, xx[sm.first], yy[sm.second]);
        }

        printf("\n");
    }



    return 0;
}
