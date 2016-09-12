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

int n, k, i, j;
ll pows[maxN];
ll dp[maxN][maxN];

int main()
{
    cin >> n >> k;

    for (i = 1; i <= n; i++) pows[i] = 1;
    for (i = 0; i <= k; i++) {
        printf("#%d : ", i);
        for (j = 1; j <= n; j++) {
            dp[i][j] = dp[i][j - 1] + pows[j];
            pows[j] *= j;
            printf("%d ", dp[i][j]);
        }

        printf("\n");
    }



    return 0;
}
