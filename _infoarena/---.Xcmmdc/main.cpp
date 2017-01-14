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
#define maxLog 10

int n, m, k, q, i, j, dim, sdim, x;
int rmq[maxLog][maxN][maxN];
int hp[maxN];

int ans[maxN];

inline int cmmdc(int x, int y) {
    if (x < y) swap(x, y);

    while(y > 0) {
        x %= y;
        swap(x, y);
    }

    return x;
}

inline int query(int x, int y, int l) {
    static int lvl, dim;

    lvl = hp[l];
    dim = 1 << lvl;

    return cmmdc(cmmdc(rmq[lvl][x][y], rmq[lvl][x][y + l - dim]),
                 cmmdc(rmq[lvl][x + l - dim][y], rmq[lvl][x + l - dim][y + l - dim]));
}



int main()
{
    freopen("xcmmdc.in","r",stdin);
    freopen("xcmmdc.out","w",stdout);

    scanf("%d%d%d%d", &n, &m, &k, &q);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            scanf("%d", &rmq[0][i][j]);

    for (int lvl = 1; lvl < maxLog; lvl++) {
        dim = (1 << lvl);
        sdim = dim >> 1;

        for (i = 1; i + dim - 1 <= n; i++) {
            for (j = 1; j + dim - 1 <= m; j++) {
                rmq[lvl][i][j] = cmmdc(cmmdc(rmq[lvl - 1][i][j], rmq[lvl - 1][i][j + sdim]),
                                       cmmdc(rmq[lvl - 1][i + sdim][j], rmq[lvl - 1][i + sdim][j + sdim]));
            }
        }
    }

    hp[1] = 0;
    for (i = 2; i <= 1000; i++)
        hp[i] = 1 + hp[i >> 1];

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {

            int loc = 0;
            for (int step = 1 << 10; step > 0; step >>= 1)
                if (i + loc + step - 1 <= n && j + loc + step - 1 <= m)
                    if (query(i, j, loc + step) > k)
                        loc += step;

            ans[loc + 1]++;

            for (int step = 1 << 10; step > 0; step >>= 1)
                if (i + loc + step - 1 <= n && j + loc + step - 1 <= m)
                    if (query(i, j, loc + step) >= k)
                        loc += step;

            ans[loc + 1]--;
        }
    }

    for (i = 1; i <= n; i++) ans[i] += ans[i - 1];

    for (i = 1; i <= q; i++) {
        scanf("%d", &x);
        printf("%d\n", ans[x]);
    }


    return 0;
}
