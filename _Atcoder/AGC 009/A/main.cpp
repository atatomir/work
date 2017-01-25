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

int n, i;
ll A[maxN], B[maxN];
ll ans, cnt;

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lld%lld", &A[i], &B[i]);
    }

    for (i = n; i > 0; i--) {
        A[i] += ans;

        cnt = B[i] * (A[i] / B[i]);
        while (cnt < A[i]) cnt += B[i];
        ans += cnt - A[i];
    }

    printf("%lld", ans);

    return 0;
}
