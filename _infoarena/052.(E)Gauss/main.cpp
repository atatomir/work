#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

// M necunoscute si N ecuatii
#define maxN 311
#define eps 0.0000000001

long n,m,i,j,k,l;
vector<double> ec[maxN],tmp;
double ans[maxN];

int main()
{
    freopen("gauss.in","r",stdin);
    freopen("gauss.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++){
        ec[i].resize(m+2);
        for(j=1;j<=m+1;j++) scanf("%lf",&ec[i][j]);
    }

    i=1;j=1;
    while(i<=n&&j<=m){
        for(k=i;k<=n;k++)
            if(ec[k][j]<-eps || ec[k][j]>eps) break;

        if(k==n+1){ j++; continue;}
        if(k!=i){
            tmp = ec[i]; ec[i] = ec[k]; ec[k] = tmp;
        }

        for(k=j+1;k<=m+1;k++) ec[i][k] /= ec[i][j];
        ec[i][j] = 1;

        for(k=i+1;k<=n;k++){
            if(ec[k][j]>-eps && ec[k][j]<eps) continue;
            for(l=j+1;l<=m+1;l++) ec[k][l] -= ec[i][l]*ec[k][j];
            ec[k][j] = 0;
        }

        i++; j++;
    }

    for(i=n;i;i--){
        for(j=1;j<=m+1;j++){
            if(ec[i][j]>-eps && ec[i][j]<eps) continue;
            if(j==m+1){
                printf("Imposibil");
                return 0;
            }

            ans[j] = ec[i][m+1];
            for(k=j+1;k<=m;k++) ans[j] -= ec[i][k]*ans[k];

            break;
        }
    }

    for(i=1;i<=m;i++) printf("%.11lf ",ans[i]);

    return 0;
}
