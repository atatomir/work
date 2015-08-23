#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011
#define mod 666013

int n,i;
int v[maxN];

int dp[maxN]; //! cu mod
double dpLog[maxN]; //! cu logaritmare

int main()
{
    freopen("emax.in","r",stdin);
    freopen("emax.out","w",stdout);

    scanf("%d",&n);
    for (i = 1; i <= n; i++) {
        scanf("%d",&v[i]);
        if (v[i]<0) v[i] *= -1;

        if (v[i] == 0) {
            i--; n--;
            continue;
        }
    }

    dp[0] = 1; dpLog[0] = log( 1.00 );
    dp[1] = v[1]; dpLog[1] = log( 1.00*dp[1] );
    dp[2] = max(v[1]*v[2], v[1]+v[2]); dpLog[2] = log( 1.00*dp[2] );

    for (i = 3; i <= n; i++) {
        double v1 = dpLog[i-1] + log( 1.00 * (v[i]) );
        double v2 = dpLog[i-2] + log( 1.00 * (v[i-1] + v[i]) );
        double v3 = dpLog[i-3] + log( 1.00 * (v[i-2] + v[i-1] + v[i]) );

        if (v1 > v2 && v1 > v3) { //! v1 maxim
            dpLog[i] = v1;
            dp[i] = (dp[i-1] * v[i]) % mod;
        } else
        if (v2 > v3) { //! v2 maxim
            dpLog[i] = v2;
            dp[i] = (dp[i-2] * (v[i-1] + v[i]) ) % mod;
        } else { //! v3 maxim
            dpLog[i] = v3;
            dp[i] = (dp[i-3] * (v[i-2] + v[i-1] + v[i]) ) % mod;
        }
    }

    printf("%d",dp[n]);


    return 0;
}
