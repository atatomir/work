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

#define maxN (1 << 20) + 22

int t, ti;
int n, m, k, i, base, maxi;
ll ans;
ll cnt[maxN];


int main()
{
    freopen("aiacujoc.in","r",stdin);
    freopen("aiacujoc.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%d%d", &n, &m, &k);
        memset(cnt, 0, sizeof(cnt));
        ans = 0;

        k++; n--; m--;

        base = n / k;
        maxi = n % k;
        for (i = 0; i < k && i <= n; i++) {
            cnt[(i ^ ((n - i) % k))] += base + (i <= maxi ? 1 : 0);
        }

        base = m / k;
        maxi = m % k;
        for (i = 0; i < k && i <= m; i++) {
            ans += 1LL * cnt[(i ^ ((m - i) % k))] * (base + (i <= maxi ? 1 : 0)) ;
        }

        printf("%lld\n", ans);
    }


    return 0;
}
