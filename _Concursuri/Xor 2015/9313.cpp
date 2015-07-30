#include <iostream>
#include <cstdio>

using namespace std;

#define maxS 100000
#define maxPR 10111

long s;
long long i,j;
bool C[maxS+111];
long pr[maxPR];

long long ans;

void make_ciur(){
    long long i,j;
    C[1] = true;
    for(i=2;i<=maxS+15;i++){
        if(C[i]) continue;
        pr[++pr[0]] = i;

        for(j=i*i;j<=maxS;j+=i){
            C[j] = true;
        }
    }
}

int main()
{
    freopen("sprime.in","r",stdin);
    freopen("sprime.out","w",stdout);

    make_ciur();
    scanf("%ld",&s);

    for(i=1;i<=pr[0];i++){
        for(j=i;pr[i]+2*pr[j]<=s;j++){
            long def = s-pr[i]-pr[j];
            if(C[def]==false)
                ans++;
        }
    }

    printf("%lld\n",ans);


    return 0;
}
