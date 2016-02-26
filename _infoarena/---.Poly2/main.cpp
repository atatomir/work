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
#define mod 30103

int n, i, j;
int comb[maxN][maxN];

int main()
{
    freopen("poly2.in","r",stdin);
    freopen("poly2.out","w",stdout);

    scanf("%d", &n);

    comb[0][0] = 1;
    for (i = 1; i <= 2 * n; i++) {
        comb[i][0] = 1;
        for (j = 1; j <= i; j++) {
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
            if (comb[i][j] >= mod) comb[i][j] -= mod;
        }
    }

    int ans = comb[2 * n][n] - comb[2 * n][n - 1];
    if (ans < 0) ans += mod;
    printf("%d", ans);


    return 0;
}
