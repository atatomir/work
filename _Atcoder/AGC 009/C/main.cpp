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
#define mod 1000000007
#define inf (1LL << 61)

int n, i;
ll A, B;
ll v[maxN];

int cntA[maxN], cntB[maxN];
int posA, posB;

ll dpA[maxN], dpB[maxN];
ll sumA[maxN], sumB[maxN];

void moddo(ll &a) {
    while (a < 0) a += mod;
    while (a >= mod) a -= mod;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%lld%lld", &n, &A, &B);
    for (i = 1; i <= n; i++) scanf("%lld", &v[i]);

    v[0] = -inf;
    v[n + 1] = inf;

    for (i = 1; i <= n + 1; i++) {
        cntA[i] = cntB[i] = 0;

        if (v[i] - v[i - 1] >= A)
            cntA[i] = cntA[i - 1] + 1;

        if (v[i] - v[i - 1] >= B)
            cntB[i] = cntB[i - 1] + 1;
    }

    posA = posB = 0;
    dpA[0] = dpB[0] = sumA[0] = sumB[0] = 1;

    for (i = 1; i <= n; i++) {
        while (posA + 1 <= i - 1 && v[posA +1] + A <= v[i + 1]) posA++;
        while (posB + 1 <= i - 1 && v[posB +1] + B <= v[i + 1]) posB++;

        int l = max(0, i - cntA[i] - 1);
        int r = posB;

        if (l <= r) dpA[i] = sumB[r] - (l > 0 ? sumB[l - 1] : 0);
        sumA[i] = sumA[i - 1] + dpA[i];

        l = max(0, i - cntB[i] - 1);
        r = posA;

        if (l <= r) dpB[i] = sumA[r] - (l > 0 ? sumA[l - 1] : 0);
        sumB[i] = sumB[i - 1] + dpB[i];

        moddo(dpA[i]);
        moddo(dpB[i]);
        moddo(sumA[i]);
        moddo(sumB[i]);
    }

    ll ans = dpA[n] + dpB[n];
    moddo(ans);

    printf("%lld", ans);


    return 0;
}
