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

#define maxN 20011
#define inf 1000000

int n, m, i, j, k;
int ss, dd;
int dp[2][maxN];
char A[maxN], B[maxN];

int main()
{
    freopen("edist.in","r",stdin);
    freopen("edist.out","w",stdout);

    scanf("%d%d%d\n%s\n%s", &n, &m, &k, A + 1, B + 1);

    k = min(k, m);

    ss = 0; dd = 1;
    for (i = 1; i <= k; i++)
        dp[ss][i] = i;

    for (i = 1; i <= n; i++) {
        dp[dd][0] = i;

        int low = max(1, i - k);
        int high = min(m, i + k);

        for (j = low; j <= high; j++) {
            int aux = dp[ss][j - 1];
            if (A[i] != B[j]) aux++;

            dp[dd][j] = min(dp[dd][j - 1], dp[ss][j]) + 1;
            dp[dd][j] = min(dp[dd][j], aux);
        }

        swap(ss, dd);
    }

    printf("%d", dp[ss][m]);

    return 0;
}
