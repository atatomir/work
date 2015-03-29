#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 100011

long n,i,x,pos;
long dp[maxN],prov[maxN],a[maxN],best[maxN],provDp[maxN];
bool used[maxN];

long aPos;

long cb(long x){
    long i=1,j=dp[0],m;
    while(i<=j){
        m = (i+j)>>1;
        if(x <= dp[m])
            j=m-1;
        else
            i=m+1;
    }
    return i;
}

int main()
{
    freopen("move.in","r",stdin);
    freopen("move.out","w",stdout);

    scanf("%ld",&n); aPos=1;
    for(i=1;i<=n;i++){
        scanf("%ld",&x); a[i] = x;
        pos = cb(x);
        dp[pos] = x;

        provDp[pos] = i;
        prov[i] = provDp[pos-1];

        dp[0] = max(dp[0],pos);
        best[i] = pos;

        if(best[aPos]<pos) aPos = i;
    }

    long cnt = n;
    for(;aPos;used[a[aPos]]=true,aPos=prov[aPos],cnt--);

    printf("%ld\n",cnt);
    for(i=1;i<=n;i++){
        if(used[i]) continue;
        printf("%ld %ld\n",i,i-1);
    }


    return 0;
}
