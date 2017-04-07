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

#define maxN 2016

int n, m, i, j;
ll k;
ll a[maxN][maxN];
int ans = maxN * maxN;

bool can(int l1, int l2, int c1, int c2) {
    ll aux = a[l2][c2] - a[l1 - 1][c2] - a[l2][c1 - 1] + a[l1 - 1][c1 - 1];
    return aux <= k;
}

void solve_ln(int l1, int l2, int c1, int c2, int cost, int deny) {
    while (l1 <= l2 && can(l1, l1, c1, c2)) l1++;
    while (l1 <= l2 && can(l2, l2, c1, c2)) l2--;
    if (l1 > l2 || c1 > c2) {
        ans = min(ans, cost);
        return;
    }

    if ((deny & 1) == 0) {
        if (can(l1, l2, c1, c1)) {
            if (can(l1, l2, c2, c2))
                solve_ln(l1, l2, c1 + 1, c2, cost + 1, deny | 2);
            else
                solve_ln(l1, l2, c1 + 1, c2, cost + 1, deny);
        }
    }

    if ((deny & 2) == 0) {
        if (can(l1, l2, c2, c2)) {
            if (can(l1, l2, c1, c1))
                solve_ln(l1, l2, c1, c2 - 1, cost + 1, deny | 1);
            else
                solve_ln(l1, l2, c1, c2 - 1, cost + 1, deny);
        }
    }

    if (deny == 0 && c1 != c2) {
        if (can(l1, l2, c1, c1) && can(l1, l2, c2, c2)) {
            solve_ln(l1, l2, c1 + 1, c2 - 1, cost + 2, deny);
        }
    }
}

void solve_co(int l1, int l2, int c1, int c2, int cost, int deny) {
    while (c1 <= c2 && can(l1, l2, c1, c1)) c1++;
    while (c1 <= c2 && can(l1, l2, c2, c2)) c2--;
    if (l1 > l2 || c1 > c2) {
        ans = min(ans, cost);
        return;
    }

    if ((deny & 1) == 0) {
        if (can(l1, l1, c1, c2)) {
            if (can(l2, l2, c1, c2))
                solve_co(l1 + 1, l2, c1, c2, cost + 1, deny | 2);
            else
                solve_co(l1 + 1, l2, c1, c2, cost + 1, deny);
        }
    }

    if ((deny & 2) == 0) {
        if (can(l2, l2, c1, c2)) {
            if (can(l1, l1, c1, c2))
                solve_co(l1, l2 - 1, c1, c2, cost + 1, deny | 1);
            else
                solve_co(l1, l2 - 1, c1, c2, cost + 1, deny);
        }
    }

    if (deny == 0 && l1 != l2) {
        if (can(l1, l1, c1, c2) && can(l2, l2, c1, c2)) {
            solve_co(l1 + 1, l2 - 1, c1, c2, cost + 2, deny);
        }
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%lld%d%d", &k, &m, &n);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            scanf("%lld", &a[i][j]);
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    }

    solve_ln(1, n, 1, m, n, 0);
    solve_co(1, n, 1, m, m, 0);


    printf("%d", ans);


    return 0;
}
