#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011

int n, m, i, x, a, b;
int how[maxN][4];

int main()
{
    freopen("bcount.in","r",stdin);
    freopen("bcount.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        how[i][1] = how[i - 1][1];
        how[i][2] = how[i - 1][2];
        how[i][3] = how[i - 1][3];

        scanf("%d", &x);
        how[i][x]++;
    }

    for (i = 1; i <= m; i++) {
        scanf("%d%d", &a, &b);
        printf("%d %d %d\n", how[b][1] - how[a - 1][1],
                             how[b][2] - how[a - 1][2],
                             how[b][3] - how[a - 1][3]);
    }


    return 0;
}
