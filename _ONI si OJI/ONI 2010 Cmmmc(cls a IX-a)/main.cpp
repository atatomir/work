#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

long k,n,i,cont,nn;
pair<long,long> Div[30];
long val[30];
long long count;

long sumMin,aMin,bMin;

map<long,pair<pair<long long,long>,long> > M;

void back(long pos,long a,long ksel,long prod){
    if(pos > cont){
        if(ksel == 0) ksel++;
        count += (1LL << (ksel-1))*prod;
        long b = n/a;
        if(a+b < sumMin) {
            sumMin = a+b;
            aMin = a; bMin = b;
        }
        return;
    }

    back(pos+1,a,ksel+1,prod*Div[pos].second);
    back(pos+1,a*val[pos],ksel,prod);
}

int main()
{
    freopen("cmmmc.in","r",stdin);
    freopen("cmmmc.out","w",stdout);

    scanf("%ld",&k);
    for(;k;k--){
        scanf("%ld",&n); cont = 0; count = 0; sumMin = n+2;

        if(M.count(n)){
            printf("%lld %ld %ld\n",M[n].first.first,M[n].first.second,M[n].second);
            continue;
        }

        nn = n;
        for(i=2;i*i<=nn;i++){
            if(nn % i == 0){
                cont++;
                Div[cont].first = i;
                Div[cont].second = 0;
                val[cont] = 1;
                while(nn % i == 0) {
                    val[cont] *= i;
                    nn /= i;
                    Div[cont].second++;
                }
            }
        }
        if(nn != 1) {
                    Div[++cont].first = nn;
                    Div[cont].second = 1;
                    val[cont] = nn;
        }

        back(1,1,0,1);
        if(aMin > bMin) {cont=aMin;aMin=bMin;bMin=cont;}
        printf("%lld %ld %ld\n",count,aMin,bMin);
        M[n] = make_pair(make_pair(count,aMin),bMin);
    }

    return 0;
}
