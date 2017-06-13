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

#define maxN 200011

struct sat2 {
    int dim, i;
    vector<int> from[maxN], to[maxN];
    int sol[maxN];

    bool us[maxN];
    vector<int> aux;
    vector<int> comp;

    void init(int _dim) {
        dim = _dim;
        for (i = 1; i <= 2 * dim; i++) from[i].clear(), to[i].clear();
    }

    void add_rel(int a, int b) {
        if (a < 0) a = dim - a;
        if (b < 0) b = dim - b;
        to[a].pb(b);
        from[b].pb(a);
    }

    void add_or(int a, int b) {
        add_rel(-a, b);
        add_rel(-b, a);
    }

    void dfs_to(int node) {
        us[node] = true;
        for (auto e : to[node])
            if (!us[e])
                dfs_to(e);
        aux.pb(node);
    }

    void dfs_from(int node) {
        us[node] = true;
        for (auto e : from[node])
            if (!us[e])
                dfs_from(e);
        comp.pb(node);
    }

    int inv(int x) {
        if (x <= dim) x += dim;
        else          x -= dim;
        return x;
    }

    int get_color() {
        int ans = 0;
        for (auto e : comp)
            if (sol[e] == 1)
                ans = 1;
        return ans;
    }

    bool set_color(int c) {
        for (auto e : comp) {
            if (sol[e] != -1 && sol[e] != c) return false;
            sol[e] = c;

            int ii = inv(e);
            if (sol[ii] != -1 && sol[ii] != c ^ 1) return false;
            sol[ii] = c ^ 1;
        }

        return true;
    }

    bool run() {
        int i;

        for (i = 1; i <= 2 * dim; i++) sol[i] = -1;
        aux.clear();
        memset(us, 0, sizeof(us));
        for (i = 1; i <= 2 * dim; i++)
            if (!us[i])
                dfs_to(i);

        memset(us, 0, sizeof(us));
        reverse(aux.begin(), aux.end());
        for (auto e : aux) {
            if (us[e]) continue;
            comp.clear();
            dfs_from(e);

            int col = get_color();
            if (!set_color(col)) return false;
        }

        return true;
    }
};

struct cell {
    ll x, y, a, b;
};

int n, i;
cell C[maxN];
vector<ll> xx, yy;
map<ll, ll> Mx, My;
sat2 work;

bool check(int limit) {
    int i;

    work.init(xx.size() + yy.size());
    for (i = 1; i <= limit; i++) {
        int n1 = C[i].x;
        int n2 = xx.size() + C[i].y;

        if (C[i].a == C[i].b) {
            work.add_or(n1, -n2);
            work.add_or(-n1, n2);
        } else {
            work.add_or(-n1, -n2);
            work.add_or(n1, n2);
        }
    }

    return work.run();
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lld%lld%lld%lld", &C[i].x, &C[i].y, &C[i].a, &C[i].b);
        xx.pb(C[i].x);
        yy.pb(C[i].y);
    }

    sort(xx.begin(), xx.end());
    xx.resize(unique(xx.begin(), xx.end()) - xx.begin());
    for (i = 0; i < xx.size(); i++) Mx[xx[i]] = i + 1;
    for (i = 1; i <= n; i++) C[i].x = Mx[C[i].x];

    sort(yy.begin(), yy.end());
    yy.resize(unique(yy.begin(), yy.end()) - yy.begin());
    for (i = 0; i < yy.size(); i++) My[yy[i]] = i + 1;
    for (i = 1; i <= n; i++) C[i].y = My[C[i].y];

    int ans = 0;
    for (int step = 1 << 20; step > 0; step >>= 1)
        if (ans + step <= n)
            if (check(ans + step))
                ans += step;

    for (i = 1; i <= ans; i++)
        printf("Yes\n");

    for (i = 1; i <= n - ans; i++)
        printf("No\n");

    //! why?


    return 0;
}
