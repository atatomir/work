#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

struct compare {
    bool operator()(long long& a,long long& b){
        return a > b;
    }
};

long long n,k,i,x,ini,pow;
priority_queue<long long,vector<long long>,compare> pq;

int main()
{
    freopen("bleach.in","r",stdin);
    freopen("bleach.out","w",stdout);

    scanf("%lld %lld\n",&n,&k);

    for(i=1;i<=k;i++){
        scanf("%lld ",&x);
        pq.push(x);
    }

    for(i=k+1;i<=n;i++){
        scanf("%lld ",&x);
        pq.push(x);

        x = pq.top(); pq.pop();
        if(pow < x) ini += x-pow;
        pow = max(2*x,pow+x);
    }

    while(!pq.empty()){
        x = pq.top(); pq.pop();
        if(pow < x) ini += x-pow;
        pow = max(2*x,pow+x);
    }

    printf("%lld",ini);

    return 0;
}
