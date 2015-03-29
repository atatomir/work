#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define mod 7733
#define maxN 1111
#define mPair pair<long,long>
#define sum first
#define pos second

long n,i,j,l,p;
long a[maxN];
vector<mPair > Hash[mod];

long long ans;

inline long getId(long x){return (x)%mod;}
void addPair(long i,long j){
    long id = getId(a[i]+a[j]);
    Hash[id].push_back(make_pair(a[i]+a[j],i));
}

long cb(long id,long x){
    long i=0,j=Hash[id].size()-1,m;
    while(i<=j){
        m = (i+j)>>1;
        if(x<=Hash[id][m].pos) j=m-1;else i=m+1;
    }
    return i;
}

int main()
{
    freopen("oite.in","r",stdin);
    freopen("oite.out","w",stdout);

    scanf("%ld %ld",&n,&l);
    for(i=1;i<=n;i++) scanf("%ld",&a[i]);
    sort(a+1,a+n+1);

    for(i=1;i<n;i++)
        for(j=i+1;j<=n;j++)
            addPair(i,j);

    for(i=1;i<n;i++){
        for(j=i+1;j<=n;j++){
            long target = l-a[i]-a[j];
            long id = getId(target);

            if(target<0) continue;
            for(p=cb(id,j+1);p<Hash[id].size();p++){
                mPair newP = Hash[id][p];

                if(newP.sum!=target) continue;
                if(newP.pos<=j) continue;
                ans++;
            }
        }
    }

    printf("%lld",ans);

    return 0;
}
