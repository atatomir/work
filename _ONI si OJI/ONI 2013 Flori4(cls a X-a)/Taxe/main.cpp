#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

#define maxN 1011
#define x first
#define y second
#define INF 2000000000
#define maxBuf 1000000

typedef pair<long,long> Point;

const long defX[8]={0,0,1,-1,1,-1,-1,1};
const long defY[8]={1,-1,0,0,-1,1,-1,1};

long n,m,i,j;
long a[maxN][maxN],dp[maxN][maxN];
bool inQueue[maxN][maxN];
Point start,stop;

queue<Point> Q;

char Buff[maxBuf];
long pos=0;

long bulaneala=0;

inline bool isDigit(char c){
    return c >= '0' && c <= '9';
}
long getLong(){
    while(!isDigit(Buff[pos])){
        pos++;
        if(pos == maxBuf){
            pos = 0;
            fread(Buff,1,maxBuf,stdin);
        }
    }
    long ans = 0;
    while(isDigit(Buff[pos])){
        ans = ans*10 + Buff[pos++] - '0';
        if(pos == maxBuf){
            pos = 0;
            fread(Buff,1,maxBuf,stdin);
        }
    }
    return ans;
}

int main()
{
    freopen("taxa.in","r",stdin);
    freopen("taxa.out","w",stdout);

    scanf("%ld %ld %ld %ld %ld %ld",&n,&m,&start.x,&start.y,&stop.x,&stop.y);
    fread(Buff,1,maxBuf,stdin);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++) {a[i][j] = getLong();dp[i][j] = INF;}

    dp[start.x][start.y] = 0;
    inQueue[start.x][start.y] = true;
    Q.push(start);

    while(!Q.empty()){
        Point p = Q.front(); Q.pop();
        if(dp[stop.x][stop.y] != INF) bulaneala++;
        if(bulaneala > n*m) break;

        inQueue[p.x][p.y] = false;
        for(i=0;i<8;i++){
            Point newP;
            newP.x = p.x + defX[i];
            newP.y = p.y + defY[i];

            long newCost = dp[p.x][p.y] + (a[p.x][p.y] != a[newP.x][newP.y] ? a[p.x][p.y]*a[newP.x][newP.y]:0);
            if(newCost < dp[newP.x][newP.y]){
                dp[newP.x][newP.y] = newCost;
                if(!inQueue[newP.x][newP.y]){
                    inQueue[newP.x][newP.y] = true;
                    Q.push(newP);
                }
            }
        }
    }

    printf("%ld",dp[stop.x][stop.y]);

    return 0;
}
