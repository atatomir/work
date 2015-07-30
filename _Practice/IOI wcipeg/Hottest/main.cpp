#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

long n,k,i,sum,ans,x;
deque<long> vraja;

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("test.in","r",stdin);
    #endif

    scanf("%ld %ld",&n,&k);
    vraja.push_back(0);
    for(i=1;i<k;i++){
        scanf("%ld",&x);
        vraja.push_back(x); sum += x;
    }

    for(i=k;i<=n;i++){
        scanf("%ld",&x);
        sum += x; vraja.push_back(x);
        sum -= vraja.front(); vraja.pop_front();
        ans = max(ans,sum);
    }
    printf("%ld",ans);


    return 0;
}
