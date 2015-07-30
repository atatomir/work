#include <iostream>
#include <cstdio>

using namespace std;

typedef pair<char,pair<long,long> > Switch;

#define type first
#define left second.first
#define right second.second
#define maxN 500011

long long B[maxN];
long n,i;
Switch Nodes[maxN];
long par[maxN];

void Dfs(long nod){
    if(B[nod]&1){
        if(Nodes[nod].type == 'L') B[Nodes[nod].left]++; else B[Nodes[nod].right]++;
    }
    if(B[nod]&1){
        if(Nodes[nod].type == 'L') Nodes[nod].type = 'R'; else Nodes[nod].type = 'L';
    }

    par[Nodes[nod].left]--; B[Nodes[nod].left]+= B[nod]/2;
    if(!par[Nodes[nod].left]) Dfs(Nodes[nod].left);

    par[Nodes[nod].right]--; B[Nodes[nod].right]+= B[nod]/2;
    if(!par[Nodes[nod].right]) Dfs(Nodes[nod].right);
}


int main()
{
    freopen("digicomp2.in","r",stdin);
    freopen("digicomp2.out","w",stdout);

    par[0] = maxN;
    scanf("%ld %ld\n",&B[1],&n);
    for(i=1;i<=n;i++){
        scanf("%c %ld %ld\n",&Nodes[i].type,&Nodes[i].left,&Nodes[i].right);
        par[Nodes[i].left]++; par[Nodes[i].right]++;
    }

    Dfs(1);

    for(i=1;i<=n;i++) printf("%c",Nodes[i].type);

    return 0;
}
