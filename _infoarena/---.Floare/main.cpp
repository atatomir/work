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

int n, k, t, i, x;
int a[maxN];

int dp[maxN];
int l, r;
int dq[maxN];

pair<int, int> best;

int main()
{
    freopen("floare.in","r",stdin);
    freopen("floare.out","w",stdout);

    best = mp(-1000000000, -1);

    scanf("%d%d%d", &n, &k, &t);
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        best = max(best, mp(a[i], i));
    }


    l = r = 1;
    dq[1] = 0;
    dp[0] = n - 1;

    for (i = 1; i <= 200000; i++) {
        while (dq[l] < i - k) l++;

        dp[i] = (dp[dq[l]] + 1) % n;

        while (a[ n - 1 - dp[ dq[r] ] ] <= a[ n - 1 - dp[i] ] && l <= r) r--;
        dq[++r] = i;
    }

    best.second = 0;
    for (i = 1; i <= t; i++) {
        scanf("%d", &x);
        int ans = (dp[x] + best.second) % n;
        printf("%d\n", ans + 1);
    }


    return 0;
}
