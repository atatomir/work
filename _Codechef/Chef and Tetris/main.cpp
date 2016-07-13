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

#define maxN 10011

int t, ti;
int n, i;
int a[maxN], b[maxN];
int ans;

int wa[maxN], wb[maxN];

bool check(int val) {
    int i;

    memcpy(wa, a, sizeof(a));
    memcpy(wb, b, sizeof(b));

    for (i = 1; i <= n; i++) {
        wa[i] += wb[i - 1];
        wb[i - 1] = 0;

        if (wa[i] == val) continue;

        if (wa[i] + wb[i] == val) {
            wa[i] += wb[i];
            wb[i] = 0;
            continue;
        }

        if (wa[i] + wb[i + 1] == val) {
            wa[i] += wb[i + 1];
            wb[i + 1] = 0;
            continue;
        }

        if (wa[i] + wb[i] + wb[i + 1] == val) {
            wa[i] += wb[i] + wb[i + 1];
            wb[i] = wb[i + 1] = 0;
            continue;
        }

        return false;
    }

    return wb[n] == 0;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));

        scanf("%d", &n);
        for (i = 1; i <= n; i++) scanf("%d", &b[i]);
        for (i = 1; i <= n; i++) scanf("%d", &a[i]);

        ans = -1;
        if (check(a[1])) ans = max(ans, a[1]);
        if (check(a[1] + b[1])) ans = max(ans, a[1] + b[1]);
        if (check(a[1] + b[2])) ans = max(ans, a[1] + b[2]);
        if (check(a[1] + b[1] + b[2])) ans = max(ans, a[1] + b[1] + b[2]);

        printf("%d\n", ans);
    }


    return 0;
}
