#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 10011
#define lSon (node << 1)
#define rSon (lSon | 1)
#define inf 1000000

struct flow_edge {
    int to;
    int C, F;
};

struct big_flow {
    int i, dim, S, D;
    vector<flow_edge> edges;
    vector< vector<int> > list;
    int total_flow;

    vector<bool> us;
    vector<int> prov;
    queue<int> Q;

    void init(int _dim, int _S, int _D) {
        dim = _dim; S = _S; D = _D;
        edges.clear();
        list = vector< vector<int> >(dim + 11, vector<int>(0));
        us = vector<bool>(dim + 11, false);
        prov = vector<int>(dim + 11, 0);
    }

    void add_dir_edge(int x, int y, int cap) {
        edges.pb({y, cap, 0});
        list[x].pb(edges.size() - 1);
        edges.pb({x, 0, 0});
        list[y].pb(edges.size() - 1);
    }

    void add_edge(int x, int y, int cap) {
        edges.pb({y, cap, 0});
        list[x].pb(edges.size() - 1);
        edges.pb({x, cap, 0});
        list[y].pb(edges.size() - 1);
    }

    bool bellman() {
        int i;

        for (i = 0; i <= dim + 4; i++) {
            us[i] = false;
            prov[i] = 0;
        }

        us[S] = true;
        Q.push(S);

        while (!Q.empty()) {
            int node = Q.front(); Q.pop();
            if (node == D) continue;

            for (auto e : list[node]) {
                auto aux = edges[e];

                if (us[aux.to]) continue;
                if (aux.C == aux.F) continue;
                us[aux.to] = true;
                Q.push(aux.to);
                prov[aux.to] = e;
            }
        }

        if (!us[D]) return false;

        for (auto e : list[D]) {
            auto aux = edges[e];
            if (!us[aux.to]) continue;
            if (edges[e ^ 1].C == edges[e ^ 1].F) continue;

            prov[D] = e ^ 1;
            int ff = 1000000000;


            for (int node = D; node != S && ff > 0; node = edges[ prov[node] ^ 1 ].to)
                ff = min(ff, edges[prov[node]].C - edges[prov[node]].F);

            if (ff > 0)
            for (int node = D; node != S; node = edges[ prov[node] ^ 1 ].to) {
                edges[prov[node]].F += ff;
                edges[prov[node] ^ 1].F -= ff;
            }

            total_flow += ff;
        }

        return true;
    }

    int run() {
        total_flow = 0;
        while (bellman());
        return total_flow;
    }
};

int n, m, i, pos, op;
int x, y, xx, yy;
set< pair< pair<int, int>, int> > S;
vector< pair< pair<int, int>, pair<int, int> > > ord;
big_flow work;

int cnt, cnt_ln, cnt_co;
vector<int> leaves_ln, leaves_co;
vector<int> nodes_ln, nodes_co;

vector< pair< pair<int, int>, int> > to_add, to_rm;

void walk(int node, int l, int r, int qL, int qR, int bonus, vector<int>& data) {
    if (qL <= l && r <= qR) {
        data.pb(bonus + node);
        return;
    }

    int mid = (l + r) >> 1;
    if (qL <= mid) walk(lSon, l, mid, qL, qR, bonus, data);
    if (qR > mid) walk(rSon, mid + 1, r, qL, qR, bonus, data);
}

void add_rect(int x, int y, int xx, int yy) {
    //cerr << x << ' ' << y << ' ' << xx << ' ' << yy << '\n';

    if (x > xx || y > yy) return;
    if (xx > n || yy > n) return;


    cerr << x << ' ' << y << ' ' << xx << ' ' << yy << '\n';
    nodes_ln.clear();
    nodes_co.clear();

    walk(1, 1, n, x, xx, cnt_ln, nodes_ln);
    walk(1, 1, n, y, yy, cnt_co, nodes_co);

    cnt++;
    for (auto e : nodes_ln)
        work.add_dir_edge(e, cnt, inf);
    for (auto e : nodes_co)
        work.add_dir_edge(cnt, e, inf);
}

void remove_now() {
    auto it = S.lower_bound(mp(mp(y, 0), 0));
    while (it != S.begin()) {
        it--;
        if (it->first.second < y) break;
    }

    to_add.clear();
    to_rm.clear();

    for (; it != S.end(); it++) {
        if (it->first.second < y) continue;
        if (it->first.first > yy) break;
        auto aux = *it;
        to_rm.pb(*it);

        if (it->first.first < y && it->first.second > yy) {
            //! split both
            add_rect(aux.second, y, pos - 1, yy);
            to_add.pb(mp(mp(aux.first.first, y - 1), aux.second));
            to_add.pb(mp(mp(yy + 1, aux.first.second), aux.second));
            continue;
        }

        if (it->first.first < y) {
            //! split left
            add_rect(aux.second, y, pos - 1, aux.first.second);
            to_add.pb(mp(mp(aux.first.first, y - 1), aux.second));
            continue;
        }

        if (it->first.second > yy) {
            //! split right
            add_rect(aux.second, aux.first.first, pos - 1, yy);
            to_add.pb(mp(mp(yy + 1, aux.first.second), aux.second));
            continue;
        }

        //! don't split
        add_rect(aux.second, aux.first.first, pos - 1, aux.first.second);
    }

    for (auto e : to_add)
        S.insert(e);

    for (auto e : to_rm)
        S.erase(e);

}

void add_now() {
    S.insert(mp(mp(y, yy), pos));
}

void build(int node, int l, int r, int bonus, vector<int>& leaves, bool from) {
    cnt++;

    if (l == r) {
        leaves.pb(bonus + node);
        return;
    }

    int mid = (l + r) >> 1;
    build(lSon, l, mid, bonus, leaves, from);
    build(rSon, mid + 1, r, bonus, leaves, from);

    if (from) {
        work.add_dir_edge(bonus + lSon, bonus + node, inf);
        work.add_dir_edge(bonus + rSon, bonus + node, inf);
    } else {
        work.add_dir_edge(bonus + node, bonus + lSon, inf);
        work.add_dir_edge(bonus + node, bonus + rSon, inf);
    }
}

void pre() {
    int i;

    work.init(maxN * 10 + 11, 1, 2);
    cnt_ln = cnt = 2;
    build(1, 1, n, cnt_ln, leaves_ln, true);

    cnt_co = cnt;
    build(1, 1, n, cnt_co, leaves_co, false);

    for (auto e : leaves_ln)
        work.add_dir_edge(1, e, 1);
    for (auto e : leaves_co)
        work.add_dir_edge(e, 2, 1);
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d%d", &x, &y, &xx, &yy);
        if (x > xx) swap(x, xx);
        if (y > yy) swap(y, yy);

        ord.pb(mp( mp(x, 1), mp(y, yy) ));
        ord.pb(mp( mp(xx + 1, -1), mp(y, yy) ));
    }

    ord.pb(mp( mp(n + 1, 1), mp(1, n) ));
    sort(ord.begin(), ord.end());
    S.insert(mp(mp(1, n), 1));

    pre();

    for (auto e : ord) {
        pos = e.first.first;
        op = e.first.second;
        y = e.second.first;
        yy = e.second.second;

        if (op == 1)
            remove_now();
        else
            add_now();
    }

    cout << work.run();


    return 0;
}
