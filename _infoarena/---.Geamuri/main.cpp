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

#define maxLim 1055
#define maxN 50011

int limi, n, m, i, j, x;
int px1, px2, py1, py2;
int smen[maxLim][maxLim];
int cnt[maxN];

int main()
{
    freopen("geamuri.in","r",stdin);
    freopen("geamuri.out","w",stdout);

    scanf("%d%d", &limi, &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &px1, &py1, &px2, &py2);
        smen[px1][py1]++;
        smen[px1][py2 + 1]--;
        smen[px2 + 1][py1]--;
        smen[px2 + 1][py2 + 1]++;
    }

    for (i = 1; i <= limi; i++) {
        for (j = 1; j <= limi; j++) {
            smen[i][j] += smen[i - 1][j] + smen[i][j - 1] - smen[i - 1][j - 1];
            cnt[smen[i][j]]++;
        }
    }

    scanf("%d", &m);
    for (i = 1; i <= m; i++)
        scanf("%d", &x),
        printf("%d\n", cnt[x]);


    return 0;
}
