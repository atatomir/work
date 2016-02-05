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
#define pii pair<int, int>

#define maxN 50011
#define maxM 200011

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            data.resize(_dim + 3);
            dim = _dim;
            refill();
        }

        template<typename T>
        Buffer& operator>>(T &ans) {
            while (!is_digit(data[pos])) {
                pos++;
                if (pos == dim) refill();
            }

            ans = 0;
            while (is_digit(data[pos])) {
                ans = ans * 10 + data[pos++] - '0';
                if (pos == dim) refill();
            }

            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        void refill() {
            memset(&data[0], 0, dim);
            pos = 0;
            fread(&data[0], 1, dim, stdin);
        }

        bool is_digit(char c) {
            return '0' <= c && c <= '9';
        }
};

//! ---------------------------------

class Forest {
    public:
        void init(int _n) {
            n = _n;
            dad.resize(n + 3);

            for (i = 1; i <= n; i++)
                dad[i] = i;
        }

        int Find(int x) {
            if (dad[x] == x) return x;
            dad[x] = Find(dad[x]);
            return dad[x];
        }

        bool Merge(int R1, int R2) {
            R1 = Find(R1);
            R2 = Find(R2);

            if (R1 == R2) return false;
            dad[R2] = R1;
            return true;
        }

    private:
        int n, i;
        vector<int> dad;
};

struct Edge {
    int x, y, cost;

    Edge() {}
    Edge(int _x, int _y, int _cost) {
        x = _x; y = _y; cost = _cost;
    }
};

//! ---------------------------------

int n, m, i, a, b, c, dim;
Edge Edges[maxM];
vector<int> list[maxN];

int comp[maxN];
int size_comp;
vector<int> help;

int bucket_size;
int pos, pos2;
bool us_edge[maxM];
bool rez_edge[maxM];

ll ans[maxM];

Forest work;

//! ---------------------------------

bool aux_cmp(int a , int b) {
    return Edges[a].cost < Edges[b].cost;
}

ll compute_tree(int lim) {
    int i;
    vector<int> aux;
    aux.clear();

    memset(us_edge, 0, sizeof(us_edge));

    for (i = 1; i <= lim; i++)
        aux.pb(i);
    sort(aux.begin(), aux.end(), aux_cmp);

    ll ans = 0;

    work.init(n);
    for (auto e : aux) {
        Edge now = Edges[e];
        if (work.Merge(now.x, now.y)) {
            ans += 1LL * now.cost;
            us_edge[e] = true;
        }
    }

    return ans;
}

void dfs(int node, int color) {
    comp[node] = color;

    for (auto to : list[node])
        if (comp[to] == 0)
            dfs(to, color);
}

ll solve_task(int bg, int en) {
    int i;
    vector<int> aux = help;
    ll ans = 0;

    for (i = bg; i <= en; i++)
        aux.pb(i);
    sort(aux.begin(), aux.end(), aux_cmp);

    work.init(size_comp);
    for (auto e : aux) {
        int xx = comp[ Edges[e].x ];
        int yy = comp[ Edges[e].y ];

        if (work.Merge(xx, yy))
            ans += Edges[e].cost;
    }

    return ans;
}

int main()
{
    Buffer fin("rutier.in", 1 << 20);
    //freopen("rutier.in","r",stdin);
    freopen("rutier.out","w",stdout);

    fin >> n;
    for (i = 2; i <= n; i++) {
        fin >> a >> c;
        Edges[++dim] = Edge(i, a, c);
    }

    fin >> m;
    for (i = 1; i <= m; i++) {
        fin >> a >> b >> c;
        Edges[++dim] = Edge(a, b, c);
    }

    bucket_size = sqrt(m);
    pos = n;

    m += n - 1;

    while (pos <= m) {
        if (pos == n)
            ans[pos] = compute_tree(pos);
        memcpy(rez_edge, us_edge, sizeof(rez_edge));

        pos2 = min(pos + bucket_size, m);
        ans[pos2] = compute_tree(pos2);

        //! compare results ans solve for pos + 1... pos2 - 1

        for (i = 1; i <= n; i++)
            list[i].clear();

        //! get stable edges
        ll all_cost = 0;
        for (i = 1; i <= m; i++) {
            if (us_edge[i] && rez_edge[i]) {
                //! this edge remains during these queries
                list[ Edges[i].x ].pb(Edges[i].y);
                list[ Edges[i].y ].pb(Edges[i].x);
                all_cost += 1LL * Edges[i].cost;
            }
        }

        //! get conex components
        memset(comp, 0, sizeof(comp));
        size_comp = 0;

        for (i = 1; i <= n; i++)
            if (comp[i] == 0)
                dfs(i, ++size_comp);

        //! solve tasks from pos + 1 .. pos2 - 1
        help.clear();
        for (i = 1; i <= m; i++)
            if (rez_edge[i] == true && us_edge[i] == false)
                help.pb(i);

        for (i = pos + 1; i < pos2; i++)
            ans[i] += solve_task(pos + 1, i) + all_cost;

        pos = pos2;

        if (pos == m) break;
    }

    for (i = n; i <= m; i++)
        printf("%lld\n", ans[i]);

    return 0;
}
