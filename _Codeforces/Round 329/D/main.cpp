#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 200011
#define maxLog 21

#define lSon (node << 1)
#define rSon (lSon | 1)

class aint {
    public:
        void init(int _n, double *_data) {
            n = _n;
            data = _data;

            int lim = n * 4;
            for (int i = 1; i < lim; i++) data[i] = 1.00;
        }

        void update(int node, int l, int r, int qL, int qR, double qV) {
            if (qL <= l && r <= qR) {
                data[node] *= qV;
                return;
            }

            int mid = (l + r) >> 1;
            if (qL <= mid)
                update(lSon, l, mid, qL, qR, qV);
            if (qR >  mid)
                update(rSon, mid + 1, r, qL, qR, qV);
        }

        double query(int node, int l, int r, int qNode) {
            if (l == r) return data[node];

            int mid = (l + r) >> 1;
            if (qNode <= mid)
                return data[node] * query(lSon, l, mid, qNode);
            else
                return data[node] * query(rSon, mid + 1 ,r, qNode);
        }

    private:
        int n;
        double *data;
};

int n, i, m, x, y, op;
vector< pair<int, int> > list[maxN];
int which[maxN];
double values[maxN];
bool us[maxN];

int p;
double act[maxN], v, c;
int dad[maxLog][maxN];
int lvl[maxN];

int dim;
int ll[maxN];
int rr[maxN];

double aint_data[maxN << 2];
aint work;

void dfs(int node) {
    us[node] = true;

    ll[node] = ++dim;

    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i].first;
        int id = list[node][i].second;

        if (us[to]) {
            list[node][i] = list[node][ list[node].size() - 1 ];
            list[node].pop_back();
            i--;
            continue;
        }

        which[id] = to;
        act[to] = values[id];
        dad[0][to] = node;
        lvl[to] = lvl[node] + 1;
        dfs(to);
    }

    rr[node] = dim;
}

int goUp(int node, int how) {
    for (int i = 0; how > 0; i++) {
        if (how & 1) node = dad[i][node];
        how >>= 1;
    }
    return node;
}

int getLca(int x, int y) {
    if (lvl[x] > lvl[y]) swap(x, y);
    y = goUp(y, lvl[y] - lvl[x]);

    if (x == y) return x;

    for (int actLog = maxLog - 1; actLog >= 0; actLog--) {
        if (dad[actLog][x] != dad[actLog][y]) {
            x = dad[actLog][x];
            y = dad[actLog][y];
        }
    }
    return dad[0][x];
}

void compute_lca() {
    for (int actLog = 1; actLog < maxLog; actLog++)
        for (int i = 1; i <= n; i++)
            dad[actLog][i] = dad[actLog - 1][ dad[actLog - 1][i] ];
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i < n; i++) {
        scanf("%d%d%lf", &x, &y, &v);
        list[x].pb(mp(y, i));
        list[y].pb(mp(x, i));

        values[i] = v;
    }

    dfs(1);
    compute_lca();

    act[1] = 1;
    work.init(dim, aint_data);
    for (i = 1; i <= n; i++) {
        work.update(1, 1, n, ll[i], rr[i], act[i]);
        //cerr << act[i] << ' ' << log(act[i]) << ' ' << exp(log(act[i])) << '\n';
    }

    for (i = 1; i <= m; i++) {
        scanf("%d", &op);
        if (op == 1) {
            //! query

            scanf("%d%d%lf", &x, &y, &v);
            int lca = getLca(x, y);

            double aux = v / ((work.query(1, 1, n, ll[x]) * work.query(1, 1, n, ll[y]) ) /
                              ((work.query(1, 1, n, ll[lca])) * work.query(1, 1, n, ll[lca]))) ;

            long long ans = aux;
            printf("%I64d\n", ans);
        } else {
            //! update

            scanf("%d%lf", &p, &c);
            p = which[p];

            work.update(1, 1, n, ll[p], rr[p], 1.00/act[p]);
            act[p] = c;
            work.update(1, 1, n, ll[p], rr[p], act[p]);
        }
    }

    return 0;
}
