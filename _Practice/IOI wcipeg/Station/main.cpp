#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 500011

long n,k,i,pos,wh,x;
long ans;
bool a[maxN];

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("test.in","r",stdin);
    #endif

    scanf("%ld %ld",&n,&k);
    for(i=1;i<=n;i++) {scanf("%ld",&x); if(x) a[i]=true;}

    i=1;
    while(i<n){
        wh=-1; ans++;
        for(pos = min(n,i+k);pos>i;pos--){
            if(!a[pos]) continue;
            wh = pos; break;
        }
        if(wh==-1){
            printf("-1");
            return 0;
        }
        i=wh;
    }
    printf("%ld",ans);

    return 0;
}
