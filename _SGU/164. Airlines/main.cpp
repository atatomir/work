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

#define maxN 222

int n, i, j, k, m, x, rez;
int dist[maxN][maxN];

bool good = true;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    rez = m;
    m = (m + 1) / 2;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            scanf("%d", &x);
            if (x > m)
                dist[i][j] = 0;
            else
                dist[i][j] = n * n + 17;
        }
    }

    for (k = 1; k <= n; k++)
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (i == j) continue;
            if (dist[i][j] > 3) good = false;
        }
    }

    if (good) {
        printf("%d\n", rez - m);
        for (i = m + 1; i <= rez; i++)
            printf("%d ", i);
    } else {
        printf("%d\n", m);
        for (i = 1; i <= m; i++)
            printf("%d ", i);
    }


    return 0;
}
