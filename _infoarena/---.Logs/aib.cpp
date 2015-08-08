#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 15011
#define maxM 1711

int n,m,i,j,ans,cnt;
char s[maxM];
short dp[maxN][maxM];

short aib[maxN];
short zrs(int x){ return (x^(x-1))&x; }
void add(int pos,int val){
    while(pos<=m){
        aib[pos]+=val;
        pos += zrs(pos);
    }
}
int sum(int pos){
    int ans=0;
    while(pos){
        ans += aib[pos];
        pos -= zrs(pos);
    }
    return ans;
}

int main()
{
    freopen("logs.in","r",stdin);
    freopen("logs.out","w",stdout);

    scanf("%d%d\n",&n,&m);
    fordef(i,1,n){
        gets(s+1);
        fordef(j,1,m) dp[i][j] = s[j]-'0';
    }

    fordef(j,1,m){
        for(i=n;i>0;i--){
            if(dp[i][j]==0) dp[i][j]=0; else {
                dp[i][j] = dp[i+1][j]+1;
                dp[i+1][j] = 0;
            }
        }
    }

    fordef(i,1,n){
        fordef(j,1,m){
            if(dp[i][j]) {
                cnt++;
                add(i+dp[i][j]-1,1);
            }
        }
        fordef(j,1,m)
            if(dp[i][j]) ans = max(ans, (cnt-sum(i+dp[i][j]-2))*(int)dp[i][j] );
    }

    printf("%d",ans);

    return 0;
}
