#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011

int n, i, ans, last;
double k, R, need, aux;
ll v[maxN], dist, p1, p2;
int dp[maxN];

ll ch(double a) {
    return 1000000.00 * a ;
}

bool equal(ll a, ll b) {
    return -1 <= a - b && a - b <= 1;
}

int main()
{
    freopen("kgon.in","r",stdin);
    freopen("kgon.out","w",stdout);

    scanf("%d%lf%lf", &n, &k, &R);
    need = (2.00 * M_PI * R) / k;

    for (i = 1; i <= n; i++) {
        scanf("%lld.%lld", &p1, &p2);
        v[i] = p1 * 1000000LL + p2;
    }

    sort(v + 1, v + n + 1);
    dist = ch(need);

    last = 1;
    for (i = 1; i <= n; i++) {
        while (v[i] - v[last + 1] >= dist) last++;

        dp[i] = 1;
        if (equal(v[i] - v[last], dist)) dp[i] += dp[last];

        if (dp[i] == (int)k) ans++;
    }

    printf("%d", ans);
    cerr << ans;


    return 0;
}
