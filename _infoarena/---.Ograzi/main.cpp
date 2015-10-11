#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back

#define def 1000000

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
Buffer fin("ograzi.in", 1 << 20);

int W, H;

#define mod 37139
class Hash {
    public:
        void init() {
            for (i = 0; i < mod; i++)
                data[i].clear();
        }

        void add(int x, int y, pair<int, int> who) {
            int key = getKey(x, y);
            data[key].pb(who);
        }

        pair<int, int> get(int x, int y) {
            int key = getKey(x, y);
            for (auto who : data[key])
                if (who.first / W == x && who.second / H == y)
                    return who;

            return mp(- def - 1000005, - def - 1000005);
        }

    private:
        vector< pair<int, int> > data[mod];
        int i;

        int getKey(int x, int y) {
            return (x * 17 + y) % mod;
        }
};


int n, m, i, x, y;
Hash work;
int ans;

bool isIn(int xx, int yy, int x, int y) {
    if (xx <= x && xx + W >= x)
        if (yy <= y && yy + H >= y)
            return true;
    return false;
}

bool test_point(int x, int y) {
    int xx = x / W;
    int yy = y / H;

    auto aux = work.get(xx, yy);
    if (isIn(aux.first, aux.second, x, y)) return true;

    /**/ aux = work.get(xx - 1, yy);
    if (isIn(aux.first, aux.second, x, y)) return true;

    /**/ aux = work.get(xx - 1, yy - 1);
    if (isIn(aux.first, aux.second, x, y)) return true;

    /**/ aux = work.get(xx, yy - 1);
    if (isIn(aux.first, aux.second, x, y)) return true;

    return false;
}

int main()
{
    //freopen("ograzi.in","r",stdin);
    freopen("ograzi.out","w",stdout);

    work.init();

    fin >> n >> m >> W >> H;
    for (i = 1; i <= n; i++) {
        fin >> x >> y;
        x += def; y += def;
        work.add(x / W, y / H, mp(x, y));
    }

    for (i = 1; i <= m; i++) {
        fin >> x >> y;
        x += def; y += def;
        if (test_point(x, y)) ans++;
    }

    printf("%d", ans);

    return 0;
}
