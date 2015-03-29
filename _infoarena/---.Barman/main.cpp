#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define maxN 611
#define INF 2000000000

long n,i,j,t,ans,sol;
long a[maxN],v[maxN];
bool good[maxN];

int main()
{
    freopen("barman.in","r",stdin);
    freopen("barman.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld",&a[i]);
        v[i] = a[i];
    }
    sort(v+1,v+n+1);

    ans = INF;

    for(long cnt=n;cnt;cnt--){
        sol = 0;
        t=v[1]; for(i=1;i<n;i++) v[i] = v[i+1]; v[n] = t;

        for(i=1;i<=n;i++)
            if(v[i]==a[i]) good[i] = true; else good[i]=false;

        for(i=1;i<=n;i++){
            if(a[i]==v[i]) continue;
            for(j=1;good[j] || v[j]!=a[i];j++);
            good[j] = true;

            long def = max(j,i)-min(j,i);
            sol += 20 + def;
        }

        ans = min(ans,sol);
    }

    printf("%ld",ans);

    return 0;
}
