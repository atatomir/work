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

#define maxN 1024
#define maxLet 26

int t,n,i,j,pos;
char s[maxN],ans[maxN];
short last[maxN][maxLet];
long long k,dp[maxN];

int main()
{
    freopen("kss.in","r",stdin);
    freopen("kss.out","w",stdout);

    scanf("%d",&t);
    for (;t--;) {
        scanf("%d %lld\n%s\n",&n,&k,s+1);
        memset(last,0,sizeof(last));
        const long long lim = k+1;

        for (i=n;i>0;i--) {
            memcpy(last[i-1],last[i],sizeof(last[i]));
            last[i-1][ s[i]-'a' ] = i;
        }

        for (i=n;i>=0;i--) {
            dp[i] = 1;
            for(j=0;j<26;j++){
                if (last[i][j]==0) continue;
                dp[i] += dp[ last[i][j] ];
                if (dp[i] > lim) { dp[i] = lim; break; }
            }
        }

        dp[0]--;
        if (k>dp[0]) {
            printf("-1\n");
            continue;
        }

        pos=0;
        for (i=0;i<=n;) {
            if (k==0) break;

            for (j=0;j<26;j++) {
                if (last[i][j]==0) continue;
                if (dp[ last[i][j] ] < k) {
                    k -= dp[ last[i][j] ];
                } else {
                    ans[++pos] = j+'a';
                    i = last[i][j]; k--;
                    break;
                }
            }
        }
        ans[pos+1] = '\0';

        printf("%s\n",ans+1);
    }


    return 0;
}
