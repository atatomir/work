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

const int lim = 100000;

int n, i, x, bb, ans;
int a[maxN];

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        a[x]++;
    }

    for (i = 1; i <= lim; i++) {
        while (a[i] >= 3) a[i] -= 2;
        if (a[i] > 0) ans++;
        if (a[i] == 2) bb ^= 1;
    }

    if (bb == 1)
        ans--;

    printf("%d", ans);



    return 0;
}
