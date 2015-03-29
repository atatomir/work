#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

#define maxN 30111
#define mPair pair<long,long>
#define st first
#define en second
#define mod 32173

struct cmp{
    bool operator()(long a,long b){
        return a > b;
    }
};

long n,i,cnt,fr;
long used[maxN];
mPair a[maxN];
priority_queue<long,vector<long>,cmp > H;

long long ans;

int main()
{
    freopen("ben.in","r",stdin);
    freopen("ben.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%ld %ld",&a[i].st,&a[i].en);
    sort(a+1,a+n+1);

    for(i=1;i<=n;i++){
        used[i] = used[i-1];

        if(!H.empty())
        while(H.top()<a[i].st){
            H.pop(); fr++; used[i]--;
            if(H.empty()) break;
        }

        if(fr==0) cnt++,fr++;
        used[i]++; fr--;

        H.push(a[i].en);
    }

    ans = 1;
    for(i=1;i<=n;i++){
        ans = ans*(cnt-used[i]+1);
        if(ans>=mod) ans%=mod;
    }

    printf("%ld %ld",cnt,ans);

    return 0;
}
