#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 1000011
#define act dp[i]

long n,i,aux;
char tmp[maxN],s[maxN<<1];
long dp[maxN<<1];
long long Ans;

long C,fC;

int main()
{
    freopen("pscpld.in","r",stdin);
    freopen("pscpld.out","w",stdout);

    scanf("%s",tmp+1); aux = 0;
    s[0] = '@';
    for(n=1;tmp[n];n++){
        s[++aux] = tmp[n];
        s[++aux] = ',';
    }
    s[aux--] = '#'; n--;

    C = fC = 0;
    for(i=1;i<=aux;i++){
        if(i <= fC) dp[i] = min(fC-i,dp[2*C-i]);
        for(;s[i-act-1] == s[i+act+1];act++);

        if(i&1)
            Ans += act/2 + 1;
        else
            Ans += (act+1)/2;

        if(i+act > fC){
            fC = i+act; C = i;
        }
    }

    printf("%lld\n",Ans);

    //for(i=1;i<=aux;i++) printf("%c",s[i]); printf("\n");
    //for(i=1;i<=aux;i++) printf("%ld",dp[i]); printf("\n");

    return 0;
}
