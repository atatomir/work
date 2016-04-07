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


int n, i, j;
ll x, y, z, val, val2;
ll v[maxN];

int ss, dd;
vector<ll> mn, pl;
ll dp[2][maxN];

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

    ss = 0;
    dd = 1;

    dp[ss][0] = 0;
    for (i = 1; i < pl.size(); i++) dp[ss][i] = y * i;

    for (i = 1; i < mn.size(); i++) {
        dp[dd][0] = x * i;

        for (j = 1; j < pl.size(); j++) {
            dp[dd][j] = min(dp[ss][j] + x, dp[dd][j - 1] + y);
            dp[dd][j] = min(dp[ss][j - 1] + z * abs(mn[i] - pl[j]), dp[dd][j]);

            cerr << dp[dd][j] << ' ';
        }
        cerr << '\n';

        swap(ss, dd);
    }

    printf("%lld", dp[ss][pl.size() - 1]);


    return 0;
}
