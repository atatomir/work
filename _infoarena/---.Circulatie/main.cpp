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
Buffer fin("circulatie.in", 1 << 20);

int n, i, aux, x, y;
vector<int> list[maxN];
int l[maxN], r[maxN];
bool us[maxN];

bool pairUp(int node) {
    if(us[node]) return false;
    us[node] = true;

    for (auto to : list[node]) {
        if (r[to] == 0) {
            l[node] = to;
            r[to] = node;
            return true;
        }
    }

    for (auto to : list[node]) {
        if (pairUp(r[to])) {
            l[node] = to;
            r[to] = node;
            return true;
        }
    }

    return false;
}

int main()
{
    //freopen("circulatie.in","r",stdin);
    freopen("circulatie.out","w",stdout);

    fin >> n;
    aux = n * 3;
    for (i = 1; i <= aux; i++) {
        fin >> x >> y;
        list[x].pb(y);
    }

    bool need = true;
    while (need) {
        need = false;
        memset(us, 0, sizeof(us));

        for (i = 1; i <= n; i++)
            if (!l[i])
                need |= pairUp(i);
    }

    for (i = 1; i <= n; i++) {
        printf("%d %d -2\n", i, l[i]);

        bool all_go = false;
        for (auto to : list[i])
            if (l[i] != to || all_go)
                printf("%d %d 1\n", i, to);
            else
                all_go = true;
    }

    return 0;
}
