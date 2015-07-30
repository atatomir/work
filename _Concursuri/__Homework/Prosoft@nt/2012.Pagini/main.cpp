#include <iostream>
#include <cstdio>

using namespace std;

#define maxCf 18

long long def[maxCf+5],ten[maxCf+5];
long long n;
long i,j,sOne;

long long ans,lUsed;

bool isGood(long pos,long val){
    long long used=0;
    used = def[pos-1]*val;
    if(val>1) used += ten[pos];

    used += sOne*val*ten[pos];


    if(used<n) {
        lUsed = used;
        return true;
    }else return false;
}

int main()
{
    freopen("pagini.in","r",stdin);
    freopen("pagini.out","w",stdout);

    scanf("%lld",&n);
    def[1] = ten[1] = 1;
    for(i=2;i<=maxCf;i++) {
        ten[i] = ten[i-1]*10;
        def[i] = def[i-1]*10+ten[i];
    }

    for(i=maxCf;i>1;i--){
        j = 0; lUsed = 0;
        while(j<9&&isGood(i,j+1)) j++;

        n -= lUsed;
        if(j==1) sOne++;

        ans = ans*10+j;
    }

    for(i=0;i<10;i++){
        n -= sOne;
        if(i==1) n--;

        if(n==0){
            printf("%lld",ans*10+i);
            return 0;
        }
    }

    printf("0");

    return 0;
}
