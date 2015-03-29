#include <iostream>
#include <cstdio>

using namespace std;

long long c[11100][37];
long long n,k,s,a[30][40],i,j,rez;
long v[35];
long long mod = 3210121;

inline void initializate() {
    long n = 11050,m=32,i,j;
    for(i=1;i<=n;i++) c[i][1] = 1LL*i;
    for(i=2;i<=n;i++)
        for(j=2;j<=min(m,i);j++)
            c[i][j] = (c[i-1][j-1]+c[i-1][j])% mod;

    for(j=1;j<=m;j++){
        for(i=j+1;i<=n;i++) c[i][j] = (c[i][j] + c[i-1][j]) % mod;
    }
}

void Back(long pas,long sel,long vs[35]){
    long i,v[35];
    long long sl;
    for(i=1;i<=k;i++) v[i] = vs[i];

    if(pas > n){
        sl = s;
        for(i=1;i<=k;i++) sl= sl-v[i];
        if(sl < 0) return;


        /*for(i=1;i<=k;i++) printf("%ld ",v[i]);
        printf("\n%ld\n\n",sl);*/

        if(sel % 2 == 0)
            rez = rez + c[sl+k-1][k-1];
        else{
            rez = rez - c[sl+k-1][k-1];
            if(rez < 0) rez = rez+ mod;
        }

        if(rez >= mod) rez = rez - mod;
    } else {
        Back(pas+1,sel,v);

        for(i=1;i<=k;i++){
            if(v[i] < a[pas][i]){
                v[i] = a[pas][i];
            }
        }
        Back(pas+1,sel+1,v);
    }
}

int main()
{
    freopen("cowfood.in","r",stdin);
    freopen("cowfood.out","w",stdout);

    initializate();

    scanf("%lld %lld %lld\n",&k,&s,&n);
    // k e nr de ierburi, n e nr de amestecuri
    for(i=1;i<=n;i++){
        for(j=1;j<=k;j++) scanf("%lld",&a[i][j]);
    }

    rez = 0;
    Back(1,0,v);

    rez = rez - k*s - 1;
    while(rez < 0) rez = rez + mod;

    printf("%lld",rez% mod);

    return 0;
}
