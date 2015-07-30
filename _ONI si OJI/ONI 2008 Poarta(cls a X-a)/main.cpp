#include <iostream>
#include <cstdio>
#include <queue>
 
using namespace std;
 
#define maxK 1010
#define maxN 110
#define Min first
#define cont second
#define x first
#define y second
#define mp make_pair
#define mod 997
 
const long defX[4] = {-1,1,0,0};
const long defY[4] = {0,0,1,-1};
 
long n,m,i,j,k;
pair<long,long> p[maxK];
pair<long,long> dp[maxN][maxN];
bool poarta[maxN][maxN];
pair<long,long> start,stop;
queue< pair<long,long> > Q;
pair<long,long> point;
 
long abss(long x){
    if(x<0)return -x;
    return x;
}
 
int main()
{
    freopen("poarta.in","r",stdin);
    freopen("poarta.out","w",stdout);
 
    scanf("%ld %ld %ld",&n,&m,&k);
    scanf("%ld %ld %ld %ld",&start.x,&start.y,&stop.x,&stop.y);
    for(i=1;i<=k;i++) {
        scanf("%ld %ld",&p[i].x,&p[i].y);
        poarta[p[i].x][p[i].y] = true;
    }
 
    dp[start.x][start.y] = mp(1,1);
    Q.push(start);
 
    while(!Q.empty()){
        point = Q.front(); Q.pop();
        if(dp[point.x][point.y].Min >= dp[stop.x][stop.y].Min && dp[stop.x][stop.y].Min ) break;
 
        for(i=0;i<4;i++){
            pair<long,long> newP = point;
            long newVal = dp[point.x][point.y].Min +1;
            newP.x += defX[i]; newP.y += defY[i];
 
            if(newP.x == 0 || newP.x == n+1 || newP.y == 0 || newP.y == m+1) continue;
 
            if(!dp[newP.x][newP.y].Min){
                dp[newP.x][newP.y].Min = newVal;
                dp[newP.x][newP.y].cont = dp[point.x][point.y].cont;
                Q.push(mp(newP.x,newP.y));
            } else
            if(dp[newP.x][newP.y].Min == newVal){
                dp[newP.x][newP.y].cont += dp[point.x][point.y].cont;
            }
 
            dp[newP.x][newP.y].cont %= mod;
        }
 
        if(poarta[point.x][point.y])
        for(i=1;i<=k;i++){
            pair<long,long> newP = p[i];
            long newVal = dp[point.x][point.y].Min + 1;
 
            if(dp[newP.x][newP.y].Min < newVal && dp[newP.x][newP.y].Min) {
                p[i] = p[k--];
                i--;
                continue;
            }
 
            if(!dp[newP.x][newP.y].Min){
                dp[newP.x][newP.y].Min = newVal;
                dp[newP.x][newP.y].cont = dp[point.x][point.y].cont;
                Q.push(mp(newP.x,newP.y));
            } else
            if(dp[newP.x][newP.y].Min == newVal){
                dp[newP.x][newP.y].cont += dp[point.x][point.y].cont;
            }
 
            dp[newP.x][newP.y].cont %= mod;
        }
    }
 
    printf("%ld \n%ld",dp[stop.x][stop.y].Min-1,dp[stop.x][stop.y].cont);
 
    return 0;
}