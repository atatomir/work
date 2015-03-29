#include <iostream>
#include <cstdio>

using namespace std;

long n,i,j;
long S[1024],a[10];

long cnt,best,bestI,bestJ;

void Try(long pas,long mask,long sum){
    if(pas == 10){
        S[mask] = sum;
        return ;
    }

    Try(pas+1,mask,sum);
    Try(pas+1,mask|(1<<pas),sum+a[pas]);
}

void write(long mask){
    for(long i=0;i<10;i++){
        if(mask&(1<<i)) printf("%ld ",a[i]);
    }
}

int main()
{
    freopen("numere8.in","r",stdin);
    freopen("numere8.out","w",stdout);

    for(i=0;i<10;i++) scanf("%ld",&a[i]);
    Try(0,0,0);

    cnt = best = bestI = bestJ = 0;

    for(i=0;i<1024;i++){
        for(j=i+1;j<1024;j++){
            if(i&j) continue;
            if(S[i]!=S[j]) continue;

            cnt++;
            if(S[i] > best){
                best = S[i];
                bestI = i; bestJ = j;
            }
        }
    }

    printf("%ld %ld\n",cnt,best);
    write(bestI); printf("\n");
    write(bestJ);

    return 0;
}
