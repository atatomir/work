#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 18
#define maxL 1024

int n,l,i,lim;
char s[maxL];
bitset<maxL> Sobo[maxN];
long long cost[maxL];
long long dp[1<<maxN];

long long compute_dp(int conf){
    if (conf == 0) return 0;
    if ( (conf&(conf-1)) == 0 ) return 0;
    if (dp[conf] != 0) return dp[conf];

    //! we have to compute dp[conf]
    dp[conf] = 1LL<<60 ;
    for (int i = 1; i <= l; i++) { //! bitul selectat
        long long actCost = cost[i];
        int conf_zero = 0;
        int conf_one = 0;

        for (int j = 1; j <= n; j++) { //! sobo selectat
            int verif = 1<<(j-1);
            if ( (conf&verif)==0 ) continue;

            if (Sobo[j][i] == 1)
                conf_one |= 1<<(j-1);
            else
                conf_zero |= 1<<(j-1);
        }

        if ((conf_one == 0) || (conf_zero == 0)) continue;

        actCost += max( compute_dp(conf_one) , compute_dp(conf_zero) );
        dp[conf] = min( dp[conf] , actCost );
    }

    return dp[conf];
}

int main()
{
    freopen("sobo.in","r",stdin);
    freopen("sobo.out","w",stdout);

    scanf("%d%d",&n,&l);
    for (i = 1; i <= n; i++) {
        scanf("%s\n",s+1);
        Sobo[i].reset();

        for (int j = 1; j <= l; j++)
            if (s[j] == '1') Sobo[i][j] = 1;
    }
    for (i = 1; i <= l; i++) scanf("%lld",&cost[i]);

    lim = (1<<n)-1;
    compute_dp( lim );

    printf("%lld",dp[lim]);

    return 0;
}
