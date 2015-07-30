#include <iostream>
#include <cstdio>

using namespace std;

#define maxVal 1000005

long n,i,x,dim,maxim;
long dp[maxVal];

void checkIt(long x){
    if(dp[x-1] == 1) dp[x-1] = -1;
    if(dp[x+1] == -1) dp[x+1] = 1;
}

int main()
{
    freopen("secvente2.in","r",stdin);
    freopen("secvente2.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld",&x);
        checkIt(x);
        dim = -dp[x-1] + dp[x+1] + 1;

        if(dim > maxim) maxim = dim;
        printf("%ld\n",maxim);

        dp[x + dp[x-1]] = dim;
        dp[x + dp[x+1]] = -dim;
    }

    return 0;
}
