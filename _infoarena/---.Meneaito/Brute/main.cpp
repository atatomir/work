#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 10000

int n, i, j;
int a[maxN], b[maxN], pos[maxN];
int way[maxN];
int lim = 2000000;

int how = 0;

int main()
{
    freopen("meneaito.in","r",stdin);
    freopen("meneaito.ok","w",stdout);

    scanf("%d", &n);
    for (i = 2; i < n; i++) {
        scanf("%d", &a[i]);
        pos[i] = a[i];

        how += (pos[i] == i ? 1 : 0);
        way[i] = +1;
    }
    for (i = 2; i < n; i++) {
        scanf("%d", &b[i]);
    }

    for (i = 0; i <= lim; i++) {

        if (how == 0) {
            printf("%d", i);
            return 0;
        }

        for (j = 2; j < n; j++) {
            if (pos[j] == j) how--;

            pos[j] += way[j];
            if (pos[j] < a[j] || pos[j] > b[j]) {
                way[j] = (way[j] == -1 ? 1 : -1);
                pos[j] += 2 * way[j];
            }

            if (a[j] == b[j]) pos[j] = a[j];

            if (pos[j] == j) how++;
        }
    }

    printf("-1");

    return 0;
}
