#include <iostream>
#include <cstdio>

using namespace std;

#define maxD 11
#define maxN 25

long n,k,d,i,co,def,x;
long mask[maxN],v[maxD];

inline void foundSol(){
    for(long i=1;i<=k;i++) printf("%ld ",v[i]);
    printf("\n");
}

void Try(long pos,long act){
    long i;
    if(pos > k){
        if(!act) foundSol();
        return;
    }

    long need = (k-pos+1);
    need = n-need+1;
    for(i=v[pos-1]+1;i<=need;i++){
        v[pos] = i;
        Try(pos+1,act&mask[i]);
    }
}

int main()
{
    freopen("pluricex.in","r",stdin);
    freopen("pluricex.out","w",stdout);

    scanf("%ld %ld %ld",&n,&k,&d);
    def = (1<<d)-1;
    for(i=1;i<=n;i++){
        scanf("%ld",&co);
        mask[i] = def;
        for(;co;co--){
            scanf("%ld",&x); x--;
            mask[i] ^= 1<<x;
        }
    }

    v[0] = 0;
    Try(1,def);

    return 0;
}
