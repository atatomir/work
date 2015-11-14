#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define pb push_back
#define mp make_pair

#define def 100005
#define maxN def + 11
#define maxLog 21

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim);

            reFill();
        }

        Buffer& operator>>(int &who) {
            while (!isDigit(data[pos]))
                if (++pos == dim) reFill();
            who = 0;
            while (isDigit(data[pos])) {
                who = who * 10 + data[pos] - '0';
                if (++pos == dim) reFill();
            }
            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        bool isDigit(char c) {
            return ('0' <= c && c <= '9');
        }

        void reFill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }
};

Buffer fin("viteza.in", 1 << 20);

int n, m, i, x, y;
vector<int> list[maxN];
bool us[maxN];
int dad[maxLog][maxN];
int lvl[maxN];
int vals[maxN];
int query[maxN];

vector<int> to_do[maxN];

int lim = def;
int aib[maxN];
int ans[maxN];

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void add(int x, int v) {
    while (x <= lim) {
        aib[x] += v;
        x += zrs(x);
    }
}

int sum(int x) {
    int ans = 0;
    while (x > 0) {
        ans += aib[x];
        x -= zrs(x);
    }
    return ans;
}

void dfs(int node) {
    us[node] = true;

    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i];

        if (us[to]) continue;

        dad[0][to] = node;
        lvl[to] = lvl[node] + 1;
        dfs(to);
    }
}

void lca_preprocess() {
    for (int actLog = 1; actLog < maxLog; actLog++)
        for (int i = 1; i <= n; i++)
            dad[actLog][i] = dad[actLog - 1][ dad[actLog - 1][i] ];
}

void goUp(int& x, int how) {
    for (int i = 0; how > 0; i++) {
        if (how & 1) x = dad[i][x];
        how >>= 1;
    }
}

int getLca(int x, int y) {
    if (lvl[x] > lvl[y]) swap(x, y);
    goUp(y, lvl[y] - lvl[x]);

    if (x == y) return x;

    for (int actLog = maxLog - 1; actLog >= 0; actLog--) {
        if (dad[actLog][x] != dad[actLog][y]) {
            x = dad[actLog][x];
            y = dad[actLog][y];
        }
    }

    return dad[0][x];
}

void dfs_solve(int node) {
    us[node] = true;

    add(vals[node], +1);

    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i];

        if (us[to]) continue;
        dfs_solve(to);
    }

    for (int i = 0; i < to_do[node].size(); i++) {
        int id = to_do[node][i];
        int k;

        if (id > 0) {
            k = query[id];
            ans[id] += sum(k);
        } else {
            k = query[-id];
            ans[-id] -= sum(k);
        }
    }

    add(vals[node], -1);
}

int main()
{
    //freopen("viteza.in", "r", stdin);
    freopen("viteza.out", "w", stdout);

    fin >> n >> m;
    for (i = 1; i < n; i++) {
        fin >> x >> y;
        list[x].pb(y);
        list[y].pb(x);
    }

    dfs(1);
    lca_preprocess();

    for (i = 1; i <= n; i++) {
        fin >> vals[i];
        vals[i]++;
    }
    for (i = 1; i <= m; i++) {
        fin >> x >> y >> query[i];
        query[i]++;

        int lca = getLca(x, y);
        to_do[x].pb(i);
        to_do[y].pb(i);
        to_do[lca].pb(-i);
        to_do[ dad[0][lca] ].pb(-i);
    }


    memset(us, 0, sizeof(us));
    dfs_solve(1);

    for (i = 1; i <= m; i++) printf("%d\n", ans[i]);

    return 0;
}
