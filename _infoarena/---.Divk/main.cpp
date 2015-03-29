#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 500011
#define maxK 100011

long n,k,a,b,i;
long v[maxN];
long cnt[maxK];

long long ans;

int main()
{
    freopen("divk.in","r",stdin);
    freopen("divk.out","w",stdout);

    scanf("%ld%ld%ld%ld",&n,&k,&a,&b);
    for(i=1;i<=n;i++){
        scanf("%ld",&v[i]);
        v[i] += v[i-1];
        v[i] %= k;
    }

    cnt[0]++;
    for(i=a;i<=n;i++){
        if(i-b-1>=0) cnt[v[i-b-1]]--;

        ans += cnt[v[i]];
        cnt[v[i-a+1]]++;
    }

    printf("%lld",ans);

    return 0;
}
