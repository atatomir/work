#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 1024

bool edge[maxN][maxN];
long   dp[maxN<<1][maxN<<1];
long n,m,x,y,i;

bool isEdge(long x,long y){
    if(x > n) x-=n;
    if(y > n) y-=n;
    return edge[x][y];
}

long zip(long _x,long _y){
    return _x*10000+_y;
}
pair<long,long> unzip(long _zz){
    return make_pair( _zz/10000,_zz%10000 );
}

bool compute(long bg,long en){
    if(dp[bg][en]==-1) return false;
    if(dp[bg][en] > 0) return true;
    if(bg==en)         return true;

    //! Let's compute
    long l = bg;
    long r = en; if(l<r) r--; else r++;
    if(l>r) swap(l,r);

    if( compute(l,r) && isEdge(r,en) ) dp[bg][en] = zip( l,r ); else
    if( compute(r,l) && isEdge(l,en) ) dp[bg][en] = zip( r,l );

    if(dp[bg][en]==0) dp[bg][en]=-1;


    if(dp[bg][en]==-1) return false;
    if(dp[bg][en] > 0) return true;
}

void solve(long bg,long en){
    while(bg!=en){
        long nor = en; if(nor>n) nor -= n ;
        printf("%ld\n",nor);

        pair<long,long> tmp = unzip( dp[bg][en] );
        bg = tmp.first;
        en = tmp.second;
    }


    printf("%ld\n",bg);

    exit(0);
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("test.in","r",stdin);
    #endif // ONLINE_JUDGE

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld",&x,&y);
        edge[x][y]=edge[y][x]=true;
    }

    for(i=1;i<=n;i++){
        if(compute(i,i+n-1)) solve(i,i+n-1);
        if(compute(i+n-1,i)) solve(i+n-1,i);
    }

    printf("-1");

    return 0;
}
