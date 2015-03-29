#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define cost first
#define n1 second.first
#define n2 second.second
#define maxN 200010
#define cEdge aEdges[i]

typedef pair<long,pair<long,long> > Edge;

long n,m,i,R1,R2;
vector<Edge> G;
long Dad[maxN],Bren[maxN];
Edge tmp;

long ans;
vector<long> aEdges;

void init(){
    for(long i=1;i<=n;i++) Dad[i] = i,Bren[i]=1;
}

long Find(long nod){
    long loc = nod;
    while(Dad[loc] != loc) loc = Dad[loc];
    while(loc != nod){
        long temp = Dad[nod];
        Dad[nod] = loc;
        nod = temp;
    }
    return nod;
}

void Merge(long R1,long R2){
    if(Bren[R1] < Bren[R2]){
        Dad[R1] = R2;
        Bren[R2]++;
    } else {
        Dad[R2] = R1;
        Bren[R1]++;
    }
}

int main()
{
    freopen("apm.in","r",stdin);
    freopen("apm.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++) {
        scanf("%ld %ld %ld",&tmp.n1,&tmp.n2,&tmp.cost);
        G.push_back(tmp);
    }

    init();
    sort(G.begin(),G.end());
    for(i=0;i<G.size();i++){
        tmp = G[i];
        R1 = Find(tmp.n1); R2 = Find(tmp.n2);
        if(R1 == R2) continue;
        Merge(R1,R2);
        ans += tmp.cost;
        aEdges.push_back(i);
    }

    printf("%ld\n%ld\n",ans,aEdges.size());
    for(i=0;i<aEdges.size();i++) printf("%ld %ld\n",G[cEdge].n1,G[cEdge].n2);

    return 0;
}
