#include <iostream>
#include <cstdio>

using namespace std;

//#define DEBUG
#define maxN 3011

long n,m,h,w,i,j,mid,how;
long a[maxN][maxN],def[maxN][maxN];

bool allLess(long lim){
    long i,j;

    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            def[i][j]  = (a[i][j]<lim?1:0);
            def[i][j] += def[i-1][j]+def[i][j-1]-def[i-1][j-1];

            if(i<h) continue;
            if(j<w) continue;
            if(def[i][j]-def[i][j-w]-def[i-h][j]+def[i-h][j-w] > how ) return false;
        }
    }

    return true;
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld %ld %ld %ld",&n,&m,&h,&w);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            scanf("%ld",&a[i][j]);

    how = (h*w)>>1;
    i = 1; j = n*m;
    while(i<=j){
        mid = (i+j)>>1;
        if(allLess(mid))
            i = mid+1;
        else
            j = mid-1;
    }

    printf("%ld",j);

    return 0;
}
