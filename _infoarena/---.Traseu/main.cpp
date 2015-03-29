#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

#define maxN 64
#define INF 1000000000

long n,m,i,j,k,x,y,c,S,D;
long grIn[maxN],grOut[maxN];
long roy[maxN][maxN];

vector<long> mLeft,mRight;
long C[maxN][maxN],F[maxN][maxN];
long pay[maxN][maxN];
vector<long> list[maxN];

bool inQueue[maxN];
long prov[maxN],bCost[maxN];
queue<long> Q;
long long Ans;

void RoyFloyd(){
    long i,j,k;
    for(k=1;k<=n;k++)
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                if(i!=j&&i!=k&&j!=k && roy[i][k]+roy[k][j]<roy[i][j])
                    roy[i][j]=roy[i][k]+roy[k][j];
}

bool bellman(){
    for(i=S;i<=D;i++) bCost[i]=INF;
    memset(prov,0,sizeof(prov));
    memset(inQueue,0,sizeof(inQueue));

    inQueue[S]=true; Q.push(S);
    bCost[S] = 0;

    while(!Q.empty()){
        long node = Q.front(); Q.pop();
        inQueue[node] = false;

        for(i=0;i<list[node].size();i++){
            long newNode = list[node][i];
            long newCost = bCost[node]+pay[node][newNode];

            if(C[node][newNode]==F[node][newNode] || newCost >= bCost[newNode] ) continue;
            bCost[newNode] = newCost;
            if(!inQueue[newNode]){
                Q.push(newNode);
                inQueue[newNode] = true;
            }
            prov[newNode] = node;
        }
    }

    if(bCost[D]==INF) return false;

    long flux=INF;
    for(long node=D;node!=S;node=prov[node]) flux=min(flux,C[prov[node]][node]-F[prov[node]][node]);
    for(long node=D;node!=S;node=prov[node]) {
        F[prov[node]][node] += flux;
        F[node][prov[node]] -= flux;
    }
    Ans = Ans + flux*bCost[D];

    return true;
}

int main()
{
    freopen("traseu.in","r",stdin);
    freopen("traseu.out","w",stdout);

    scanf("%ld%ld",&n,&m);
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++) roy[i][j]=INF;

    for(i=1;i<=m;i++){
        scanf("%ld %ld %ld",&x,&y,&c);
        grOut[x]++; grIn[y]++;
        roy[x][y] = c; Ans += c;
    }

    RoyFloyd();
    for(i=1;i<=n;i++){
        if(grIn[i]>grOut[i]) mLeft.push_back(i);
        if(grIn[i]<grOut[i]) mRight.push_back(i);
    }
    S=0; D=n+1;

    for(i=0;i<mLeft.size();i++){
        long node = mLeft[i];
        long how = grIn[node]-grOut[node];

        list[S].push_back(node);
        list[node].push_back(S);
        C[S][node] = how;
        //!pay==0
    }
    for(i=0;i<mRight.size();i++){
        long node = mRight[i];
        long how = grOut[node]-grIn[node];

        list[node].push_back(D);
        list[D].push_back(node);
        C[node][D] = how;
        //!pay==0
    }
    for(i=0;i<mLeft.size();i++){
        for(j=0;j<mRight.size();j++){
            long sNode = mLeft[i];
            long dNode = mRight[j];

            if(roy[sNode][dNode]==INF) continue;

            list[sNode].push_back(dNode);
            list[dNode].push_back(sNode);
            C[sNode][dNode] = INF;
            pay[sNode][dNode] = roy[sNode][dNode];
            pay[dNode][sNode] =-roy[sNode][dNode];
        }
    }

    for(;bellman(););
    printf("%lld",Ans);

    return 0;
}
