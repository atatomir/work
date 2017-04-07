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

#define maxN 50011
#define lSon (node << 1)
#define rSon (lSon | 1)

struct aint {
    int n;
    vector< vector< pair<int, int> > > data;
    vector<int> upd;
    vector<int> nodes;

    void combine(vector< pair<int, int> >& dest, vector< pair<int, int> >& s1, vector< pair<int, int> >& s2) {
        int i, j, pos;
        pair<int, int> act;

        dest.resize(s1.size() + s2.size());
        merge(s1.begin(), s1.end(), s2.begin(), s2.end(), dest.begin());

        pos = 0;
        for (i = 0; i < dest.size(); i = j) {
            act = mp(dest[i].first, 0);

            for (j = i; j < dest.size(); j++) {
                if (dest[j].first != dest[i].first) break;
                act.second += dest[j].second;
            }

            dest[pos++] = act;
        }
        dest.resize(pos);
    }

    void refr(int node, int l, int r) {
        if (upd[node]) {
            data[node] = {mp(upd[node], r - l + 1)};
        } else {
            combine(data[node], data[lSon], data[rSon]);
        }
    }

    void init(int _n) {
        n = _n;
        data = vector< vector< pair<int, int> > >(4 * n + 11, vector< pair<int, int> >(0));
        upd = vector<int>(4 * n + 11, 0);
    }

    void update(int node, int l, int r, int qL, int qR, int val) {
        if (qL <= l && r <= qR) {
            upd[node] = val;
            refr(node, l, r);
            return;
        }

        int mid = (l + r) >> 1;
        if (upd[node]) {
            upd[lSon] = upd[node]; refr(lSon, l, mid);
            upd[rSon] = upd[node]; refr(rSon, mid + 1, r);
            upd[node] = 0;
        }

        if (qL <= mid) update(lSon, l, mid, qL, qR, val);
        if (qR > mid) update(rSon, mid + 1, r, qL, qR, val);

        refr(node, 1, n);
    }

    void query(int node, int l, int r, int qL, int qR) {
        if (qL <= l && r <= qR) {
            nodes.pb(node);
            return;
        }

        int mid = (l + r) >> 1;
        if (upd[node]) {
            upd[lSon] = upd[node]; refr(lSon, l, mid);
            upd[rSon] = upd[node]; refr(rSon, mid + 1, r);
            upd[node] = 0;
        }

        if (qL <= mid) query(lSon, l, mid, qL, qR);
        if (qR > mid) query(rSon, mid + 1, r, qL, qR);
    }
};

int n, m, c, i, x, y, cnt, op;
vector<int> list[maxN];
int l[maxN], r[maxN];
aint work;
vector< pair<int, int> > aux, aux2;

void dfs(int node, int root) {
    l[node] = ++cnt;

    for (auto to : list[node])
        if (to != root)
            dfs(to, node);

    r[node] = cnt;
}

int main()
{
    freopen("color4.in","r",stdin);
    freopen("color4.out","w",stdout);

    scanf("%d%d%d", &n, &m, &c);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    dfs(1, 0);
    work.init(n);

    work.update(1, 1, n, 1, n, 1);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &op, &x);

        if (op == 0) {
            scanf("%d", &c);
            work.update(1, 1, n, l[x], r[x], c);
        } else {
            work.nodes.clear();
            work.query(1, 1, n, l[x], r[x]);

            aux = work.data[ work.nodes[0] ];
            for (int j = 1; j < work.nodes.size(); j++) {
                aux2 = aux;
                work.combine(aux, aux2, work.data[ work.nodes[j] ]);
            }

            auto best = aux[0];
            for (auto e : aux) {
                if (e.second > best.second)
                    best = e;
                if (e.second == best.second && e.first < best.first)
                    best = e;
            }

            printf("%d %d\n", best.first, best.second);
        }
    }



    return 0;
}
