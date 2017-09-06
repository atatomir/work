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

#define maxN 200011

int n, m, i, j, cover, x, y;
int a[maxN], cnt[maxN], here[maxN];

void rm(int x) {
    if (x - cnt[x] + 1 >= 1)
        if (--here[ x - cnt[x] + 1 ] == 0)
            cover--;
    cnt[x]--;
}

void add(int x) {
    if (x - cnt[x] >= 1)
        if (++here[ x - cnt[x] ] == 1)
            cover++;
    cnt[x]++;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) scanf("%d", &a[i]), add(a[i]);

    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        rm(a[x]);
        add(y);
        a[x] = y;

        printf("%d\n", n - cover);
    }


    return 0;
}
