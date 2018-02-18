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

#define maxN 100011

int n, m, i, l, r, tp, x;
int v[maxN];

void update() {
    int i;

    for (i = l; i <= r; i++)
        if (v[i] > x)
            v[i] -= x;
}

int query() {
    int i, ans;

    ans = 0;
    for (i = l; i <= r; i++)
        if (v[i] == x)
            ans++;

    return ans;
}

int main()
{
    freopen("test.in","r",stdin);
    freopen("test.ok","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) scanf("%d", &v[i]);

    for (i = 1; i <= m; i++) {
        scanf("%d%d%d%d", &tp, &l, &r, &x);

        if (tp == 1)
            update();
        else
            printf("%d\n", query());
    }

    return 0;
}

