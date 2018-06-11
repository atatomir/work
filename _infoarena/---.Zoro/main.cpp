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
#define inf 1000000000

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
        vector<char> data;
        int pos, dim;

        bool is_digit(char c) {
            return '0' <= c && c <= '9';
        }

        void refill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }
};

int n, m, i, j;
int mat[maxN][maxN];
pair<int, int> wh[maxN * maxN];
int nxt_l[maxN][maxN], nxt_c[maxN][maxN];
int dp[maxN][maxN];


void pre_line(int id) {
    int i;
    vector< pair<int, int> > aux = {};

    for (i = 1; i <= m; i++) aux.pb(mp(mat[id][i], i));
    sort(aux.begin(), aux.end());

    for (i = 1; i < aux.size(); i++)
        nxt_l[id][aux[i].second] = aux[i - 1].second;
}

void pre_column(int id) {
    int i;
    vector< pair<int, int> > aux = {};

    for (i = 1; i <= n; i++) aux.pb(mp(mat[i][id], i));
    sort(aux.begin(), aux.end());

    for (i = 1; i < aux.size(); i++)
        nxt_c[aux[i].second][id] = aux[i - 1].second;
}

void solve(int x, int y) {
    int i, xx, yy;

    if (dp[x][y] < 0) return;

    int id_l = nxt_l[x][y];
    if (id_l != 0) dp[x][id_l] = max(dp[x][id_l], dp[x][y] + 1);

    int id_c = nxt_c[x][y];
    if (id_c != 0) dp[id_c][y] = max(dp[id_c][y], dp[x][y] + 1);
}

int main()
{
    Buffer fin("zoro.in", 1 << 20);
    freopen("zoro.out","w",stdout);

    fin >> n >> m;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            fin >> mat[i][j];
            wh[mat[i][j]] = mp(i, j);
            dp[i][j] = -inf;
        }
    }

    for (i = 0; i <= n; i++)
        mat[i][0] = mat[i][m + 1] = inf;

    for (i = 0; i <= m; i++)
        mat[0][i] = mat[n + 1][i] = inf;

    for (i = 1; i <= n; i++) pre_line(i);
    for (i = 1; i <= m; i++) pre_column(i);

    dp[1][1] = 1;
    for (i = n * m; i > 0; i--)
        solve(wh[i].first, wh[i].second);

    printf("%d", dp[n][m]);

    return 0;
}
