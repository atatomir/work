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

#define maxN 250011

int t,n,i,u;
int v[maxN],pr[maxN];
int dad[maxN];
long long cost[maxN];

int main()
{
    freopen("zlego.in","r",stdin);
    freopen("zlego.out","w",stdout);

    for(scanf("%d",&t);t--;){
        scanf("%d",&n);
        fordef(i,1,n) scanf("%d",&v[i]);
        fordef(i,1,n) scanf("%lld",&cost[i]);

        u = 0;
        fordef(i,2,n){
            while(u && v[i]!=v[u+1]) u = pr[u];
            if(v[i]==v[u+1]) u++;

            dad[i] = u;
            pr[i] = u;
        }

        for(i=n;i>0;i--) cost[dad[i]] += cost[i];
        fordef(i,1,n) printf("%lld\n",cost[i]);
    }


    return 0;
}
