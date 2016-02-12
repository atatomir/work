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

#define maxN 555
#define maxM 111
#define base 10001

int n, m, i, j;
ll A[maxN][maxN];
ll B[maxN][maxN];
int ans;

ll small[maxM];
ll big[maxN];
bool good[maxM][maxN];

int pr[maxM], q;

void kmp(int line) {
    int i, j;

    memset(good[line], 0, sizeof(good[line]));

    pr[1] = q = 0;
    for (i = 2; i < m; i++) {
        while (q > 0 && small[q + 1] != small[i]) q = pr[q];
        if (small[q + 1] == small[i]) q++;
        pr[i] = q;
    }

    q = 0;
    for (i = 1; i < n; i++) {
        while (q > 0 && small[q + 1] != big[i]) q = pr[q];
        if (small[q + 1] == big[i]) q++;

        good[line][i] = (q == m - 1);
        if (good[line][i]) q = pr[q];
    }
}

void solve(int l1) {
    int l2 = l1 + m - 1;
    int i, j;

    for (i = l1 + 1; i <= l2; i++) {
        for (j = 2; j <= m; j++)
            small[j - 1] = B[i - l1 + 1][j];
        for (j = 2; j <= n; j++)
            big[j - 1] = A[i][j];

        kmp(i - l1);
    }

    for (i = 2; i < m; i++)
        for (j = 1; j < n; j++)
            good[i][j] &= good[i - 1][j];

    for (i = 1; i < n; i++)
        ans += good[m - 1][i];
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
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= m; j++) {
            scanf("%d", &B[i][j]);
            B[i][j] *= -1;
        }
    }

    if (m == 1) {
        printf("%d", n * n);
        cerr << n * n;
        return 0;
    }

    ll aux;
    for (i = n; i > 1; i--) {
        for (j = n; j > 1; j--) {
            aux = A[i][j] - A[i - 1][j - 1] + base;
            aux = (aux * base + (A[i][j] - A[i - 1][j] + base));
            aux = (aux * base + (A[i][j] - A[i][j - 1] + base));

            A[i][j] = aux;
        }
    }

    for (i = m; i > 1; i--) {
        for (j = m; j > 1; j--) {
            aux = B[i][j] - B[i - 1][j - 1] + base;
            aux = (aux * base + (B[i][j] - B[i - 1][j] + base));
            aux = (aux * base + (B[i][j] - B[i][j - 1] + base));

            B[i][j] = aux;
        }
    }

    for (i = 1; i + m - 1 <= n; i++)
        solve(i);

    printf("%d", ans);
    cerr << ans;

    return 0;
}
