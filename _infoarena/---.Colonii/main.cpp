#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <map>
#include <bitset>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 5016

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 5);
            refill();
        }

        Buffer& operator>>(int &dest) {
            while (!is_digit(data[pos]))
                if (++pos == dim)
                    refill();
            dest = 0;
            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }

            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        bool is_digit(char c) {
            return '0' <= c && c <= '9';
        }

        void refill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }
};

int n, m, i, x, y, S;
vector<int> ini[maxN];
vector<int> list[maxN], from[maxN];
bool us[maxN], on_way[maxN];
queue<int> Q;
vector<int> order;

bitset<maxN> dep[maxN], full, aux;


void dfs(int node) {
    us[node] = true;
    on_way[node] = true;
    order.pb(node);

    for (int to : ini[node]) {
        if (!us[to]) dfs(to);
        if (!on_way[to])
            list[node].pb(to), from[to].pb(node);
    }

    on_way[node] = false;
}



int main()
{
    Buffer fin("colonii.in", 1 << 20);
    freopen("colonii.out","w",stdout);

    fin >> n >> m >> S;
    for (i = 1; i <= m; i++) {
        fin >> x >> y;
        ini[x].pb(y);
    }

    dfs(S);

    full.reset();
    for (i = 1; i <= n; i++) full[i] = 1;
    for (i = 1; i <= n; i++) dep[i] = i;
    dep[S].reset(); dep[S][S] = 1;

    bool need = true;
    while (need) {
        need = false;

        for (int node : order) {
            if (node == S) continue;

            aux = full;
            for (int to : from[node]) {
                aux &= dep[to];
            }

            aux[node] = 1;

            if (aux != dep[node]) {
                need = true;
                dep[node] = aux;
            }
        }
    }

    for (i = 1; i <= n; i++)
        printf("%d\n", dep[i].count() - 1);


    return 0;
}
