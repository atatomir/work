#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 211

bool aux[maxN][maxN];
bool aux2[maxN][maxN];

struct Matrix {
    int n;
    bool data[maxN][maxN];

    void init(int _n) {
        n = _n;
        memset(data, 0, sizeof(data));
    }

    void operator*=(const Matrix& who) {
        memcpy(aux, data, sizeof(data));
        memcpy(aux2, who.data, sizeof(who.data));

        int i, j, k;

        init(n);
        for (k = 1; k <= n; k++)
            for (i = 1; i <= n; i++)
                for (j = 1; j <= n; j++)
                    data[i][j] |= aux[i][k] & aux2[k][j];
    }
};

int n, m, i, j, k, x, y;
int risc[maxN];
int ans[maxN];

Matrix ini;
Matrix use;

int main()
{
    freopen("steinsgate.in","r",stdin);
    freopen("steinsgate.out","w",stdout);

    scanf("%d%d%d", &n, &m, &k);

    ini.init(n);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        ini.data[x][y] = true;
    }
    for (i = 1; i <= n; i++)
        scanf("%d", &risc[i]);

    use = ini;

    k--;
    while (k) {
        if (k & 1) ini *= use;
        k >>= 1;
        use *= use;
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (ini.data[i][j])
                ans[j] = max(ans[j], risc[i]);

    for (i = 1; i <= n; i++)
        printf("%d ", ans[i]);

    return 0;
}
