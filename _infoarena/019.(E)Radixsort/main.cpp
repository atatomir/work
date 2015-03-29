#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxN 10000011
#define maxBit 31

long long n,a,b,c,i,act,bit;
long v[maxN],tmp[maxN],cnt[1<<8],sum[1<<8];

void radix(long l,long r){
    long mask=0,i;
    for(i=l;i<=r;i++)
        mask ^= (1<<i);

    memset(cnt,0,sizeof(cnt));
    for(i=1;i<=n;i++){
        long dir = (v[i]&mask)>>l;
        cnt[dir]++;
    }
    sum[0] = cnt[0];
    for(i=0;i<(1<<8);i++)
        sum[i] = sum[i-1]+cnt[i];
    memset(cnt,0,sizeof(cnt));
    memcpy(tmp,v,sizeof(v));

    for(i=1;i<=n;i++){
        long dir = (tmp[i]&mask)>>l;
        cnt[dir]++;
        v[sum[dir-1]+cnt[dir]] = tmp[i];
    }
}

int main()
{
    freopen("radixsort.in","r",stdin);
    freopen("radixsort.out","w",stdout);

    scanf("%lld %lld %lld %lld",&n,&a,&b,&c);act=b;
    for(i=1;i<=n;i++){
        v[i] = act;
        act = (act*a+b)%c;
    }

    radix(0,7);
    radix(8,15);
    radix(16,23);
    radix(24,31);

    for(i=1;i<=n;i+=10) printf("%ld ",v[i]);

    return 0;
}
