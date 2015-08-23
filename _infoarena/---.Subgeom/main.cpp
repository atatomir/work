#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 5011
#define maxVal 100011

int n,i,t,R,cnt,ans,act,limit;
int v[maxN];
short dp[maxVal];
short lastUsed[maxVal];

int Try(){
    int i;
    cnt++;

    for (i = 1; i <= n; i++) {
        if( lastUsed[ v[i] ] == cnt ) return 1;
        for (int j = v[i]*2; j <= limit; j++ ) lastUsed[j] = cnt;
    }

    return 0;
}

int main()
{
    freopen("subgeom.in","r",stdin);
    freopen("subgeom.out","w",stdout);

    scanf("%d",&t);
    for (; t--;) {
        scanf("%d",&n);
        limit = 1;
        for (i = 1; i <= n; i++) {
            scanf("%d",&v[i]);
            limit = max(limit,v[i]);
        }

        ans = 1;
        for ( R = 2; R*R <= limit; R++ ) {
            ++cnt;

            for (i = 1; i <= n; i++) {
                if (v[i] % R != 0) {
                    if ( lastUsed[ v[i] ] != cnt ){
                        lastUsed[ v[i] ] = cnt;
                        dp[ v[i] ] = 1;
                    }
                    continue;
                }

                if (lastUsed[ v[i]/R ] == cnt)
                    act = dp[ v[i]/R ]+1;
                else
                    act = 1;

                lastUsed[ v[i] ] = cnt;
                dp[ v[i] ] = act;

                ans = max(ans,act);
            }
        }

        if(ans == 1) ans += Try();
        printf("%d\n",ans);
    }


    return 0;
}
