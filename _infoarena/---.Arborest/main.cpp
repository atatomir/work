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

class Buffer {
    public:
        Buffer(int _dim, string file) {
            dim = _dim;
            data.resize(dim);
            freopen(file.c_str(), "r", stdin);
            reFill();
        }

        Buffer& operator>>(int &dest) {
            while (!isDigit(data[pos])) {
                if (++pos == dim) reFill();
            }
            dest = 0;
            while (isDigit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim) reFill();
            }
            return *this;
        }

    private:
        vector<char> data;
        int dim,pos;

        bool isDigit(char c) {
            return ('0' <= c) && (c <= '9');
        }
        void reFill() {
            memset(&data[0], 0, sizeof(data));
            fread(&data[0], 1, dim, stdin);
            pos = 0;
        }
};

int n, i, k, dad;
vector<int> list[maxN];
int lvl[maxN];
int count_changes;
int lim_level;

void dfs(int node) {
    lvl[node] = 1;
    for (auto neigh : list[node]) {
        dfs(neigh);
        lvl[node] = max(lvl[node], lvl[neigh] + 1);
    }

    if (lvl[node] == lim_level - 1) {
        lvl[node] = 0;
        count_changes++;
    }
}

bool try_height(int lim) {
    count_changes = 0;
    lim_level = lim;

    for (auto neigh : list[1]) {
        dfs(neigh);
        if (lvl[neigh] == 0) count_changes--;
    }

    return count_changes <= k;
}

int main()
{
    Buffer fin(1 << 20, "arborest.in");
    freopen("arborest.out","w",stdout);

    fin >> n >> k;
    for (i = 2; i <= n; i++) {
        fin >> dad;
        list[dad].pb(i);
    }

    if (n == 1) {
        printf("0");
        return 0;
    }
    if (n - 1 - list[1].size() <= k) {
        printf("1");
        return 0;
    }

    try_height(n+10);
    int lim = lvl[ list[1][0] ] + 1;
    for (auto e : list[1]) lim = max(lim, lvl[e] + 1);

    int ans = 1;
    int step = 1;
    while (2 * step <= lim) step <<= 1;

    for (; step > 0; step >>= 1) {
        int aux = ans + step;
        if (!try_height(aux + 1)) ans = aux;
    }

    printf("%d", ans + 1);

    return 0;
}
