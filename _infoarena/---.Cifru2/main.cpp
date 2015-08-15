#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 100011
#define maxM  10011

int n,m,i;
int A[maxN<<2],B[maxN<<2]; //! by default
int _A[maxN<<2],_B[maxN<<2]; //! with distances
int aux[maxM];
int pr[maxN<<2];
int ans[maxM];

void getArray( int dim,int* S,int* D ){
    int i;

    memset(aux,0,sizeof(aux));
    for (i=dim;i>0;i--){
        int from = aux[ S[i] ];

        if (from==0){
            D[i] = 0;
        } else {
            D[i] = from-i;
        }

        aux[ S[i] ] = i;
    }
}

int KMP(int *_big,int *_small){
    int i,u;

    pr[1] = 0; u = 0;
    for (i=2;i<=n;i++) {
        while (u>0 && _small[u+1]!=_small[i]) u = pr[u];
        if (_small[u+1] == _small[i]) u++;
    }

    u=0;
    for (i=1;i<=2*n;i++) {
        while (u>0 && _small[u+1]!=_big[i]) u = pr[u];
        if (_small[u+1] == _big[i]) u++;

        if (u==n) return i-n;
    }
}

int main()
{
    freopen("cifru2.in","r",stdin);
    freopen("cifru2.out","w",stdout);

    scanf("%d%d",&n,&m);
    for (i=1;i<=n;i++) scanf("%d",&A[i]);
    for (i=1;i<=n;i++) scanf("%d",&B[i]);

    for (i=n+1;i<=3*n;i++){
        int source = i%n;
        if (source==0) source = n;

        A[ i ] = A[ source ];
        B[ i ] = B[ source ];
    }

    getArray(3*n,A,_A);
    getArray(3*n,B,_B);

    int pos = KMP(_B,_A);
    for (i=1;i<=n;i++) B[i] = B[i+pos];
    for (i=1;i<=n;i++) ans[ A[i] ] = B[i];

    printf("%d\n",pos);
    for (i=1;i<=m;i++) printf("%d ",ans[i]);

    return 0;
}
