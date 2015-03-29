#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 1000011

long cnt[maxN];
long x,y,i;

long getInd(long a,long b){
    long ans = 0,def=b;
    while(a%b==0){
        ans++;
        b*= def;
    }
    return ans;
}

void make_ciur(long lim){
    long i,j;
    for(i=1;i<=lim;i++) cnt[i] = 1;
    for(i=2;i<=lim;i++){
        if(cnt[i]>1) continue;
        cnt[i]=2;

        long actInd;
        for(j=2*i;j<=lim;j+=i){
            actInd = getInd(j,i);
            cnt[j] *= (actInd+1);
        }
    }

    for(i=1;i<=lim;i++){
        if(i%cnt[i]==0) cnt[i]=1; else cnt[i] = 0;
        cnt[i] += cnt[i-1];
    }
}

int main()
{
    freopen("magicnum.in","r",stdin);
    freopen("magicnum.out","w",stdout);

    scanf("%ld %ld",&x,&y);
    make_ciur(y);
    printf("%ld",cnt[y]-cnt[x-1]);

    return 0;
}
