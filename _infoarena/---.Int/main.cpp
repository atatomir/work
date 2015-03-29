#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

long n,i;
pair<long,long> v[50005];
long dp[50005];

long cb(long x){
    long i=1,j=n,m;
    do {
        m = (i+j)/2;
        if(x < v[m].first)
            j = m-1;
        else
            i = m+1;
    }   while(i<=j);
    return j;
}

int main()
{
    freopen("int.in","r",stdin);
    freopen("int.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%ld %ld",&v[i].second,&v[i].first);
    sort(v,v+n+1);

    for(i=1;i<=n;i++){
        dp[i] = max(dp[i-1],1+dp[cb(v[i].second)]);
    }
    printf("%ld\n",dp[n]);

    return 0;
}
