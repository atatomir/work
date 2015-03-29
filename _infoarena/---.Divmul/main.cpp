#include <iostream>
#include <cstdio>

using namespace std;

#define maxVal 10000
#define maxCiur 1500

long t,test,x,y,i,l1,l2;
long long cnt;

bool ciur[maxVal+11];
long pr[maxCiur];

void make_ciur(){
    for(long i=2;i*i<=maxVal;i++){
        if(ciur[i]) continue;
        for(long j=i*i;j<=maxVal;j+=i) ciur[j]=true;
    }
    for(i=2;i<=maxVal;i++)
        if(ciur[i]==0) pr[++pr[0]] = i;
}

int main()
{
    freopen("divmul.in","r",stdin);
    freopen("divmul.out","w",stdout);

    make_ciur();

    scanf("%ld",&test);
    for(;test;test--){
        scanf("%ld%ld",&x,&y);
        cnt = 1;
        if(x>y){t=x;x=y;y=t;}
        for(i=1;pr[i]*pr[i]<=y;i++){
            if(x%pr[i]==0 || y%pr[i]==0){
                l1=l2=0;
                while(x%pr[i]==0){l1++; x/=pr[i];}
                while(y%pr[i]==0){l2++; y/=pr[i];}

                if(l1>l2) {cnt=0;break;}
                if(l1!=l2) cnt<<=1;
            }
        }
        if(x!=1||y!=1){
            if(x!=y){
                if(x!=1) cnt<<=1;
                if(y!=1) cnt<<=1;
            }
        }

        printf("%lld\n",cnt);
    }


    return 0;
}
