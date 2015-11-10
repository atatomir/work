#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 22
#define maxM 411

int n, m, i, j, x, y;
int mask[maxM];

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        mask[i] |= 1 << (x - 1);
        mask[i] |= 1 << (y - 1);
    }

    int ans = 0;

    int limit = (1 << n);
    for (i = 0; i < limit; i++) {
        bool good = true;

        for (j = 1; j <= m; j++) {
            if ( (i & mask[j]) == mask[j] ) {
                good = false;
                break;
            }
        }

        if (good) ans++;
    }

    printf("%d", ans);

    return 0;
}
