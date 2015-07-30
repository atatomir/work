#include <iostream>
#include <cstdio>

using namespace std;

//#define DEBUG
#define maxN 2011

long n,m,i,j,p,x,pos;
bool t[maxN][maxN];
long pct[maxN],solved[maxN];
long valoare[maxN];

int main()
{
    #ifdef DEBUG
    freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld %ld %ld",&n,&m,&p);
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            scanf("%ld",&x);
            t[i][j] = x;
            if(!x) pct[j]++;
        }
    }

    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            if(!t[i][j]) continue;
            valoare[i] += pct[j];
            solved[i]++;
        }
    }

    pos=1;
    for(i=1;i<=n;i++){
        if(i==p) continue;
        if(valoare[i]<valoare[p])continue;
        if(valoare[i]>valoare[p]) pos++;
        if(valoare[i]==valoare[p]){
            if(solved[i]<solved[p]) continue;
            if(solved[i]>solved[p]) pos++;
            if(solved[i]==solved[p]){
                if(i<p) pos++;
            }
        }
    }

    printf("%ld %ld",valoare[p],pos);

    return 0;
}
