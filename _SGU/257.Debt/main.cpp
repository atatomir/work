#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

#define maxN 15
#define maxPietre 100011
#define INF 2000000000

long c1,c2,c3,id,ids[maxPietre];
long n,i,S,D,A,B,C;
long cnt[8];
char s[10];

vector<long> list[maxN];
long Cap[maxN][maxN],F[maxN][maxN];
long prov[maxN];
queue<long> Q;
bool used[maxN];

long toA[8];
long toB[8];
long toC[8];
char ans[maxPietre];

inline void addEdge(long SS,long DD,long cap){
    Cap[SS][DD] = cap;
    list[SS].push_back(DD);
    list[DD].push_back(SS);
}

bool makeFlux(){
    memset(prov,0,sizeof(prov));
    memset(used,0,sizeof(used));
    long i;

    used[S]=true; Q.push(S);
    while(!Q.empty()){
        long node = Q.front(); Q.pop();
        if(node==D) continue;

        for(i=0;i<list[node].size();i++){
            long newNode = list[node][i];
            if(used[newNode] || Cap[node][newNode]==F[node][newNode]) continue;
            used[newNode] = true; Q.push(newNode);
            prov[newNode]=node;
        }
    }

    if(used[D]==false) return false;

    for(i=0;i<list[D].size();i++){
        prov[D]=list[D][i];
        if(used[list[D][i]]==false) continue;

        long flux=INF;
        for(long node=D;node!=S;node=prov[node]) flux=min(flux,Cap[prov[node]][node]-F[prov[node]][node]);
        for(long node=D;node!=S;node=prov[node]){
            F[prov[node]][node]+=flux;
            F[node][prov[node]]-=flux;
        }
    }

    return true;
}

int main()
{
    freopen("debt.in","r",stdin);

    scanf("%ld%ld%ld",&c1,&c2,&c3);
    scanf("%ld\n",&n);
    for(i=1;i<=n;i++){
        scanf("%s\n",s);
        id=0;
        if(s[0]=='B') id++;
        if(s[1]=='B') id+=2;
        if(s[2]=='B') id+=4;

        cnt[id]++; ids[i] = id;
    }

    S=11; A=8;B=9;C=10; D=12;
    for(i=0;i<8;i++) addEdge(S,i,cnt[i]);
    for(i=0;i<8;i++){
        if(i&1) addEdge(i,A,cnt[i]);
        if(i&2) addEdge(i,B,cnt[i]);
        if(i&4) addEdge(i,C,cnt[i]);
    }
    addEdge(A,D,c1/2);
    addEdge(B,D,c2/2);
    addEdge(C,D,c3/2);

    for(;makeFlux(););

    for(i=0;i<8;i++){
        toA[i] += F[i][A]; c1 -= F[i][A]*2;
        toB[i] += F[i][B]; c2 -= F[i][B]*2;
        toC[i] += F[i][C]; c3 -= F[i][C]*2;
    }

    for(i=1;i<=n;i++){
        if(toA[ids[i]]) { toA[ids[i]]--; ans[i]='P';} else
        if(toB[ids[i]]) { toB[ids[i]]--; ans[i]='O';} else
        if(toC[ids[i]]) { toC[ids[i]]--; ans[i]='S';}
    }

    for(i=1;i<=n;i++){
        if(ans[i]=='\0'){
            if(c1) {ans[i]='P';c1--;} else
            if(c2) {ans[i]='O';c2--;} else
            {
                if(c3) c3--;
                ans[i]='S';
            }
        }
    }

    if(c1 || c2 || c3) {
        printf("no solution");
        return 0;
    }
    printf("%s",ans+1);

    return 0;
}
