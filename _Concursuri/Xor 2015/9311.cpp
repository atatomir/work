#include <iostream>
#include <cstdio>

using namespace std;

long t,n,i,j,p,nn,k;

int main()
{
    freopen("punctul.in","r",stdin);
    freopen("punctul.out","w",stdout);

    scanf("%ld",&t);
    if(t==1){
        scanf("%ld",&n);
        if(n==0){
            printf("0 0\n");
            return 0;
        }

        p=1; nn=n;
        while(p*2+1<nn){nn-=2*p+1;p++;}
        i=p;j=0;
        if(nn<=p+1) {
            j += nn-1;
        } else {
            i = p;
            j = p; nn -= p+1;
            while(nn) {nn--;i--;}
        }
        if(p%2==0) printf("%ld %ld\n",j,i); else printf("%ld %ld\n",i,j);

    } else {
        scanf("%ld %ld",&i,&j);
        if(i==j && i==0){
            printf("0\n");
            return 0;
        }

        p = max(i,j); nn = 0;
        for(k=1;k<p;k++) nn += 2*k+1;

        if(p%2==0) {k=i;i=j;j=k;}
        if(i==p){
            nn += j+1;
        } else {
            nn += p+1;
            k = p; while(k!=i) {nn++; k--;}
        }

        printf("%ld\n",nn);
    }


    return 0;
}
