#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 16

int n,m,i,x,y;
bool neigh[maxN][maxN];
int still[maxN];

int dp[1<<maxN];
long long cnt[1<<maxN];


void solve(int pas,int aa,int bb,int vaj){
    if(pas==n){
        if( !aa ) return;

        int conf = aa|bb;
        int newDp = 1+dp[bb];

        if(newDp==dp[conf]) cnt[conf]+=cnt[bb]; else
        if(newDp< dp[conf]){
            dp[conf] = newDp;
            cnt[conf] = cnt[bb];
        }

        return;
    }

    solve(pas+1,aa,bb,vaj);
    if( ((1<<pas)&vaj)>0 )  solve(pas+1,aa|(1<<pas),bb,vaj & still[pas+1]);
    solve(pas+1,aa,bb|(1<<pas),vaj);
}

int main()
{
    freopen("colorare.in","r",stdin);
    freopen("colorare.out","w",stdout);

    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++) still[i] = (1<<n)-1;
    for(i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        neigh[x][y]=neigh[y][x]=true;
        still[x] ^= 1<<(y-1);
        still[y] ^= 1<<(x-1);
    }

    cnt[0] = 1;
    for(i=(1<<n);i;i--) dp[i]=2015;
    dp[0] = 0; cnt[0]= 1;
    solve( 0 ,0,0, (1<<n)-1 );

    printf("%d %lld",dp[(1<<n)-1 ],cnt[(1<<n)-1 ]);

    return 0;
}
