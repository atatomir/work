#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

const long defX[4]={0,0,-1,1};
const long defY[4]={-1,1,0,0};

typedef pair<long,long> Pos;
#define xx first
#define yy second
#define mp make_pair
#define maxN 1011
#define INF 1000000000

long n,m,i,j,h;
queue<Pos> Q;
long High[maxN][maxN];
long Ans;

int main()
{
    freopen("tsunami.in","r",stdin);
    freopen("tsunami.out","w",stdout);

    scanf("%ld %ld %ld",&n,&m,&h);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            scanf("%ld",&High[i][j]);

    for(i=1;i<=n;i++){
        High[i][0] = High[i][m+1] = INF;
        if(!High[i][1]) {
            High[i][1] = INF;
            Q.push(mp(i,1));
        }
        if(!High[i][m]) {
            High[i][m] = INF;
            Q.push(mp(i,m));
        }
    }

     for(i=1;i<=m;i++){
        High[0][i] = High[n+1][i] = INF;
        if(!High[1][i]) {
            High[1][i] = INF;
            Q.push(mp(1,i));
        }
        if(!High[n][i]) {
            High[n][i] = INF;
            Q.push(mp(n,i));
        }
    }

    while(!Q.empty()){
        Pos nod = Q.front(); Q.pop();
        for(i=0;i<4;i++){
            Pos newNod = mp(nod.xx+defX[i],nod.yy+defY[i]);
            if(High[newNod.xx][newNod.yy] < h){
                if(High[newNod.xx][newNod.yy])Ans++;
                High[newNod.xx][newNod.yy] = INF;
                Q.push(mp(newNod.xx,newNod.yy));
            }
        }
    }
    printf("%ld",Ans);

    return 0;
}
