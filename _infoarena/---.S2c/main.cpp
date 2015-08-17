#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 2015

int t,i,last,n,ans;
int v[maxN];
int dp[maxN][maxN];

void Minimize(int dim,int *_v){
    vector< pair<int,int> > aux;
    aux.clear();

    for (i=1;i<=n;i++) aux.pb( mp( _v[i],i ) );
    sort(aux.begin(),aux.end());

    _v[ aux[0].second ] = 1;
    for (i=1;i<aux.size();i++) {
        if (aux[i].first==aux[i-1].first)
            _v[ aux[i].second ] = _v[ aux[i-1].second ];
        else
            _v[ aux[i].second ] = _v[ aux[i-1].second ]+1;
    }
}

int main()
{
    freopen("s2c.in","r",stdin);
    freopen("s2c.out","w",stdout);

    scanf("%d",&t);
    for (;t--;) {
        scanf("%d",&n);
        for (i=1;i<=n;i++) scanf("%d",&v[i]);

        Minimize(n,v);
        ans = 0;

        for (i=1;i<=n;i++) {
            for (last=0;last<=n;last++) dp[i][last] = 1;

            for (last=i-1;last>0;last--)
                dp[i][ v[last] ] = max( dp[i][ v[last] ] , dp[last][ v[i]-1 ]+1 );
            for (last=1;last<=n;last++)
                dp[i][last] = max(dp[i][last],dp[i][last-1]);

            ans = max(ans,dp[i][n]);
        }

        printf("%d\n",ans);
    }


    return 0;
}
