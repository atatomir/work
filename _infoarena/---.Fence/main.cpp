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

#define maxN 1024

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 11);
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
            fread(&data[0], 1 , dim, stdin);
        }
};


int n, m, i, j, val, op;
int north, south, east, west;
int v[maxN][maxN];

int xx1, yy1, xx2, yy2;
int must;

int aux_n, aux_m;
int aux[maxN][maxN];
int help[maxN][maxN];
int dp[maxN][maxN];

void get_from(int x1, int y1, int x2, int y2) {
    int i, j;

    for (i = x1; i <= x2; i++)
        for (j = y1; j <= y2; j++)
            aux[i - x1 + 1][j - y1 + 1] = v[i][j];

    aux_n = x2 - x1 + 1;
    aux_m = y2 - y1 + 1;
}

void rotate_once() {
    int i, j;

    memcpy(help, aux, sizeof(help));
    for (i = 1; i <= aux_n; i++)
        for (j = 1; j <= aux_m; j++)
            aux[aux_m - j + 1][i] = help[i][j];

    swap(aux_n, aux_m);
}

int solve() {
    int i, j;
    int best = 0;

    for (j = 1; j <= aux_m; j++) {
        dp[aux_n][j] = aux[aux_n][j];
        for (i = aux_n - 1; i > 0; i--) dp[i][j] = aux[i][j] + dp[i + 1][j];

        dp[1][j] += dp[1][j - 1];
        for (i = 2; i <= aux_n; i++) dp[i][j] = max(dp[i - 1][j], dp[i][j] + dp[i][j - 1]);

        for (i = 1; i <= aux_n; i++)
            best = max(best, dp[i][j]);
    }

    return best;
}

int main()
{
    //freopen("fence.in","r",stdin);
    Buffer fin("fence.in", 1 << 20);
    freopen("fence.out","w",stdout);

    fin >> op;
    fin >> n >> m >> val >> north >> south >> west >> east;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            fin >> v[i][j], v[i][j] -= val;

    if (north > south) {
        for (i = 1; i <= n; i++)
            for (j = 1; 2 * j <= m; j++)
                swap(v[i][j], v[i][m - j + 1]);

        north = m - north + 1;
        south = m - south + 1;

        swap(east, west);
    }

    xx1 = min(west, east);
    xx2 = max(west, east);

    yy1 = min(north, south);
    yy2 = max(north, south);

    for (i = xx1; i <= xx2; i++)
        for (j = yy1; j <= yy2; j++)
            must += v[i][j];

    for (i = 1; i < xx1; i++) must += v[i][north];
    for (i = 1; i < yy1; i++) must += v[west][i];
    for (i = yy2 + 1; i <= m; i++) must += v[east][i];
    for (i = xx2 + 1; i <= n; i++) must += v[i][south];

    if (op == 1) {
        printf("%d", must);
        return 0;
    }

    get_from(1, north + 1, east - 1, m);
    must += solve();

    get_from(east + 1, south + 1, n, m);
    rotate_once();
    must += solve();

    get_from(west + 1, 1, n, south - 1);
    rotate_once();
    rotate_once();
    must += solve();

    get_from(1, 1, west - 1, north - 1);
    rotate_once();
    rotate_once();
    rotate_once();
    must += solve();

    printf("%d", must);

    return 0;
}
