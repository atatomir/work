#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 15011
#define maxM 1711

int n,m,i,j,ans,act;
char dp[maxN][maxM];
short ind[maxM],how[maxM];
short wh[maxM];

bool cmp(const short a,const short b){
    return dp[act][a] < dp[act][b];
}

void Try(){
    int i;
    fordef(i,1,m){
        int tmp = (m-i+1)*how[ ind[i] ];
        ans = max(ans, tmp );
    }
}

int main()
{
    freopen("logs.in","r",stdin);
    freopen("logs.out","w",stdout);

    scanf("%d%d\n",&n,&m);
    fordef(i,1,n) gets(dp[i]+1);

    //! solve it...
    act = 1; fordef(i,1,m) ind[i]=i;
    fordef(i,1,m) how[i] = dp[1][i]-'0';
    sort(ind+1,ind+m+1,cmp);
    Try();

    fordef(i,2,n){
        int vaj = m; act++;
        wh[0]=0;
        for(j=m;j>0;j--)
            if(dp[act][ ind[j] ]=='1') {ind[vaj--] = ind[j];how[ ind[j] ]++;}
            else                       {wh[ ++wh[0] ]=ind[j];how[ ind[j] ]=0;}

        while(vaj){
            ind[vaj] = wh[vaj];
            vaj--;
        }


        Try();

        //fordef(j,1,m) cerr << dp[act][ind[j]] << ' ';
        //cerr << '\n';
    }

    printf("%d",ans);

    return 0;
}
