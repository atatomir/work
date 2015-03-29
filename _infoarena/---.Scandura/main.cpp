#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

long long n,i,Pay,k,x,nn;
queue<long long> iQ,Q;

int main()
{
    freopen("scandura.in","r",stdin);
    freopen("scandura.out","w",stdout);

    scanf("%lld %lld",&n,&k);
    for(nn=n;(nn-1)%(k-1) != 0;nn++) iQ.push(0);
    for(i=1;i<=n;i++){
        scanf("%lld",&x);
        iQ.push(x);
    }
    n = nn;

    while(n > 1){
        long long val,sum=0;
        bool second;

        for(i=1;i<=k;i++){
            second = false; val = 1LL << 60;
            if(!iQ.empty()) val = iQ.front();
            if(!Q.empty())
                if(val > Q.front()) val = Q.front(),second = true;

            if(!second) iQ.pop(); else Q.pop();
            sum += val;
        }
        Pay += sum;
        Q.push(sum);
        n -= k-1;
    }

    printf("%lld",Pay);

    return 0;
}
