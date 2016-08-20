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

#define maxN (2 * 277)
#define mod 9901

int n, i, j, k;
int v[maxN];
int dp[maxN][maxN];
ll aux;


int main()
{
    freopen("culori.in","r",stdin);
    freopen("culori.out","w",stdout);

    scanf("%d", &n); n = 2 * n - 1;
    for (i = 1; i <= n; i++)
        scanf("%d", &v[i]);

    for (int l = 0; l < n; l++) {
        for (i = 1; i + l <= n; i++) {
            j = i + l;
            aux = 0;

            if (i == j) dp[i][j] = 1;
            if (i >= j || v[i] != v[j]) continue;

            for (k = i + 1; k <= j; k++)
                if (v[i] == v[k])
                    aux += 1LL * dp[i + 1][k - 1] * dp[k][j];

            dp[i][j] = aux % mod;
        }
    }


    printf("%d", dp[1][n]);


    return 0;
}
