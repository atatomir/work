#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 22
#define maxVar 22*22
#define id(a,b) idd[a][b]
#define eps 0.0000001

long n,m,i,j,k,l,nr;
double ec[maxVar][maxVar],aux;
double ans[maxVar];
long idd[maxN+10][maxN+10];

void debug(){
    long i,j;
    printf("\n");
    for(i=1;i<=nr;i++){
        for(j=1;j<=nr+1;j++) printf("%lf ",ec[i][j]);
        printf("\n");
    }
}

void Gauss(){
    i=1;j=1;
    while(i<=nr&&j<=nr){
        for(k=i;k<=nr;k++)
            if(ec[k][j]<-eps||ec[k][j]>eps) break;

        if(k>nr) {j++; continue;}
        for(l=1;l<=nr;l++){aux = ec[i][l]; ec[i][l] = ec[k][l]; ec[k][l] = aux;}

        for(k=j+1;k<=nr+1;k++) ec[i][k] /= ec[i][j]; ec[i][j] = 1.00;
        for(k=i+1;k<=nr;k++){
            for(l=j+1;l<=nr+1;l++) ec[k][l] -= ec[k][j]*ec[i][l];
            ec[k][j] = 0.00;
        }

        i++; j++;
    }

    for(i=nr;i;i--){
        for(j=1;j<=nr+1;j++){
            if(ec[i][j]>-eps && ec[i][j]<eps) continue;
            ans[j] = ec[i][nr+1];
            for(l=j+1;l<=nr;l++) ans[j] -= ec[i][l]*ans[l];

            break;
        }
    }
}

int main()
{
    freopen("minesweeper.in","r",stdin);
    freopen("minesweeper.out","w",stdout);

    scanf("%ld %ld",&n,&m); n *= m;
    for(i=0;i<=n;i++)
        for(j=0;j+i<=n;j++) {
            id(i,j) = ++nr;
        }

    for(long a=0;a<=n;a++){
        for(long b=0;b+a<=n;b++){
            long c = n-a-b;
            if(a==n&&b==0){
                ec[id(a,b)][id(a,b)] = 1.00;
                continue;
            }

            ec[id(a,b)][id(a,b)] = 1.00;
            if(b)ec[id(a,b)][id(a+1,b-1)] = (double)-b/n;
            if(c)ec[id(a,b)][id(a,b+1)] = (double)-c/n;
            if(a)ec[id(a,b)][id(a-1,b)] = (double)-a/n;
            ec[id(a,b)][nr+1] = 1.00;
        }
    }

    Gauss();

    printf("%.6lf",ans[id(0,0)]);
    return 0;
}
