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

const int maxN = 300011;

int n, i, a[maxN];
int B, W;

bool check(ll least) {
    int i, j, u;

    u = 0;
    for (i = 1; i <= n; i++) {
        if (i & 1) {
            u += a[i];
        } else {
            if (u - a[i] < 0 && u >= least) {
                u = 0;
                continue;
            }
            u -= a[i];
        }
    }

    if (u < least) return false;
    return true;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if (i & 1)
            B += a[i];
        else
            W += a[i];
    }

    if (n % 2 == 0) {
        printf("%d %d", max(B, W), min(B, W));
        return 0;
    }


    ll ans = 0;
    for (ll step = 1LL << 30; step > 0; step >>= 1)
        if (check(ans + step))
            ans += step;
  
    printf("%lld %lld", ans + W, B - ans);


    return 0;
}
