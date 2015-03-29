#include <iostream>
#include <cstdio>
#include <bitset>

using namespace std;

#define maxN 175
#define maxM 11200

long n,m,i,j,t,k;
bitset<11500> dp[maxN]; //!! i-drepte , j-intersectii = posbil/imposibil
//!! daca dp[i][j]==true atunci avem i+j+1 zone

int main()
{
    freopen("intersect.in","r",stdin);
    freopen("intersect.out","w",stdout);

    n=150;m=11185;
    dp[0][0]=1;
    for(i=0;i<=n;i++){
        for(j=0;j<=m;j++){
            if(dp[i][j]==0) continue;
            for(k=1;(i+k<=n)&&(j+i*k<=m);k++) dp[i+k][j+i*k]=1;
        }
    }

    scanf("%ld",&t);
    for(;t;t--){
        scanf("%ld %ld",&n,&m);
        if(dp[n][m]==0)
            printf("0\n");
        else
            printf("%ld\n",n+m+1);
    }

    return 0;
}
