#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 15010
#define leftSon (nod << 1)
#define rightSon ((nod << 1)|1)

long n,m,i;
long aint[maxN << 2],v[maxN];
long op,x,y;

void BuildAInt(long nod,long L,long R) {
    if(L == R) {
        aint[nod] = v[L];
        return;
    }
    long M = (L+R) >> 1;
    BuildAInt(leftSon,L,M);
    BuildAInt(rightSon,M+1,R);

    aint[nod] = aint[leftSon] + aint[rightSon];
}

void Update(long nod,long L,long R,long dest,long val){
    aint[nod] -= val;
    if(L == R) return;
    long M = (L+R) >> 1;
    if(dest <= M)
        Update(leftSon,L,M,dest,val);
    else
        Update(rightSon,M+1,R,dest,val);
}

long Query(long nod,long L,long R,long qL,long qR){
    if(qL <= L && R <= qR) return aint[nod];
    long M = (L+R) >> 1,ans =0;
    if(qL <= M ) ans += Query(leftSon,L,M,qL,qR);
    if(M  <  qR) ans += Query(rightSon,M+1,R,qL,qR);
    return ans;
}

int main()
{
    freopen("datorii.in","r",stdin);
    freopen("datorii.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++) scanf("%ld",&v[i]);

    BuildAInt(1,1,n);

    for(i=1;i<=m;i++){
        scanf("%ld %ld %ld",&op,&x,&y);
        if(op == 0){
            Update(1,1,n,x,y);
        } else {
            printf("%ld\n",Query(1,1,n,x,y));
        }
    }
    return 0;
}
