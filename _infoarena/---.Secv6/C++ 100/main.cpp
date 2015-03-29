#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

#define mod 8192

long n,i,k,ans;
long x[mod];
stack<long> S;

int main()
{
    freopen("secv6.in","r",stdin);
    freopen("secv6.out","w",stdout);

    scanf("%ld",&n);
    k = mod; if(k > n) k = n;
    for(i=0;i<k;i++) scanf("%ld",&x[i]);

    S.push(0);
    for(i=1;i<n;i++){
        long cont = 1,val = i + (x[i/mod] ^ x[i%mod]);
        while(S.top() < val){
            S.pop(); cont++;
            if(S.empty()) break;
        }
        ans += cont;
        if(S.size() == 0) ans--;
        if(!S.empty())
            if(S.top() == val) continue;
        S.push(val);
    }

    printf("%ld",ans);

    return 0;
}
