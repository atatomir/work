#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define Sym 36

long n,i,x,cont;
vector<long long> V;
long long Freq[Sym + 10];

long f,l1,l2;
long long dp[Sym+10][Sym+10][Sym+10]; // fr l1 l2
long long Ans= 1LL << 60;

bool cmp(long long a,long long b){
    return a > b;
}

int main()
{
    freopen("telegraf.in","r",stdin);
    freopen("telegraf.out","w",stdout);

    for(i=1;i<=Sym;i++){
        scanf("%ld",&x);
        if(!x) continue;
        V.push_back(x); cont++;
    }
    sort(V.begin(),V.end(),cmp);

    Freq[cont] = V[cont-1];
    for(i=cont-1;i;i--) Freq[i] = Freq[i+1] + V[i-1];

    for(f=0;f<=cont;f++)
        for(l1=0;l1<=cont;l1++)
            for(l2=0;l2<=cont;l2++) dp[f][l1][l2] = 1LL << 60;
    dp[0][1][0] = 0;

    for(f=0;f<cont;f++){
        for(l1=0;l1<=cont;l1++){
            for(l2=0;l2<=cont;l2++){
                if(dp[f][l1][l2] == 1LL << 60) continue;
                for(x=0;x<=l1+l2&&x+f<=cont;x++)
                    dp[f+x][l1+l2-x][l1] = min(dp[f][l1][l2] + Freq[f+1],dp[f+x][l1+l2-x][l1]);
            }
        }
    }

    for(l1=0;l1<=cont;l1++)
        for(l2=0;l2<=cont;l2++)
                Ans = min(Ans,dp[cont][l1][l2]);

    printf("%lld",Ans);

    return 0;
}
