#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<long,long> Point;

#define maxN 16010
#define maxM 100010
#define x first
#define y second
#define leftSon (nod << 1)
#define rightSon ((nod << 1)|1)
#define pb push_back

long n,m,i;
vector<long> aint[maxN << 2];
Point p[maxN],p1,p2;


void BuildAInt(long nod,long L,long R){
    if(L == R){
        aint[nod].pb(p[L].y);
        return;
    }
    long M = (L+R) >> 1;
    BuildAInt(leftSon,L,M);
    BuildAInt(rightSon,M+1,R);

    aint[nod].resize(aint[leftSon].size() + aint[rightSon].size());
    merge(aint[leftSon].begin(),aint[leftSon].end(),aint[rightSon].begin(),aint[rightSon].end(),aint[nod].begin());
}

long cbL(long src){
    long i=1,j=n,m;
    do {
        m = (i+j) >> 1;
        if(src <= p[m].x)
            j = m-1;
        else
            i = m+1;
    }   while(i<=j);
    return i;
}

long cbR(long src){
    long i=1,j=n,m;
    do {
        m = (i+j) >> 1;
        if(src < p[m].x)
            j = m-1;
        else
            i = m+1;
    }   while(i<=j);
    return j;
}

long cbnL(long nod,long src){
    long i=0,j=aint[nod].size()-1,m;
    do {
        m = (i+j) >> 1;
        if(src <= aint[nod][m])
            j = m-1;
        else
            i = m+1;
    }   while(i<=j);
    return i;
}

long cbnR(long nod,long src){
    long i=0,j=aint[nod].size()-1,m;
    do {
        m = (i+j) >> 1;
        if(src < aint[nod][m])
            j = m-1;
        else
            i = m+1;
    }   while(i<=j);
    return j;
}

long check(long nod,long L,long R){
    L = cbnL(nod,L);
    R = cbnR(nod,R);
    if(L <= R) return R-L+1;
    return 0;
}

long Query(long nod,long L,long R,long qL,long qR){
    if(qL <= L && R <= qR){
        return check(nod,p1.y,p2.y);
    }
    long M = (L+R) >> 1,ans=0;
    if(qL <= M) ans += Query(leftSon,L,M,qL,qR);
    if(qR >  M) ans += Query(rightSon,M+1,R,qL,qR);
    return ans;
}

int main()
{
    freopen("zoo.in","r",stdin);
    freopen("zoo.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%ld %ld",&p[i].x,&p[i].y);
    sort(p+1,p+n+1);

    BuildAInt(1,1,n);

    scanf("%ld",&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld %ld %ld",&p1.x,&p1.y,&p2.x,&p2.y);
        p1.x = cbL(p1.x);
        p2.x = cbR(p2.x);
        if(p1.x <= p2.x)
            printf("%ld\n",Query(1,1,n,p1.x,p2.x));
        else
            printf("0\n");
    }

    return 0;
}
