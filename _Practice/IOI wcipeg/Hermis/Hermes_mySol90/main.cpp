#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 70000
#define maxDim 1024
#define mp make_pair
#define actA wh[s][0][k]
#define actB wh[s][1][k]
#define xx first
#define yy second
#define abs abss

long n,i,k,x,y,pos,s,d,ans;
long cnt[2];
pair< pair<long,long>,long > wh[2][2][maxN],bestX,bestY;
long newCost,newX,newY;

long abs(long x){
    if(x>0) return x;
    return -x;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("test.in","r",stdin);
    #endif // ONLINE_JUDGE

    scanf("%ld",&n); x=y=0; s=0; d=1;
    wh[s][0][ ++cnt[s] ] = mp(mp(x,y),0);
    wh[s][1][   cnt[s] ] = mp(mp(x,y),0); //! dublam pt simplitate

    for(i=1;i<=n;i++){
        scanf("%ld %ld",&x,&y);

        cnt[d]=0; bestX.second = bestY.second = 1<<29;
        for(k=1;k<=cnt[s];k++){
            newCost = actA.second + abs(x-actA.first.xx);
            newX    = x;
            newY    = actA.first.yy;
            wh[d][0][ ++cnt[d] ] = mp( mp( newX , newY ) , newCost );

            long rez = actA.second + abs(y-actA.first.yy);
            if(rez < bestX.second) bestX = mp( mp( actA.first.xx , y ), rez );


            newCost = actB.second + abs(y-actB.first.yy);
            newX    = actB.first.xx;
            newY    = y;
            wh[d][1][   cnt[d] ] = mp( mp( newX , newY ) , newCost );

            /**/ rez = actB.second + abs(x-actB.first.xx);
            if(rez < bestY.second) bestY = mp( mp( x , actB.first.yy ), rez );
        }

        wh[d][1][ ++cnt[d] ] = bestX;
        wh[d][0][   cnt[d] ] = bestY;

        swap(d,s);
    }

    ans = (1<<29);
    for(k=1;k<=cnt[s];k++) {
        ans = min(ans, actA.second );
        ans = min(ans, actB.second );
    }

    printf("%ld",ans);

    return 0;
}
