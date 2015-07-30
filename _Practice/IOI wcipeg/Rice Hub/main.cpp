#include <iostream>
#include <cstdio>

using namespace std;

//#define DEBUG
#define maxN 100011

long n,i,j,pos,ans;
long long l,b,need,act;
long long x[maxN];
long long sum[maxN];

long long getNeed(){
    long wh = i-1+(j-i+2)/2;
    if(wh>pos){
        act += 1LL*(wh-i)*(x[wh]-x[wh-1]);
        act -= 1LL*(j-wh+1)*(x[wh]-x[wh-1]);
    }
    pos = wh;
}

int main()
{
    #ifdef DEBUG
    freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld %lld %lld",&n,&l,&b);
    for(i=1;i<=n;i++) {
        scanf("%ld",&x[i]);
        sum[i]=x[i]+sum[i-1];
    }

    i=1; pos=1;act=0; ans=1;
    for(j=1;j<=n;j++){
        act += x[j]-x[pos]; getNeed();
        while(act>b) {
            act -= x[pos]-x[i++];
            getNeed();
        }

        ans = max(ans,j-i+1);
    }

    printf("%ld",ans);

    return 0;
}
