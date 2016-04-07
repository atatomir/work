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
#define lSon (node << 1)
#define rSon (lSon | 1)

class aint {
    public:
        int n;

        void init(int _n, vector<int> _from) {
            n = _n;
            data.resize(n << 2);
            from = _from;

            init_tree(1, 1, n);
            from.clear();
        }

        void update(int node, int l, int r, int pos, int v) {
            if (l == r) {
                data[node] = v;
                return;
            }

            int mid = (l + r) >> 1;
            if (pos <= mid)
                update(lSon, l, mid, pos, v);
            else
                update(rSon, mid + 1, r, pos, v);

            data[node] = max(data[lSon], data[rSon]);
        }

        int query(int node, int l, int r, int qL, int qR) {
            if (qL <= l && r <= qR)
                return data[node];

            int ans = 0;
            int mid = (l + r) >> 1;
            if (qL <= mid)
                ans = max(ans, query(lSon, l, mid, qL, qR));
            if (qR > mid)
                ans = max(ans, query(rSon, mid + 1, r, qL, qR));

            return ans;
        }


    private:
        vector<int> data;
        vector<int> from;

        void init_tree(int node, int l, int r) {
            if (l == r) {
                data[node] = from[l - 1];
                return;
            }

            int mid = (l + r) >> 1;
            init_tree(lSon, l, mid);
            init_tree(rSon, mid + 1, r);

            data[node] = max(data[lSon], data[rSon]);
        }
};


int n, i, m, x, y, op;
int v[maxN];
vector<int> list[maxN];
bool us[maxN];
int count_bottom[maxN];
int daddy[maxN];

int cnt;
int lvl[maxN];
vector<int> path[maxN];
aint work[maxN];
int belong[maxN];
int pos[maxN];
vector<int> aux;



void dfs(int node) {
    us[node] = true;
    count_bottom[node] = 1;

    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i];

        if (us[to]) {
            list[node][i] = list[node].back();
            list[node].pop_back();
            i--;
            continue;
        }

        lvl[to] = lvl[node] + 1;
        daddy[to] = node;
        dfs(to);
    }

    if (list[node].empty()) {
        //! new path
        path[++cnt].pb(node);
        belong[node] = cnt;
        return;
    }

    int best = list[node][0];

    for (int to : list[node]) {
        count_bottom[node] += count_bottom[to];
        if (count_bottom[to] > count_bottom[best]) best = to;
    }

    best = belong[best];

    belong[node] = best;
    path[best].pb(node);
}

void clean_path(int id) {
    aux.clear();
    reverse(path[id].begin(), path[id].end());
    for (int i = 0; i < path[id].size(); i++)
        pos[ path[id][i] ] = i + 1, aux.pb(v[ path[id][i] ]);
}

void make_paths() {
    int i;

    lvl[1] = 1;
    dfs(1);

    for (i = 1; i <= cnt; i++) {
        clean_path(i);
        work[i].init(path[i].size(), aux);
    }
}

int solve(int x, int y) {
    int R1, R2;
    int ans = 0;

    while (belong[x] != belong[y]) {
        R1 = belong[x];
        R2 = belong[y];

        if(lvl[ path[R1][0] ] < lvl[ path[R2][0] ]) swap(x, y), swap(R1, R2);

        ans = max(ans, work[R1].query(1, 1, work[R1].n, 1, pos[x])  );
        x = daddy[ path[R1][0] ];
    }

    R1 = belong[x];
    if (pos[x] > pos[y]) swap(x, y);
    ans = max(ans, work[R1].query(1, 1, work[R1].n, pos[x], pos[y]) );

    return ans;
}


int main()
{
    freopen("heavypath.in","r",stdin);
    freopen("heavypath.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) scanf("%d", &v[i]);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    make_paths();

    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &op, &x, &y);

        if (op == 0) { //! update
            work[ belong[x] ].update(1, 1, work[ belong[x] ].n, pos[x], y);
        } else { //! query
            printf("%d\n", solve(x, y));
        }
    }


    return 0;
}
