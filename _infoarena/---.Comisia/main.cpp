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

#define maxN 200011
#define maxLog 19
#define inf 1000000000000000000LL

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

Buffer fin("comisia.in", 1 << 22);

int n, i, j, l, r;
ll sums[maxN];
int rmq[maxLog][maxN];
int help[maxN];
ll ans = inf;

int query(int l, int r) {
    int dim = (r - l + 1);
    int id = help[dim];

    return max(rmq[id][l], rmq[id][r - (1 << id) + 1]);
}

int main()
{
    //freopen("comisia.in","r",stdin);
    freopen("comisia.out","w",stdout);

    fin >> n;
    for (i = 1; i <= n; i++) fin >> rmq[0][i];
    for (i = 1; i <= n; i++) fin >> sums[i], sums[i] += sums[i - 1];


    help[1] = 0;
    for (i = 1; i <= n; i++) {
        help[i] = help[i - 1];
        if (i >= (1 << help[i]) << 1) help[i]++;
    }

    for (i = 1; i <= help[n]; i++) {
        int big_dim = (1 << i);
        int small_dim = big_dim >> 1;

        for (j = 1; j + big_dim - 1 <= n; j++)
            rmq[i][j] = max(rmq[i - 1][j], rmq[i - 1][j + small_dim]);
    }

    for (l = 1; l <= n; l++) {
        r = l;

        while (r <= n) {
            if (sums[r] - sums[l - 1] >= ans) break;

            int need = query(l, r);
            if (need <= r - l + 1) break;
            r = l + need - 1;
        }

        if (r <= n) ans = min(ans, sums[r] - sums[l - 1]);
    }

    printf("%lld", ans);

    return 0;
}
