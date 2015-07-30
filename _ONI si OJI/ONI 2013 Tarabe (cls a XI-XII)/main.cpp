#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back

#define maxN 200011

long long n,k,i;
long long pr[maxN],ra[maxN];
long long l,r,mid;

long long howMany(long long lim){
    long long ans = 0;
    long long i;

    fordef(i,1,n){
        if(pr[i] > lim) continue;
        ans += 1 + (lim-pr[i])/ra[i];
    }
    return ans;
}

long long getAns(long long lim){
    long long cost=0;
    long long i;

    fordef(i,1,n){
        if(pr[i] > lim) continue;
        long long how = 1 + (lim-pr[i])/ra[i];

        cost += how*pr[i];
        cost += ((how*(how-1))>>1)*ra[i];
    }

    return cost;
}

int main()
{
    freopen("tarabe.in","r",stdin);
    freopen("tarabe.out","w",stdout);

    scanf("%lld%lld",&n,&k);
    fordef(i,1,n) scanf("%lld%lld",&ra[i],&pr[i]);

    l = 0; r = (1LL<<40);
    while(l<=r){
        mid = (l+r)>>1;
        if( howMany(mid) < k )
            l = mid+1;
        else
            r = mid-1;
    }

    long long how = howMany(l);
    long long ans = getAns(l);
    ans -= l * (how-k);

    printf("%lld",ans);
    cerr << ans;

    return 0;
}
