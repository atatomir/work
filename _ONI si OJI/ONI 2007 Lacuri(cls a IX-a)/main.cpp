#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

#define maxN 110
#define mp make_pair
#define xx first
#define yy second

const long defX[4]={0,0,1,-1};
const long defY[4]={1,-1,0,0};

long n,i,j,a[maxN][maxN],ans,cont,start,x,y;
long y1=105,y2=0,x1=105,x2=0;
vector<pair<long,long> > answer;

void dfs(long x,long y){
    a[x][y] = -1; cont++;
    x1 = min(x1,x); x2 = max(x2,x);
    y1 = min(y1,y); y2 = max(y2,y);

    for(long p=0;p<4;p++)
        if(a[x+defX[p]][y+defY[p]] == 1) dfs(x+defX[p],y+defY[p]);
}

void retur(long x,long y){
    if(a[x][y] == -1) return;
    answer.push_back(mp(x,y));
    for(long p=0;p<4;p++)
        if(a[x+defX[p]][y+defY[p]] == a[x][y]-1) {retur(x+defX[p],y+defY[p]);break;}
}

void bfs(){
    for(i=0;i<=n+1;i++) a[0][i] = a[n+1][i] = a[i][0] = a[i][n+1] = -1;
    queue<pair<long,long> > Q;

    a[1][1] = 1; Q.push(mp(1,1));
    while(!Q.empty()){
        x = Q.front().xx; y = Q.front().yy; Q.pop();
        for(long p =0;p<4;p++){
            if(!a[x+defX[p]][y+defY[p]]) {
                a[x+defX[p]][y+defY[p]] = a[x][y]+1;
                Q.push(mp(x+defX[p],y+defY[p]));
            }
        }
    }
}

int main()
{
    freopen("lacuri.in","r",stdin);
    freopen("lacuri.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++) scanf("%ld",&a[i][j]);

    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            y1=105,y2=0,x1=105,x2=0;
            cont = 0;
            if(a[i][j] == 1) dfs(i,j),start++;

            if((y2-y1+1)*(x2-x1+1) == cont && (y2-y1)==(x2-x1)) ans++;
        }
    }

    printf("%ld\n",ans);
    if(ans != start) return 0;

    bfs();
    retur(n,n);
    for(i=answer.size()-1;i >= 0;i--){
        printf("%ld %ld\n",answer[i].xx,answer[i].yy);
    }

    return 0;
}
