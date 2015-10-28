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

#define maxN 1000011
#define mod 666013

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1000011
#define mod 666013

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
Buffer fin("harta2.in", 1 << 20);

struct hash_struct {
    size_t operator()(const pair<int, int>& who )const {
        return (who.first * 17 + who.second) % mod;
    }
};

const int defX[8] = {0, 0, -1, 1, -1, 1, -1, 1};
const int defY[8] = {-1, 1, 0, 0, -1, 1, 1, -1};

int n, i;
int Px[maxN], Py[maxN];
unordered_map< pair<int, int>, int, hash_struct > M;
int _dim;

bool intersect(int id1, int id2) {
    if (Px[id1] > Px[id2]) swap(id1, id2);
    if (Px[id1] + _dim <= Px[id2]) return false;

    if (Py[id1] > Py[id2]) swap(id1, id2);
    if (Py[id1] + _dim <= Py[id2]) return false;

    return true;
}

bool check(int dim) {
    M.clear();
    _dim = dim;

    for (int i = 1; i <= n; i++) {
        int xx = Px[i] / dim;
        int yy = Py[i] / dim;

        if (M.count(mp(xx, yy)) != 0) return false;
        M[mp(xx, yy)] = i;

        for (int j = 0; j < 8; j++) {
            int _xx = xx + defX[j];
            int _yy = yy + defY[j];

            if (_xx < 0 || _yy < 0) continue;
            if (M.count(mp(_xx, _yy)) == 0) continue;

            if (intersect(i, M[mp(_xx, _yy)])) return false;
        }
    }

    return true;
}

int main()
{
    //freopen("harta2.in","r",stdin);
    freopen("harta2.out","w",stdout);

    fin >> n;
    for (i = 1; i <= n; i++) {
        fin >> Px[i] >> Py[i];
        Py[i] *= 3;
    }

    int l = 1;
    int r = 1000000;
    int mid;

    while (l <= r) {
        mid = (l + r) / 2;
        if (check(mid))
            l = mid + 1;
        else
            r = mid - 1;
    }

    printf("%.3lf", r / 3.00);


    return 0;
}
