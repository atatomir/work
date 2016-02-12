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

#define maxN 611
#define base 30007LL
#define mod 1000000007LL

int n, m, i, j, dim, sz;
int A[maxN][maxN];
ll work[maxN][maxN];
ll dest[maxN][maxN];

void compute() {
    int i, j;

    for (i = dim; i > 1; i--) {
        for (j = dim; j > 1; j--) {
            work[i][j] = (mod + A[i][j] - (A[i - 1][j - 1])% mod ) % mod;
            work[i][j] = (work[i][j] * base + mod + A[i][j] - (A[i - 1][j])% mod ) % mod;
            work[i][j] = (work[i][j] * base + mod + A[i][j] - (A[i][j - 1])% mod ) % mod;
        }
    }

    /*for (i = 1; i <= dim; i++) {
        for (j = 1; j <= dim; j++)
            cerr << work[i][j] << ' ';
        cerr << '\n';
    }
    cerr << '\n';*/

    for (i = 1; i <= dim; i++) {
        ll act = 0;
        ll poww = 1;

        for (j = 1; j < sz; j++) {
            act = (act * base * work[i][j]) % mod;
            poww = (poww * base) % mod;
        }

        for (j = sz; j <= dim; j++) {
            act = (act + mod - (poww * work[i][j - sz]) % mod) % mod;
            act = (act * base + work[i][j]) % mod;

            dest[i][j] = act;
        }
    }

    /*for (i = 1; i <= dim; i++) {
        for (j = 1; j <= dim; j++)
            cerr << dest[i][j] << ' ';
        cerr << '\n';
    }
    cerr << '\n';*/

    memcpy(work, dest, sizeof(work));
    for (j = 1; j <= dim; j++) {
        ll act = 0;
        ll poww = 1;

        for (i = 1; i < sz; i++) {
            act = (act * base * work[i][j]) % mod;
            poww = (poww * base) % mod;
        }

        for (i = sz; i <= dim; i++) {
            act = (act + mod - (poww * work[i - sz][j]) % mod) % mod;
            act = (act * base + work[i][j]) % mod;

            dest[i][j] = act;
        }
    }

    /*for (i = 1; i <= dim; i++) {
        for (j = 1; j <= dim; j++)
            cerr << dest[i][j] << ' ';
        cerr << '\n';
    }
    cerr << '\n';*/
}

int main()
{
    freopen("tetris2.in","r",stdin);
    freopen("tetris2.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &A[i][j]);

    scanf("%d", &m);
    for (i = 1; i <= m; i++)
        for (j = 1; j <= m; j++) {
            scanf("%d", &A[i][j + n]);
            A[i][j + n] *= -1;
        }

    if (m == 1) {
        printf("%d", n * n);
        return 0;
    }

    dim = n + m;
    sz = m - 1;
    compute();

    ll target = dest[m][n + m];
    int ans = 0;

    for (i = m; i <= n; i++)
        for (j = m; j <= n; j++)
            if (dest[i][j] == target)
                ans++;

    printf("%d", ans);
    cerr << ans;

    return 0;
}
