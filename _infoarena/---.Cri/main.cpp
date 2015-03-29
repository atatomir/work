#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 505

long n,m,x,y,i,j;
long sum[maxN][maxN],a[maxN][maxN];

struct {
    long Z=0,T=0,K=0;
} ans;

void check(long Z,long T,long K){
    if((T > ans.T)||((T == ans.T)&&(K < ans.K))){
        ans.Z = Z;
        ans.T = T;
        ans.K = K;
    }
}

void Try(long i,long j,long i2,long j2,long edge) {
    long poss=0,dim=(i2-i+1)*(j2-j+1),minim=a[i][j+1],x,y,targ;
    if(((i2-i+1) % 2 != 0)||((j2-j+1) % 2 != 0)){
        poss = sum[i2][j2] - sum[i-1][j2] - sum[i2][j-1] + sum[i-1][j-1];
        check(edge,poss,dim);
    } else {
        if((edge == 1)||(edge == 4)) targ = 1; else targ = 0;

        poss = sum[i2][j2] - sum[i-1][j2] - sum[i2][j-1] + sum[i-1][j-1];
        for(x=i;x<=i2;x++){
            for(y=j;y<=j2;y++){
                if((x-i+y-j)% 2 == targ) minim = min(minim,a[x][y]);
            }
        }
        check(edge,poss-minim,dim-1);
    }
}

int main()
{
    freopen("cri.in","r",stdin);
    freopen("cri.out","w",stdout);

    scanf("%ld %ld %ld %ld\n",&n,&m,&x,&y);
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            scanf("%ld",&sum[i][j]);
            a[i][j] = sum[i][j];
            sum[i][j] += sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
        }
    }

    Try(1,1,x,y,1);
    Try(1,y,x,m,2);
    Try(x,1,n,y,3);
    Try(x,y,n,m,4);

    printf("%ld %ld %ld\n",ans.Z,ans.T,ans.K);

    return 0;
}
