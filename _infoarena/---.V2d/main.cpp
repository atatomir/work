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

#define maxN 511

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

Buffer fin("v2d.in", 1 << 22);





short aux[maxN][maxN];

int n, i, j, t, q, pas;
short P[maxN][maxN], Pmax[maxN][maxN], help[maxN][maxN];

void read() {
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            fin >> P[i][j];
}

void reset() {
    memset(Pmax, 0, sizeof(Pmax));
}

void rot90_P() {
    memcpy(aux, P, sizeof(P));
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            P[n - j + 1][i] = aux[i][j];
}

void rot90_Pmax() {
    memcpy(aux, Pmax, sizeof(Pmax));
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            Pmax[n - j + 1][i] = aux[i][j];
}

void solve() {
    int i, j;

    memcpy(help, P, sizeof(help));
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            help[i][j] += i + j;

            Pmax[i][j] = max((int)Pmax[i][j], max( (int)help[i - 1][j], (int)help[i][j - 1]) - (i + j) );
            help[i][j] = max(help[i][j], max(help[i - 1][j], help[i][j - 1]));
        }
    }
}

void conclude(short day) {
    int i, j;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            P[i][j] = day + (1LL * P[i][j] + 1LL * (day - 1) * Pmax[i][j] ) % q;
}




int main()
{
    freopen("v2d.out","w",stdout);

    fin >> n >> t >> q;
    read();

    for (pas = 2; pas <= t + 1; pas++) {
        reset();

        solve();
        rot90_P(); rot90_Pmax();

        solve();
        rot90_P(); rot90_Pmax();

        solve();
        rot90_P(); rot90_Pmax();

        solve();
        //rot90_P(); rot90_Pmax();

        conclude(pas);
    }

    int ans = 0;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            ans = (ans + P[i][j]) % q;

    printf("%d", ans);
    cerr << ans;

    return 0;
}
