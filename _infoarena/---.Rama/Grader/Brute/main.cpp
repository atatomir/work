#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 777
#define up my_up
#define left my_left

int n, m, i, j, k, l;
char s[maxN][maxN];

int up[maxN][maxN], left[maxN][maxN];
int ans = 0;

bool isGood(int l1, int c1, int l2, int c2) {
    if (up[l2][c1] - up[l1 - 1][c1] != l2 - l1 + 1) return false;
    if (up[l2][c2] - up[l1 - 1][c2] != l2 - l1 + 1) return false;

    if (left[l1][c2] - left[l1][c1 - 1] != c2 - c1 + 1) return false;
    if (left[l2][c2] - left[l2][c1 - 1] != c2 - c1 + 1) return false;

    return true;
}

int main()
{
    freopen("rama.in","r",stdin);
    freopen("rama.ok","w",stdout);

    scanf("%d%d\n", &n, &m);
    for (i = 1; i <= n; i++)
        scanf("%s\n", s[i] + 1);

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            up[i][j] = up[i - 1][j] + s[i][j] - '0';
            left[i][j] = left[i][j - 1] + s[i][j] - '0';
        }
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            for (k = i; k <= n; k++)
                for (l = j; l <= m; l++)
                    if (isGood(i, j, k, l))
                        ans = max(ans, (k - i + 1) * (l - j + 1) );

    printf("%d", ans);

    return 0;
}
