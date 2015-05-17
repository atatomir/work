#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxN 85
#define maxDim 23

long n,i,j,s,d,c,p,h2,h5,u;
long long cnt,p2[maxDim],p5[maxDim];
long long dp[maxN][maxN<<1][maxN<<1];

void preProc(){
    for(long val=1;val<=200;val++){
        long h = val;
        long pp2 = 0;
        while(h%2==0) {pp2++; h/=2;}
        long pp5 = 0;
        while(h%5==0) {pp5++; h/=5;}

        if(h!=1) continue;
        cnt++;
        p2[cnt] = pp2;
        p5[cnt] = pp5;
    }
}

int main()
{
    freopen("procente.in","r",stdin);
    freopen("procente.out","w",stdout);

    preProc();
    scanf("%ld\n%c%ld",&n,&c,&p);
    if(c=='-') p = 100-p; else p+=100;

    h2 = 0;
    while((p&1)==0) {h2++; p>>=1;}
    while(p%5==0)   {h5++; p /=5;}
    if(p!=1){
        printf("0");
        return 0;
    }

    h2 = 2*n-h2;
    h5 = 2*n-h5;

    dp[0][0][0]=1;
    for(u=1;u<=cnt;u++){
        long add2 = p2[u];
        long add5 = p5[u];

        for(i=0;i<n;i++)
            for(long ph2=0;ph2<=h2-add2;ph2++)
                for(long ph5=0;ph5<=h5-add5;ph5++)
                    dp[i+1][ph2+add2][ph5+add5] += dp[i][ph2][ph5];
    }

    printf("%lld",dp[n-1][h2][h5]);

    return 0;
}
