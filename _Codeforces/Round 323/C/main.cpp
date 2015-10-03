#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 511
#define def -1

int n, i, j, x, cnt, last;
int v[maxN * maxN];

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            scanf("%d", &v[++x]);
        }
    }

    cnt = n;
    n *= n;
    sort(v + 1, v + n + 1);

    while(cnt) {

    last = -1;
    for (i = n; (i >= 1) && (cnt > 0); i--) {
        if (v[i] == -1) continue;

        if (v[i] != last ) {
            printf("%d ", v[i]);
            last = v[i];
            v[i] = def;
            cnt--;
        }

    }



    }



    return 0;
}
