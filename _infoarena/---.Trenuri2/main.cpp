#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011
#define maxSpeed 1024
#define maxLog 17

class aib {
    public:
        void init(int _n, double *_data) {
            n = _n;
            data = _data;
            memset(data, 0, sizeof(double) * (n + 3));
        }

        void add(int pos, double val) {
            while (pos <= n) {
                data[pos] += val;
                pos += zrs(pos);
            }
        }

        double sum(int pos) {
            double ans = 0.00;

            while (pos > 0) {
                ans += data[pos];
                pos -= zrs(pos);
            }

            return ans;
        }

        double sum_from_to(int a, int b) {
            return sum(b) - sum(a - 1);
        }

    private:
        int n;
        double *data;

        int zrs(int x) {
            return (x & (x - 1)) ^ (x);
        }
};

struct Edge {
    int to, dist, limit;

    Edge(int _to, int _dist, int _limit) {
        to = _to;
        dist = _dist;
        limit = _limit;
    }
};

//!--------------------------------------

int n, i, x, y, d, v, m;
vector<Edge> list[maxN];
int up_dad[maxLog][maxN];
int lvl[maxN];

int q_limit[maxN];
vector<int> Queries[maxN];

double _aib_dist[maxSpeed];
double _aib_time[maxSpeed];

aib work_dist;
aib work_time;

double Answer[maxN];

//!-------------------------------------

void dfs(int node) {
    for (int i = 0; i < list[node].size(); i++) {
        auto who = list[node][i];

        if (lvl[who.to] > 0) {
            list[node][i] = list[node][ list[node].size() - 1 ];
            list[node].pop_back();
            i--;
            continue;
        }

        lvl[who.to] = lvl[node] + 1;
        up_dad[0][who.to] = node;
        dfs(who.to);
    }
}

int goUp(int x, int how) {
    for (int i = 0; how > 0; i++) {
        if (how & 1) x = up_dad[i][x];
        how >>= 1;
    }
    return x;
}

int getLca(int x, int y) {
    if (lvl[x] > lvl[y]) swap(x, y);

    y = goUp(y, lvl[y] - lvl[x]);
    if (x == y) return x;
    for (int actLog = maxLog - 1; actLog >= 0; actLog--) {
        if (up_dad[actLog][x] != up_dad[actLog][y]) {
            x = up_dad[actLog][x];
            y = up_dad[actLog][y];
        }
    }

    return up_dad[0][x];
}

void dfs_solve(int node) {
    for (auto qq : Queries[node]) {
        bool diff = false;

        if (qq < 0) {
            diff = true;
            qq = -qq;
        }

        int how = q_limit[qq];
        double aux = work_time.sum(how) + work_dist.sum_from_to(how + 1, 1000) / (1.00 * how);
        if (diff == false)
            Answer[qq] += aux;
        else
            Answer[qq] -= 2.00 * aux;
    }

    //! queries solved... go ahead

    for (auto who : list[node]) {
        work_dist.add(who.limit, who.dist);
        work_time.add(who.limit, 1.00 * who.dist / (1.00 * who.limit));

        dfs_solve(who.to);

        work_dist.add(who.limit, -who.dist);
        work_time.add(who.limit, -(1.00 * who.dist / (1.00 * who.limit)));
    }
}

int main()
{
    freopen("trenuri2.in","r",stdin);
    freopen("trenuri2.out","w",stdout);

    scanf("%d %d", &n, &m);
    for (i = 1; i < n; i++) {
        scanf("%d%d%d%d", &x, &y, &d, &v);
        list[x].pb(Edge(y, d, v));
        list[y].pb(Edge(x, d, v));
    }

    lvl[1] = 1;
    dfs(1);

    for (int actLog = 1; actLog < maxLog; actLog++)
        for (i = 1; i <= n; i++)
            up_dad[actLog][i] = up_dad[actLog - 1][ up_dad[actLog -1][i] ];

    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &v);

        int lca = getLca(x, y);
        q_limit[i] = v;

        Queries[x].pb(i);
        Queries[y].pb(i);
        Queries[lca].pb(-i);
    }

    work_dist.init(1003, _aib_dist);
    work_time.init(1003, _aib_time);

    dfs_solve(1);

    for (i = 1; i <= m; i++) printf("%.3lf\n", Answer[i]);

    return 0;
}
