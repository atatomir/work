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

#define maxN 100011
#define maxLog 20

#define base 31
#define mod 1000000007

int n, q, i, j, x, y;
char c[maxN];

int dad[maxLog][maxN];
ll hsh[maxLog][maxN];

ll pre[maxLog + 11];

void solve(int &a, int &b) {
    for (int i = maxLog - 1; i >= 0; i--) {
        if (hsh[i][a] == hsh[i][b]) {
            a = dad[i][a];
            b = dad[i][b];
            if (a == b) return;
        }
    }
}

int main()
{
    freopen("aiacupalindroame.in","r",stdin);
    freopen("aiacupalindroame.out","w",stdout);

    scanf("%d%d", &n, &q);
    for (i = 2; i <= n; i++) scanf("%d", &dad[0][i]);
    scanf("\n%s", c + 2);
    for (i = 2; i <= n; i++) hsh[0][i] = c[i] - 'a' + 1;

    pre[0] = base;
    for (i = 1; i < maxLog; i++) pre[i] = (pre[i - 1] * pre[i - 1]) % mod;


    for (i = 1; i < maxLog; i++) {
        for (j = 1; j <= n; j++) {
            dad[i][j] = dad[i - 1][ dad[i - 1][j] ];
            hsh[i][j] = (hsh[i - 1][j] + pre[i - 1] * hsh[i - 1][ dad[i - 1][j] ]) % mod;
        }
    }

    for (i = 1; i <= q; i++) {
        scanf("%d%d", &x, &y);
        solve(x, y);

        if (x == y)
            printf("1\n");
        else
            printf("0\n");
    }

    return 0;
}
