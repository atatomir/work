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

#define maxN 40011
#define maxM 100011

class Buffer {
    public:
        Buffer(int _dim) {
            //freopen("test.in", "r", stdin);
            dim = _dim;
            data.resize(dim + 11);
            refill();
        }

        Buffer& operator>>(int &dest) {
            while (!is_digit(data[pos]) && data[pos] != '-')
                if (++pos == dim)
                    refill();

            dest = 0;
            int sgn = 1;

            if (data[pos] == '-') {
                sgn = -1;
                if (++pos == dim)
                    refill();
            }

            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }

            dest *= sgn;

            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        bool is_digit(char c) {
            return '0' <= c && c <= '9';
        }

        void refill() {
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
            pos = 0;
        }
};

struct query {
    int x, y;
    int id;
};

const int dim = 200;

int n, m, i, x, y;
int v[maxN], lvl[maxN], dad[maxN];
vector<int> ord;
vector<int> list[maxN];

int min_down[maxN], max_up[maxN];
vector<int> centers;

int assigned[maxN];
vector<int> way, way2;

vector<query> Q[maxN];
query aux;
vector<query> to_solve[maxN];

int actual_center;

bool on_way[maxN];
int cnt[maxN];
int ans;

vector< pair<int, int> > to_do;
int sol[maxM];


void get_centers(int node, int root) {
    min_down[node] = n + 1;
    max_up[node] = dim;

    for (auto to : list[node]) {
        if (to == root) continue;

        lvl[to] = lvl[node] + 1;
        dad[to] = node;
        get_centers(to, node);

        min_down[node] = min(min_down[node], min_down[to] + 1);
        max_up[node] = min(max_up[node], max_up[to] - 1);
    }

    if (max_up[node] >= min_down[node]) {
        max_up[node] = n + 1;
    }

    if (max_up[node] == 0) {
        centers.pb(node);
        min_down[node] = 0;
        max_up[node] = n + 1;
    }
}

void get_nodes(int node, int root, int cnt, int id) {
    assigned[node] = id;
    if (cnt == 0) return;

    for (auto to : list[node])
        if (to != root)
            get_nodes(to, node, cnt - 1, id);
}

void get_way(int x, int y) {
    way = {x};
    way2 = {y};

    while (lvl[x] > lvl[y]) {
        x = dad[x];
        way.pb(x);
    }

    while (lvl[x] < lvl[y]) {
        y = dad[y];
        way2.pb(y);
    }

    while (x != y) {
        x = dad[x];
        y = dad[y];
        way.pb(x);
        way2.pb(y);
    }

    for (int i = way2.size() - 2; i >= 0; i--) way.pb(way2[i]);
}

inline void add_value(int x) {
    if (++cnt[x] == 1) ans++;
}

inline void rm_value(int x) {
    if (--cnt[x] == 0) ans--;
}

void solve_query(query act) {
    get_way(act.x, actual_center);
    to_do.clear();

    bool first = true;
    for (auto e : way) {
        if (on_way[e] == false) {
            to_do.pb(mp(v[e], -1));
            add_value(v[e]);
        } else {
            if (first) {
                first = false;
                continue;
            }

            to_do.pb(mp(v[e], +1));
            rm_value(v[e]);
        }
    }

    sol[act.id] = ans;

    for (auto e : to_do) {
        if (e.second == -1)
            rm_value(e.first);
        else
            add_value(e.first);
    }

}

void solve(int node, int root) {
    on_way[node] = true;
    add_value(v[node]);

    for (auto to : list[node])
        if (to != root)
            solve(to, node);

    for (auto e : to_solve[node])
        solve_query(e);

    to_solve[node].clear();

    rm_value(v[node]);
    on_way[node] = false;
}

int main()
{
    Buffer fin(1 << 20);

    fin >> n >> m;
    for (i = 1; i <= n; i++) fin >> v[i], ord.pb(v[i]);
    for (i = 1; i < n; i++) {
        fin >> x >> y;
        list[x].pb(y);
        list[y].pb(x);
    }

    sort(ord.begin(), ord.end());
    ord.resize(unique(ord.begin(), ord.end()) - ord.begin());

    for (i = 1; i <= n; i++) v[i] = lower_bound(ord.begin(), ord.end(), v[i]) - ord.begin();
    get_centers(1, 0);
    if (max_up[1] <= n) centers.pb(1);

    for (auto e : centers)
        get_nodes(e, 0, dim, e);

    for (i = 1; i <= m; i++) {
        fin >> aux.x >> aux.y;
        aux.id = i;
        Q[ assigned[aux.x] ].pb(aux);
    }

    for (auto e : centers) {
        if (Q[e].empty()) continue;
        actual_center = e;

        for (auto qq : Q[e])
            to_solve[qq.y].pb(qq);

        solve(actual_center, 0);
    }

    for (i = 1; i <= n; i++)
        if (assigned[i] == 0)
            cerr << 5 / 0;


    for (i = 1; i <= m; i++) {
        //if (sol[i] == 0) while(1);
        printf("%d\n", sol[i]);
    }


    return 0;
}
