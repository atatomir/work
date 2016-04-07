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

#define maxN 50048

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 5);
            refill();
        }

        template<typename T>
        Buffer& operator>>(T &dest) {
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

Buffer fin("landscape.in", 1 << 22);


int n, i, j, last;
ll x, y, z, val, val2;
ll v[maxN];
vector<ll> mn, pl;

ll best, pos;
ll ans;

int main()
{
    //freopen("landscape.in","r",stdin);
    freopen("landscape.out","w",stdout);

    mn.pb(-1);
    pl.pb(-1);

    fin >> n >> x >> y >> z;
    for (i = 1; i <= n; i++) {
        fin >> val >> val2;
        v[i] = val - val2;

        while (v[i] > 0) {
            pl.pb(i);
            v[i]--;
        }

        while (v[i] < 0) {
            mn.pb(i);
            v[i]++;
        }
    }

    last = 0;
    for (i = 1; i < mn.size(); i++) {
        best = x + y * (pl.size() - 1 - last);
        pos = last;

        for (j = last + 1; j < pl.size(); j++) {
            ll aux = z * abs(mn[i] - pl[j]) + y * (j - last - 1) + y * (pl.size() - 1 - j);
            if (aux > best) break;
            best = aux;
            pos = j;
        }

        ans += best - y * (pl.size() - 1 - pos);
        last = pos;
    }

    printf("%lld", ans + y * (pl.size() - 1 - last));


    return 0;
}
