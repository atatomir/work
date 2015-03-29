#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 100100

long aint[maxN << 2],a[maxN];
long n,m,i;
long tip,x,y;

void BuildAInt(long nod,long L,long R) {
    if(L == R){
        aint[nod] = a[L];
        return;
    }
    long M = (L+R) >> 1;
    BuildAInt(nod << 1,L,M);
    BuildAInt((nod << 1) + 1,M+1,R);

    aint[nod] = max(aint[nod << 1],aint[(nod << 1)+1]);
}

void Update(long nod,long L,long R,long dest,long val){
    if(L == R){
        aint[nod] = val;
        return;
    }
    long M = (L+R) >> 1;
    if(dest <= M)
        Update(nod << 1,L,M,dest,val);
    else
        Update((nod << 1) + 1,M+1,R,dest,val);
    aint[nod] = max(aint[nod << 1],aint[(nod << 1)+1]);
}

long Query(long nod,long L,long R,long qL,long qR) {
    if(qL <= L && R <= qR) return aint[nod];
    long M = (L+R) >> 1;

    long ans = 0;
    if(qL <= M) ans = max(ans,Query(nod << 1,L,M,qL,qR));
    if(qR > M) ans = max(ans,Query((nod << 1)+1,M+1,R,qL,qR));
    return ans;
}

int main()
{
    freopen("arbint.in","r",stdin);
    freopen("arbint.out","w",stdout);

    scanf("%ld %ld\n",&n,&m);
    for(i=1;i<=n;i++) scanf("%ld",&a[i]);

    BuildAInt(1,1,n);

    for(i=1;i<=m;i++){
        scanf("%ld %ld %ld",&tip,&x,&y);
        if(tip == 0){
            long ans = Query(1,1,n,x,y);
            printf("%ld\n",ans);
        } else {
            Update(1,1,n,x,y);
        }
    }

    return 0;
}
