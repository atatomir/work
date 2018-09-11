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

#define lSon (node << 1)
#define rSon (lSon | 1)

class Buffer {
    public:
        Buffer(string name, int _dim) {
            if (name != "")
                freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 11);
            refill();
        }

        template<typename T>
        Buffer& operator>>(T &dest) {
            T sign = +1;
            dest = 0;

            while (!is_digit(data[pos]) && data[pos] != '-')
                if (++pos == dim)
                    refill();

            if (data[pos] == '-') {
                sign = -1;
                if (++pos == dim)
                    refill();
            }

            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }

            dest *= sign;
            return *this;
        }


    private:
        int pos, dim;
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

const int maxN = 100011;
const double inf = 1e30;

struct elem {
    vector<double> add, best;
    int dim;

    void init() {
        dim = 1;
        add = best = {-inf, 0};
        return;
    }

    void expand() {
        add.pb(0);
        best.pb(max(0, (int)best.back()));
        dim++;
    }

    void upd(int pos, double v) {
        if (pos == 0) return;
        add[pos] += v;
    }

    void upd_fixed(int pos, double v) {
        if (pos == 0) return;
        upd(pos, v);
        upd(pos - 1, -v);
    }

    double que() {
        return best.back();
    }

    void recompute(int sz) {
        int i;

        sz = min(sz, (int)add.size() - 1);
        for (i = sz - 1; i >= 0; i--) {
            best[dim - i] = max(best[dim - i - 1] + add[dim - i],
                                add[dim - i]);
        }
    }
};

int n, i, x, cnt;
double here[maxN], cost;
vector<int> list[maxN];

elem work[maxN];
int id[maxN];
bool found;


void combine(int src, int dest) {
    int i;

    for (i = 1; i < work[src].dim; i++)
        work[src].add[ work[src].dim - i] +=  work[src].add[ work[src].dim - i + 1];

    work[dest].upd( work[dest].dim - work[src].dim, work[src].add[1] + cost * work[src].dim );

    for (i = 0; i < work[src].dim; i++)
        work[dest].upd_fixed( work[dest].dim - i, work[src].add[work[src].dim - i] + cost * (i + 1) );

    work[dest].recompute(work[src].dim + 3);

}

void dfs(int node, int root) {
    if (list[node].empty()) {
        id[node] = ++cnt;
        work[id[node]].init();
        work[id[node]].upd(1, here[node] - cost);
        return;
    }

    pair<int, int> best = mp(0, 0);
    for (auto to : list[node]) {
        dfs(to, node);
        best = max(best, mp( work[id[to]].dim, to ));

        if (found) return;
    }

    id[node] = id[best.second];
    for (auto to : list[node]) {
        if (to == best.second) continue;
        combine(id[to], id[node]);
    }

    work[id[node]].expand();
    work[id[node]].upd( work[id[node]].dim, here[node] - cost);

    work[id[node]].recompute(3);

    found |= (work[id[node]].que() >= 0.00);
}

bool check(double _cost) {
    int i;

    cost = _cost;
    cnt = 0;
    found = false;

    dfs(1, 0);
    return found;
}

int main()
{
    Buffer fin("craciun.in", 1 << 20);
    freopen("craciun.out","w",stdout);

    fin >> n;
    for (i = 1; i <= n; i++) {
        fin >> x;
        here[i] = x;
    }
    for (i = 2; i <= n; i++) {
        fin >> x;
        list[x].pb(i);
    }

    double le = 0.00;
    double ri = 1000000.00 * 100000.00;
    int steps = 60;

    for (i = 1; i <= n; i++) le = max(le, here[i]);

    while (steps--) {
        double mid = (le + ri) / 2.00;
        if (check(mid))
            le = mid;
        else
            ri = mid;
    }

    printf("%.10f", le);


    return 0;
}
