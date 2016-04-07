#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

int lim[111];
int i, pos, dim, how, n, m;
int ans = 0;

int main()
{
    freopen("speeding.in","r",stdin);
    freopen("speeding.out","w",stdout);

    scanf("%d %d", &n, &m);

    pos = 1;
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &dim, &how);

        for (; dim > 0; dim--) {
            lim[pos] = how;
            pos++;
        }
    }

    pos = 1;
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &dim, &how);

        for (; dim > 0; dim--) {
            if (how > lim[pos])
                ans = max(ans, how - lim[pos]);
            pos++;
        }
    }

    printf("%d", ans);


    return 0;
}
