#include <iostream>
#include <cstdio>

using namespace std;

long long X,Y;
long long a,b,i,val;

long long sMin=1LL << 62,aMin,bMin;

int main()
{
    freopen("taste.in","r",stdin);
    freopen("taste.out","w",stdout);

    scanf("%lld %lld",&X,&Y);
    for(a=1LL<<60,i=60;a;a>>=1,i--){

        b = X / a;
        if(a*b < X) b++;
        if(a*b <= Y){
            val = i + b;
            if(val <= sMin){
                sMin = val;
                aMin = i; bMin = b;
            }
        }
    }
    printf("%lld %lld",bMin,aMin);

    return 0;
}
