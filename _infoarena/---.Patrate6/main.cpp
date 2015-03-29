#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 1000111111
#define maxN 100000

long n,i,j,m;
vector<long long> V;

bool isGood(long dim){
    long i;
    long cnt = 1;

    for(i=n-1;i>=0;i--){
        while(dim != V[i]){
            dim--;
            cnt <<= 2;
            if(cnt > maxN) return true;
        }
        cnt--;
        if(cnt < 0) return false;
    }
    return true;
}

int main()
{
    freopen("patrate6.in","r",stdin);
    freopen("patrate6.out","w",stdout);

    scanf("%ld",&n);
    V.resize(n);
    for(i=1;i<=n;i++) scanf("%lld",&V[i-1]);
    sort(V.begin(),V.end());

    i = V[n-1]; j = INF;
    while(i<=j){
        m = (i+j)>>1;
        if(isGood(m))
            j=m-1;
        else
            i=m+1;
    }
    cout << i;

    return 0;
}
