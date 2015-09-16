#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;

#define pb push_back
#define mp make_pair
#define ll long long

#define maxN 100011
#define maxLog 19
#define lSon (node << 1)
#define rSon (lSon | 1)
#define inf 1000000011LL

class myAint {
    public:
        void init(int _n, ll *_data) {
            n = _n;
            data = _data;

            makeTree(1, 1, n);
        }

        void update(int node, int l, int r, int qL, int qR, int val) {
            if (qL <= l && r <= qR) {
                data[node] += val;
                return;
            }

            int mid = (l + r) >> 1;
            if (qL <= mid) update(lSon, l, mid, qL, qR, val);
            if (qR >  mid) update(rSon, mid + 1, r, qL, qR, val);
        }

        ll _query(int node, int l, int r,int qq) {
            if (l == r) return data[node];

            int mid = (l + r) >> 1;
            if (qq <= mid)
                return data[node] + _query(lSon, l, mid, qq);
            else
                return data[node] + _query(rSon, mid + 1, r, qq);
        }

        ll query(int pos) {
            if (pos == 0) return 0;
            return _query(1, 1, n, pos);
        }

    private:
        int n;
        ll *data;

        void makeTree(int node, int l,int r) {
            if (l == r) {
                data[node] = 0;
                return;
            }

            int mid = (l + r)>> 1;
            makeTree(lSon, l, mid);
            makeTree(rSon, mid + 1, r);
        }
};

int n, m, i, x, y, cost;
vector<int> list[maxN];
vector< pair<int, pair<int, int> > > Guard[maxN];
int dad[maxN];

int dim;
int wh[maxN];
int lvl[maxLog][maxN << 1];
int who[maxLog][maxN << 1];
int use[maxN << 1];

int wh_cont;
int whL[maxN];
int whR[maxN];
int help[maxN];

ll aint_data[maxN << 2];
ll aint_data_s[maxN << 2];

myAint pAint, sAint;
ll dp[maxN];
ll dpSon[maxN];

void dfs(int node, int _lvl) {
    dim++;
    wh[node] = dim;
    lvl[0][dim] = _lvl;
    who[0][dim] = node;

    whL[node] = ++wh_cont;
    help[wh_cont] = node;

    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i];
        if (dad[node] == to) continue;

        dad[to] = node;
        dfs(to, _lvl + 1);

        dim++;
        lvl[0][dim] = _lvl;
        who[0][dim] = node;
    }

    whR[node] = wh_cont;
}

int rmq_query(int l, int r) {
    int actLog = use[r - l + 1];
    int _dim = 1 << actLog;
    if (lvl[actLog][l] < lvl[actLog][r - _dim + 1])
        return who[actLog][l];
    else
        return who[actLog][r - _dim + 1];
}

void make_rmq() {
    use[1] = 0;
    for (int i = 2; i <= dim; i++) {
        use[i] = use[i - 1];
        if (i >= (1 << (use[i] + 1))) use[i]++;
    }

    for (int actLog = 1; actLog <= use[dim]; actLog++) {
        int def = 1 << (actLog - 1);
        int limit = dim - def - def + 1;

        for (int i = 1; i <= limit; i++) {
            if (lvl[actLog - 1][i] < lvl[actLog -1 ][i + def]) {
                lvl[actLog][i] = lvl[actLog - 1][i];
                who[actLog][i] = who[actLog - 1][i];
            } else {
                lvl[actLog][i] = lvl[actLog - 1][i + def];
                who[actLog][i] = who[actLog - 1][i + def];
            }
        }
    }
}

stack< int > S;
void dfs_solve(int node) {
    int i;
    pair<int, pair<int, int> > act;

    for (i = 1; i <= n; i++) {
        dp[i] = inf;
        dpSon[i] = 0;
    }

    while(!S.empty()) S.pop();
    S.push(1);

    while(!S.empty()) {
        node = S.top();

        if (list[node].empty()) {
            sAint.update(1, 1, n, whL[node], whR[node], dpSon[node]);

            for (i = 0; i < Guard[node].size(); i++) {
                act = Guard[node][i];

                ll actCost = act.first +
                            sAint.query(whL[act.second.first]) + sAint.query(whL[act.second.second]) -
                            sAint.query(whL[node]) - sAint.query(whL[dad[node]]) -
                            pAint.query(whL[act.second.first]) - pAint.query(whL[act.second.second]) +
                            2 * pAint.query(whL[node]);

                dp[node] = min(dp[node], actCost);
            }

            pAint.update(1, 1, n, whL[node], whR[node], dp[node]);
            S.pop();

            dpSon[dad[node]] += dp[node];
        } else {
            if (dad[node] == list[node][ list[node].size() - 1 ]) {
                list[node].pop_back();
                continue;
            }

            S.push(list[node][ list[node].size() - 1 ]);
            list[node].pop_back();
        }
    }

}

int main()
{
    freopen("paznici3.in", "r", stdin);
    freopen("paznici3.out", "w", stdout);

    scanf("%d %d", &n, &m);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    dfs(1, 1);
    make_rmq();

    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &cost, &x, &y);

        if (wh[x] > wh[y]) swap(x, y);
        Guard[ rmq_query(wh[x], wh[y]) ].pb(mp(cost, mp(x, y)));
    }

    pAint.init(n, aint_data);
    sAint.init(n, aint_data_s);

    dfs_solve(1);
    printf("%lld", pAint.query(1));

    return 0;
}
