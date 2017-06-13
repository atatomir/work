#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 500011
#define lSon (node << 1)
#define rSon (lSon | 1)

#define inf 1000000000

struct aint {
    int dim;
    pair<int, int> data[maxN * 4 + 11];
    int lazy[maxN * 4 + 11];

    void build(int node, int l, int r) {
        if (l == r) {
            data[node] = mp(inf, l);
            return;
        }

        int mid = (l + r) >> 1;
        build(lSon, l, mid);
        build(rSon, mid + 1, r);
        data[node] = min(data[lSon], data[rSon]);
    }

    void init(int _dim) {
        dim = _dim;
        build(1, 1, dim);
    }

    void prop(int node) {
        lazy[lSon] += lazy[node];
        lazy[rSon] += lazy[node];
        data[lSon].first += lazy[node];
        data[rSon].first += lazy[node];
        lazy[node] = 0;
    }

    void upd(int node, int l, int r, int pos, int v) {
        if (l == r) {
            lazy[node] = 0;
            data[node] = mp(v, l);
            return;
        }

        prop(node);
        int mid = (l + r) >> 1;
        if (pos <= mid) upd(lSon, l, mid, pos, v);
        if (pos > mid) upd(rSon, mid + 1, r, pos, v);
        data[node] = min(data[lSon], data[rSon]);
    }

    void add(int node, int l, int r, int qL, int qR, int v) {
        if (qL > qR) return;
        if (qL <= l && r <= qR) {
            data[node].first += v;
            lazy[node] += v;
            return;
        }

        prop(node);
        int mid = (l + r) >> 1;
        if (qL <= mid) add(lSon, l, mid, qL, qR, v);
        if (qR > mid) add(rSon, mid + 1, r, qL, qR, v);
        data[node] = min(data[lSon], data[rSon]);
    }
};

int n, i;
int vals[maxN], wh[maxN];
pair<int, int> ord[maxN];
set<int> neg, zero, pos;

int data[maxN];
aint work;

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void add(int x, int v) {
    while (x <= n) {
        data[x] += v;
        x += zrs(x);
    }
}

int sum(int x) {
    int ans = 0;
    while (x > 0) {
        ans += data[x];
        x -= zrs(x);
    }
    return ans;
}

void add_zero(int i);

void add_one(int i) {
    //! add this element
    int act_val = sum(wh[i]);
    pos.insert(wh[i]);
    add(wh[i], +1);

    work.upd(1, 1, n, wh[i], vals[i] - act_val - 1);
    work.add(1, 1, n, wh[i] + 1, n, -1);

    if (work.data[1].first < 0) {
        int pp = work.data[1].second;
        i = ord[pp].second;

        pos.erase(pp);
        add(pp, -1);
        work.upd(1, 1, n, pp, inf);
        work.add(1, 1, n, pp + 1, n, +1);
    }
}

void add_zero(int i) {
    zero.insert(wh[i]);
    //! nothing else to do
}

void add_minus_one(int i) {
    //! add this element
    neg.insert(wh[i]);
    add(wh[i], -1);
    work.add(1, 1, n, wh[i] + 1, n, +1);

    int rez = i;

    //! remove last negative element
    auto it = neg.end(); it--;
    int pp = *it;
    i = ord[pp].second;

    neg.erase(it);
    add(pp, +1);
    work.add(1, 1, n, pp + 1, n, -1);

    //! add back this element
    int act_val = sum(pp);
    if (act_val == vals[i])
        add_zero(i);

    if (act_val > vals[i]) {
        neg.insert(pp);
        add(pp, -1);

        work.add(1, 1, n, pp + 1, n, +1);
    }

    //! remove first zero element
    it = zero.begin();
    if (*it == 1000000000) return;
    pp = *it;
    i = ord[pp].second;

    zero.erase(pp);

    act_val = sum(pp);
    if (act_val == vals[i])
        add_zero(i);

    if (act_val < vals[i])
        add_one(i);
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &vals[i]);
        ord[i] = mp(vals[i], i);
    }

    sort(ord + 1, ord + n + 1);
    for (i = 1; i <= n; i++) wh[ord[i].second] = i;

    zero.insert(1000000000);
    work.init(n);

    for (i = 1; i <= n; i++) {
        int pp = wh[i];
        int act_val = sum(pp);

        int last = pos.size() - neg.size();

        if (act_val < vals[i])
            add_one(i);

        if (act_val == vals[i])
            add_zero(i);

        if (act_val > vals[i])
            add_minus_one(i);

        /*for (auto e : neg) cerr << e << ' ';
        cerr << "      " << i << '\n';

        for (auto e : zero) cerr << e << ' ';
        cerr << "      " << i << '\n';

        for (auto e : pos) cerr << e << ' ';
        cerr << "      " << i << '\n';*/

        //if (n == 100000 && vals[1] == 55796 && i != 78817) continue;
        //if (i == 78817 && n == 100000 && vals[1] == 55796) printf("%d %d %d\n", act_val, vals[i], last);

        printf("%d\n", pos.size() - neg.size());
    }

    return 0;
}
