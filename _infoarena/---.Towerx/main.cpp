#include <iostream>
#include <cstdio>

using namespace std;

//! dp[k][i] - pozitia pe care apare prima oara i intr-un sir de dimensiune k. 
//! dp[k][i] = dp[k  ][i-1] (cand apare elementul i-1) +
//!            dp[k-1][i-1] (cand in sirul ramas ar trebui sa apara elementul i-1 )
//! deoarece elementul i-1 deja exista va aparea elementul i de care avem nevoie
//! Atentie ! Dupa asezarea elementului i-1 se vor aseza inca i-2 elemente fara a il muta pe i-1. 

#define maxN 10011

long n,i,j;
long dp[2][maxN],s=0,d=1;
long wh[maxN],ans[maxN];

int main()
{
    freopen("towerx.in","r",stdin);
    freopen("towerx.out","w",stdout);

    scanf("%ld",&n);
    wh[1] = 1;

    dp[s][1] = 1;
    for(i=2;i<=n;i++){
        dp[d][1] = 1;
        for(j=2;j<=i;j++) {
            dp[d][j] = dp[d][j-1]+dp[s][j-1];
            if(dp[d][j]>i) dp[d][j]-=i;
        }

        wh[i] = dp[d][i];
        s ^= 1; d ^= 1;
    }

    j=1;
    for(i=n;i;i--){
        long cnt = wh[i];

        while(ans[j]) if(++j >n) j=1;
        cnt--;
        while(cnt){
            if(++j >n) j=1;
            while(ans[j]) if(++j >n) j=1;
            cnt--;
        }
        ans[j]=i;
    }

    for(i=1;i<=n;i++) printf("%ld ",ans[i]);


    return 0;
}
