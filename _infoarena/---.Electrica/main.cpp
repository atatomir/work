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

#define maxN 2024

int n, m, i, j, l, need;
char mat[maxN][maxN];
int smen[maxN][maxN];
int ans;

int main()
{
    freopen("electrica.in","r",stdin);
    freopen("electrica.out","w",stdout);

    scanf("%d%d%d\n", &n, &m, &l);

    for (i = 1; i <= n; i++) {
        scanf("%s\n", mat[i] + 1);

        for (j = 1; j <= m; j++) {
            smen[i][j] ^= smen[i - 1][j] ^ smen[i][j - 1] ^ smen[i - 1][j - 1];
            if (smen[i][j] != mat[i][j] - '0') {
                if (i + l > n + 1 || j + l > m + 1) {
                    printf("-1");
                    return 0;
                }

                smen[i][j] ^= 1;
                smen[i + l][j] ^= 1;
                smen[i][j + l] ^= 1;
                smen[i + l][j + l] ^= 1;

                ans ++;
            }
        }
    }

    printf("%d", ans);

    return 0;
}
