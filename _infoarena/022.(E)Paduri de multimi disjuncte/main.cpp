#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 100010

long Dad[maxN],Bren[maxN];
long i,n,m,op,x,y;

void init(){
    for(long i=1;i<=n;i++) Dad[i]=i,Bren[i]=1;
}

long Merge(long R1,long R2){
    if(Bren[R1] < Bren[R2]){
        Dad[R1] = R2;
        Bren[R2]++;
    } else {
        Dad[R2] = R1;
        Bren[R1]++;
    }
}

long Find(long nod){
    long tmp = nod;
    while(Dad[tmp] != tmp) tmp = Dad[tmp];
    while(tmp != nod){
        long rez = Dad[nod];
        Dad[nod] = tmp;
        nod = rez;
    }
    return nod;
}

int main()
{
    freopen("disjoint.in","r",stdin);
    freopen("disjoint.out","w",stdout);

    scanf("%ld %ld",&n,&m); init();
    for(i=1;i<=m;i++){
        scanf("%ld %ld %ld",&op,&x,&y);
        if(op == 1){
            Merge(Find(x),Find(y));
        } else {
            x = Find(x); y = Find(y);
            if(x == y) printf("DA\n"); else printf("NU\n");
        }
    }

    return 0;
}
