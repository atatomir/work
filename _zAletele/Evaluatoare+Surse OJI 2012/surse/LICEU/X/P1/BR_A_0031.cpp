#include <cstdio>
using namespace std;
long n,k,puncta,punctb,sec[100001],sum[100001],min,poz;
int main()
{
    freopen("calcule.in","r",stdin);
    freopen("calcule.out","w",stdout);
    scanf("%ld%ld",&n,&k);
    punctb=0;
    int i,j,t;
    for(i=1;i<=n;i++){
        scanf("%ld",&t);min=0;
        for(j=1;j<=puncta;j++){if((sec[j]<t)&&(sec[j]>min)){min=sec[j];poz=j;}}
        if(min==0){++puncta;sec[puncta]=t;}
        else{sec[poz]=t;}
        for(j=1;j<=i;j++){sum[j]=(sum[j]+t)%k;if(sum[j]==0){punctb=(punctb+1)%20011;}}
                     }
    printf("%ld %ld",puncta,punctb);
return 0;
}
