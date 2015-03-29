#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define maxM 200011
#define maxN 100011

struct Edge{
    long x,y,v;
};
bool cmp(const Edge& a,const Edge& b){
    return a.v<b.v;
}

long n,m,k,i;
Edge e[maxM];
bool used[maxM];

long par[maxN],ram[maxN];

long Find(long node){
    long rez = node;
    while(par[node]!=node) node = par[node];
    while(rez!=par[rez]){
        long tmp = par[rez];
        par[rez] = node;
        rez = tmp;
    }
    return node;
}
void Merge(long r1,long r2){
    if(ram[r1]>ram[r2]){
        par[r2]=r1;
        ram[r1]++;
    } else {
        par[r1]=r2;
        ram[r2]++;
    }
}

int main()
{
    freopen("karb.in","r",stdin);
    freopen("karb.out","w",stdout);

    scanf("%ld %ld %ld",&n,&m,&k);
    for(i=1;i<=m;i++)scanf("%ld%ld%ld",&e[i].x,&e[i].y,&e[i].v);
    sort(e+1,e+m+1,cmp);

    for(i=1;i<=n;i++) par[i]=i;
    for(i=1;i<=m;i++){
        used[i]=false;
        long R1 = Find(e[i].x);
        long R2 = Find(e[i].y);
        if(R1==R2) continue;
        Merge(R1,R2);
        if(e[i].v)used[i]=true;
    }

    for(i=1;i<=n;i++){ par[i]=i; ram[i]=0;}
    for(i=1;i<=m;i++){
        if(!used[i]) continue;
        long R1 = Find(e[i].x);
        long R2 = Find(e[i].y);
        Merge(R1,R2); k--;
    }

    for(i=m;i;i--){
        if(used[i]) continue;
        if(k==0 && e[i].v==1) continue;

        long R1 = Find(e[i].x);
        long R2 = Find(e[i].y);
        if(R1==R2) continue;
        Merge(R1,R2);
        if(e[i].v==1) k--;
        used[i]=true;
    }

    for(i=1;i<=m;i++)
        if(used[i])
            printf("%ld %ld\n",e[i].x,e[i].y);

    return 0;
}
