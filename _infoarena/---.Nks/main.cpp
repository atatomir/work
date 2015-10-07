#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1024

int n, m, p, q, s, i, j, ss;
char ans[maxN][maxN];

int main()
{
    freopen("nks.in","r",stdin);
    freopen("nks.out","w",stdout);

    scanf("%d%d%d%d%d", &n, &m, &p, &q, &s); ss = s;
    for (i = 0; i < p; i++)
        for (j = 0; j < q; j++)
            if (s > 0)
                ans[i][j] = '1', s--;
            else
                ans[i][j] = '0';

    int x = 0, y = 0;
    for (i = 0; i < n; i++) {
        y = 0;
        for (j = 0; j < m; j++) {
            ans[i][j] = ans[x][y];

            if (++y == q) y = 0;
        }

        if (++x == p) x = 0;

        printf("%s\n", ans[i]);
    }

    /*for (i = 1; i <= n - p + 1; i++) {
        for (j = 1; j <= m - q + 1; j++) {
            int aux = 0;

            for (int ii = i; ii < i + p; ii++)
                for (int jj = j; jj < j + q; jj ++)
                    aux += ans[ii - 1][jj - 1] - '0';

            if (aux != ss) cerr << "No";
        }
    }*/

    return 0;
}
