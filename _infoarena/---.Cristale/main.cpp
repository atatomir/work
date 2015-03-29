#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 111

char a,b,c;
long t,n;
char s[maxN];

long solve(){
    long cntA=0,cntB=0,cntC=0;
    for(long i=1;i<=n;i++){
        if(s[i]==a) cntA++;
        if(s[i]==b) cntB++;
        if(s[i]==c) cntC++;
    }

    if((cntA|cntB)==0) return n;
    if((cntC|cntB)==0) return n;
    if((cntA|cntC)==0) return n;
    if(cntA&cntB&cntC&1) return 2;
    if(!((cntA|cntB|cntC)&1)) return 2;
    return 1;
}

int main()
{
    freopen("cristale.in","r",stdin);
    freopen("cristale.out","w",stdout);

    scanf("%c %c %c\n",&a,&b,&c);
    scanf("%ld\n",&t);
    for(;t;t--){
        scanf("%ld %s\n",&n,s+1);
        printf("%ld\n",solve());
    }


    return 0;
}
