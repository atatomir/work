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
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 100011

int t,n,k,i;
ll P,T[maxN];

int pos;
ll ant;

int main()
{
    freopen("caluti.in","r",stdin);
    freopen("caluti.out","w",stdout);

    for(scanf("%d",&t);t--;){
        scanf("%d%d%lld",&n,&k,&P);
        fordef(i,1,n) scanf("%lld",&T[i]);

        pos = n%k; if(!pos) pos += k; ant = T[pos]+P;
        for( pos+=k;pos<=n;pos+=k ) ant = max(T[pos],ant)+P;

        printf("%lld\n",ant);
    }



    return 0;
}
