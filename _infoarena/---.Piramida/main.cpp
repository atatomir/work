#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define ll long long

#define maxDim 600011
#define mod 10000
#define maxLev 23

int n, i, j;
int k, aux;
int how[maxLev][maxLev];

int dp[maxDim];

int main()
{
    freopen("piramida.in", "r", stdin);
    freopen("piramida.out", "w", stdout);

    scanf("%d", &n);

    aux = 1;
    for (k = 0; ; k++) {
        if (n - aux < 0) break;
        aux <<= 1;
    }

    k--;
    aux >>= 1;
    n -= aux;

    how[1][1] = 1;
    for (i = 2; i <= k + 1; i++)
        for (j = 1; j <= i; j++)
            how[i][j] = how[i - 1][j - 1] + how[i - 1][j];

    k++;

    dp[0] = 1;
    for (i = 1; i <= k; i++) {
        int act = how[k][i];
        int lim = n - act;

        for (j = 0; j <= lim; j++) {
            dp[j + act] += dp[j];
            if (dp[j + act] >= mod)
                dp[j + act] -= mod;
        }
    }

    printf("%d", dp[n]);

    return 0;
}
