/*
 * solve(n, d) = solve(n / d, 1)
 * solve(n, 1) = (n * (n - 1)) / 2 + n - solve(n, 2) - solve(n, 1) - solve(n, 2) - ... -solve(n, n);
 * a) solve(n, k1) could be equal to solve(n, k2), because n/k1 = n/k2 (dont compute twice)
 * b) precompute phi(i) for i <= def (1000000)
 *
 * if D = I * C + R then minimum I' when D = I' * C + R' is
 * I' = I - [ (I - R - 1) / (C + 1) ]
 */

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

#define def 1000000LL

int n, d, i;
ll phi[def + 11];
unordered_map<int, ll> work;


void precomp() {
    ll i, j;

    for (i = 1; i <= def; i++) phi[i] = i;

    for (i = 2; i <= def; i++) {
        if (phi[i] == i) {
            //! prime
            for (j = i; j <= def; j += i)
                phi[j] = (phi[j] / i) * (i - 1);
        }

        phi[i] += phi[i - 1];
    }
}

ll solve(ll lim) {
    int i, C, R, last;
    ll ans = 0;

    if (lim <= def)
        return phi[lim];

    if(work[lim]) return work[lim];

    ans = (1LL * (lim * (lim - 1))) / 2LL + lim;

    int sqr = sqrt(lim);
    for (i = 2; i <= sqr; i++)
        ans -= solve(lim / i);

    for (i = lim; i > sqr; i = last - 1) {
        C = lim / i;
        R = lim % i;
        last = max(sqr + 1, i - ((i - R - 1) / (C + 1)));

        ans -= 1LL * (i - last + 1) * solve(C);
    }

    work[lim] = ans;
    return ans;
}

int main()
{
    freopen("cntgcd.in","r",stdin);
    freopen("cntgcd.out","w",stdout);

    precomp();

    scanf("%d%d", &n, &d);
    printf("%lld", solve(n / d));



    return 0;
}
