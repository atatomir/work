#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

const long defX[4] = {0,0,-1,1};
const long defY[4] = {1,-1,0,0};

#define maxN 311
#define x first
#define y second
#define mp make_pair

long n,m,k,i,j,cont;
char a[maxN][maxN],src;
long Zone[maxN][maxN];
vector<pair<long,long> > Z;
vector<long> neigh[maxN*maxN];
long tmp[maxN*maxN],act;

queue<long> Q;
bool inActive[maxN*maxN];
long nNeigh[maxN*maxN];

long lung,ans;

void dfs(long x,long y){
    a[x][y] = '!'; Zone[x][y] = cont;
    for(long i=0;i<4;i++){
        if(a[x+defX[i]][y+defY[i]] == src) dfs(x+defX[i],y+defY[i]);
    }
}

void dfsN(long x,long y){
    a[x][y] = '?';
    for(long i=0;i<4;i++){
        if(Zone[x+defX[i]][y+defY[i]] == act) {
            if(a[x+defX[i]][y+defY[i]] != '?') dfsN(x+defX[i],y+defY[i]);
        } else {
            long aZone = Zone[x+defX[i]][y+defY[i]];
            if(!aZone) continue;
            if(tmp[aZone] != act){
                tmp[aZone] = act;
                neigh[act].push_back(aZone);
            }
        }
    }
}

void dfsF(long x,long y){
    a[x][y] = '@'; lung++;
    for(long i=0;i<4;i++){
        if(a[x+defX[i]][y+defY[i]] == '@') continue;
        if(inActive[Zone[x+defX[i]][y+defY[i]]]) continue;
        dfsF(x+defX[i],y+defY[i]);
    }
}

int main()
{
    freopen("zone2.in","r",stdin);
    freopen("zone2.out","w",stdout);

    scanf("%ld %ld %ld",&n,&m,&k);
    for(i=1;i<=n;i++) scanf("%s",a[i]+1);

    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            if(a[i][j] != '!'){
                cont++; src = a[i][j];
                Z.push_back(mp(i,j));
                dfs(i,j);
            }
        }
    }

    for(i=0;i<cont;i++){
        act = i+1;
        dfsN(Z[i].x,Z[i].y);
    }

    for(i=1;i<=cont;i++){
        nNeigh[i] = neigh[i].size();
        if(neigh[i].size() < k) {
            Q.push(i);
            inActive[i] = true;
        }
    }
    while(!Q.empty()){
        long src = Q.front(); Q.pop();
        inActive[src] = true;

        for(i=0;i<neigh[src].size();i++){
            long newNod = neigh[src][i];

            if(inActive[newNod]) continue;
            if(--nNeigh[newNod] < k){
                inActive[newNod] = true;
                Q.push(newNod);
            }
        }
    }

    inActive[0] = true;
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            if(a[i][j] == '@') continue;
            if(inActive[Zone[i][j]]) continue;

            lung = 0;
            dfsF(i,j);
            ans = max(ans,lung);
        }
    }

    printf("%ld",ans);

    return 0;
}
