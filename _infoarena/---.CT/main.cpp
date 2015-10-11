#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011
#define maxK maxN
#define maxLog 18

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim);
            reFill();
        }

        Buffer& operator>>(int &dest) {
            while (!isDigit(data[pos])) {
                if (++pos == dim) reFill();
            }
            dest = 0;
            while(isDigit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim) reFill();
            }
            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        void reFill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }
        bool isDigit(char c) {
            return ('0' <= c) && (c <= '9');
        }
};

Buffer fin("ct.in", 1 << 20);

int n, k, x, y, i, t;
vector<int> list[maxN];
bool us[maxN];
int dad[maxLog][maxN];
int lvl[maxN];
vector< pair<int, int> > lcas;
vector<int> bounds[maxN];
bool invalid[maxN];
int lca_info[maxN];
bool us_kill[maxN];

int best;

void init_all() {
    for (int i = 1; i <= n; i++) list[i].clear();
    memset(us, 0, sizeof(us));
    memset(dad, 0, sizeof(dad));
    memset(lvl, 0, sizeof(lvl));
    lcas.clear();
    for (int i = 1; i <= n; i++) bounds[i].clear();
    memset(invalid, 0, sizeof(invalid));
    memset(us_kill, 0, sizeof(us_kill));
    best = 0;
}

void dfs_ini(int node) {
    us[node] = true;

    for (int i = 0; i < list[node].size(); i++) {
        if (us[list[node][i]]) {
            list[node][i] = list[node][ list[node].size() - 1 ];
            list[node].pop_back();
            i--;
            continue;
        }

        int who = list[node][i];
        lvl[who] = lvl[node] + 1;
        dad[0][who] = node;
        dfs_ini(who);
    }
}

void make_smen_lca() {
    for (int actLog = 1; actLog < maxLog; actLog++)
        for (int i = 1; i <= n; i++)
            dad[actLog][i] = dad[actLog - 1][ dad[actLog - 1][i] ];
}

void goUp(int &x, int how) {
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

void dfs_kill(int node) {
    us_kill[node] = true;

    for (auto to : list[node])
        if (!us_kill[to]) dfs_kill(to);

    for (auto destroyed : bounds[node])
        invalid[destroyed] = true;
}

int main()
{
    //freopen("ct.in","r",stdin);
    freopen("ct.out","w",stdout);

    for (fin >> t; t > 0; t--) {
        fin >> n >> k;
        init_all();

        for (i = 1; i < n; i++) {
            fin >> x >> y;
            list[x].pb(y);
            list[y].pb(x);
        }

        dfs_ini(1);
        make_smen_lca();

        for (i = 1; i <= k; i++) {
            fin >> x >> y;
            int lca = getLca(x, y);

            lcas.pb(mp(lvl[lca], i));
            bounds[x].pb(i);
            bounds[y].pb(i);
            lca_info[i] = lca;
        }

        sort(lcas.begin(), lcas.end());

        for (i = lcas.size() - 1; i >= 0; i--) {
            int who = lca_info[ lcas[i].second ];
            int id = lcas[i].second;

            if (invalid[id]) continue;
            best++;

            dfs_kill(who);
        }

        printf("%d\n", best);
    }


    return 0;
}
