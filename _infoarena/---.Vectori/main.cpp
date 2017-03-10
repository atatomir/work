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

int n, m, i, j;
int data[maxN][maxN];

int cnt, pos;
int wh[maxN];
int act[maxN];


int main()
{
    freopen("vectori.in","r",stdin);
    freopen("vectori.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            scanf("%d", &data[i][j]);
        }
    }

    for (j = 1; j <= n; j++) {
        cnt = pos = 0;

        for (i = 1; i <= m; i++) {
            if (data[i][j] != 0) {
                cnt++;
                if (data[i][j] == 1)
                    pos = i;
            }
        }

        if (cnt == 1 && pos != 0 && wh[pos] == 0)
            wh[pos] = j;
    }

    for (int tp = 1; tp <= 10; tp++) {
        for (i = 1; i <= n; i++)
            scanf("%d", &act[i]);

        for (i = 1; i <= m; i++) {
            int aux = act[wh[i]] / data[i][wh[i]];
            for (j = 1; j <= n; j++)
                act[j] -= data[i][j] * aux;
        }

        bool ok = true;
        for (i = 1; i <= n; i++)
            if (act[i] != 0)
                ok = false;

        if (ok)
            printf("1 ");
        else
            printf("0 ");
    }



    return 0;
}
