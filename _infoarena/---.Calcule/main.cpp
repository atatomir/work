#include <iostream>
#include <cstdio>

using namespace std;

#define mod 20011
#define maxK 50011
#define maxN 100011

long n,i,k,ans;
long cnt[maxK],a[maxN],s[maxN];

long sets[maxN],nr;

long cb(long x){
    long i=1,j=nr,m;
    while(i<=j){
        m=(i+j)>>1;
        if(x<=sets[m])
            i=m+1;
        else
            j=m-1;
    }
    return i;
}

int main()
{
    freopen("calcule.in","r",stdin);
    freopen("calcule.out","w",stdout);

    scanf("%ld%ld",&n,&k); cnt[0]++;
    for(i=1;i<=n;i++){
        scanf("%ld",&a[i]);
        s[i] = s[i-1]+a[i]; s[i]%=k;
        ans = ans+cnt[s[i]]; ans%=mod;
        cnt[s[i]]++;
    }

    for(i=1;i<=n;i++){
        long pos = cb(a[i]);
        if(pos==nr+1) nr++;
        sets[pos]=a[i];
    }

    printf("%ld\n%ld",nr,ans);

    return 0;
}
