#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

#define maxN 100024

long n,i;
long long x,l,d,c;
pair<long long,long long> O[maxN];

long long ans,t;
priority_queue<long long> H;

int main()
{
    freopen("lupu.in","r",stdin);
    freopen("lupu.out","w",stdout);

    scanf("%ld %lld %lld",&n,&x,&l);
    for(i=1;i<=n;i++){
        scanf("%lld %lld",&d,&c);

        d = x-d;
        if(d < 0) d = 0; else {
            d = 1 + (d/l);
        }

        O[i] = make_pair(d,c);
    }
    sort(O+1,O+n+1);

    i=n;
    for(t=O[n].first;t;t--){
        while(O[i].first == t) H.push(O[i--].second);

        if(H.empty())
            t = O[i].first+1;
        else{
            ans += H.top();
            H.pop();
        }
    }

    printf("%lld",ans);

    return 0;
}
