#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 311

int n,k,i,j,R;
int Comb[maxN][maxN];
int dp[maxN][maxN]; //! i,dim - perm de i elemente , ultimele dim crescatoare
int aux[maxN]; //! i - nr de perm de dimensiune i cu maxim k-1 elemente crescatoare la final

void modIt(int &v) {
    while (v >= R) v -= R;
}

int main()
{
    freopen("kmax.in","r",stdin);
    freopen("kmax.out","w",stdout);

    scanf("%d%d%d", &n, &k, &R);

    for (i = 0; i <= n; i++) {
        Comb[i][0] = 1;
        for (j = 1; j <= i; j++) {
            Comb[i][j] = Comb[i-1][j-1] + Comb[i-1][j];
            modIt(Comb[i][j]);
        }
    }

    dp[1][1] = 1;
    aux[1] = (k > 1? 1 : 0);

    for (i = 2; i <= n; i++) {
        for (j = 1; j <= k; j++) {
            for (int q = 1; q < i - 1; q++) {
                dp[i][j] += ((((aux[q] * dp[i - q - 1][j]) % R) * Comb[i - 1][q]) ) % R;
                modIt(dp[i][j]);
            }
            dp[i][j] += dp[i-1][j-1] + dp[i-1][j];
            modIt(dp[i][j]);
        }

        for (j = 1; j < k; j++) aux[i] += dp[i][j];
        aux[i] %= R;
    }

    int ans = aux[n] + dp[n][k];
    modIt(ans);

    printf("%d",ans);


    return 0;
}
