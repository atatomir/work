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

int n,m,i,j,ans;
char s[maxM];
short dp[maxN][maxM];

multiset<short> S;

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

    S.clear();
    set<short>::iterator it;
    fordef(i,1,n){
        fordef(j,1,m)
            if(dp[i][j]) S.insert(i+dp[i][j]);
        //!-----------------------

        int cnt;
        for(it = S.begin(),cnt = S.size();it!=S.end();it++,cnt--)
            ans = max(ans, (int)cnt*(*it-i) );

        //!-----------------------
        while(!S.empty()){
            it = S.begin();
            if(*it>i) break;
            S.erase(i);
        }
    }

    printf("%d",ans);

    return 0;
}
