#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 32011

long n,m,i,j,k,x,cnt;
vector<long> list[maxN];

bool arb[maxN<<2];
long sum[maxN<<2],wh[maxN];
long zz[maxN<<2];

void Liniarizare(long node){
    arb[++cnt] = true;

    for(vector<long>::iterator it=list[node].begin();it!=list[node].end();it++)
        Liniarizare(*it);

    arb[++cnt] = false;
}

void LiniarizareExp(long node){
    arb[++cnt] = true; wh[node] = cnt;

    for(vector<long>::iterator it=list[node].begin();it!=list[node].end();it++)
        LiniarizareExp(*it);

    arb[++cnt] = false;
}

void makeZ(){
    long i,bg,en=0;

    for(i=2;i<=cnt;i++){
        if(en>=i) zz[i] = min(en-i+1,zz[i-bg+1]);
        while(arb[i+zz[i]] == arb[zz[i]+1]) zz[i]++;

        zz[i] = min(zz[i],2*n);
        if(en < i + zz[i]-1){
            bg = i; en = i+zz[i]-1;
        }
    }
}

int main()
{
    freopen("arbfind.in","r",stdin);
    freopen("arbfind.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld",&k); list[i].clear();
        for(j=1;j<=k;j++){
            scanf("%ld",&x);
            list[i].push_back(x);
        }
    }
    Liniarizare(1);

    scanf("%ld",&m);
    for(i=1;i<=m;i++){
        scanf("%ld",&k); list[i].clear();
        for(j=1;j<=k;j++){
            scanf("%ld",&x);
            list[i].push_back(x);
        }
    }
    LiniarizareExp(1);

    for(i=wh[1];i<=cnt;i++) sum[i] = sum[i-1] + (arb[i]?1:0);

    makeZ();
    for(i=1;i<=m;i++){
        long bg = wh[i];
        long en = bg + zz[bg] - 1;

        printf("%ld\n",sum[en]-sum[bg-1]);
    }

    return 0;
}
