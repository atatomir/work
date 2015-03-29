#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

#define mp make_pair

const long defX[4] = {0,0,-1,1};
const long defY[4] = {-1,1,0,0};

long n,m,i,j;
long a[1005][1005],ans[1005][1005];
queue<pair<long,long> > Q;
vector<pair<long,long> > V;

long maxV = 0, maxCont = 0;

void startLee(long i,long j){
    pair<long,long> start,stop;
    pair<long,long> pos,newPos;
    start = mp(i,j); stop = start;

    Q.push(mp(i,j)); a[i][j] = 0;
    while(!Q.empty()){
        pos = Q.front(); Q.pop();
        for(i=0;i<4;i++){
            newPos = pos;
            newPos.first += defX[i];
            newPos.second += defY[i];

            if(newPos.first == 0||newPos.first == n+1||
               newPos.second == 0||newPos.second == m+1) continue;
            if(a[newPos.first][newPos.second]){
                a[newPos.first][newPos.second] = 0;
                Q.push(newPos);
                if(stop.first < newPos.first || (stop.first == newPos.first && stop.second < newPos.second)){
                    stop = newPos;
                }
            }
        }
    }

    V.push_back(start);
    long sx = start.first,sy = start.second,ex = stop.first,ey = stop.second;
    ans[sx][sy] = 1; ans[ex+1][ey+1] = 1;
    ans[sx][ey+1] = -1; ans[ex+1][sy] = -1;
}

int main()
{
    freopen("dreptunghiuri2.in","r",stdin);
    freopen("dreptunghiuri2.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++) scanf("%ld",&a[i][j]);
    }

    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            if(a[i][j]){
                startLee(i,j);
            }
        }
    }

    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            ans[i][j] += ans[i-1][j] + ans[i][j-1] - ans[i-1][j-1] ;

    for(i=0;i<V.size();i++){
        long x = V[i].first,y = V[i].second;
        if(ans[x][y] > maxV){
            maxV = ans[x][y]; maxCont = 1;
        } else
        if(ans[x][y] == maxV) maxCont++;
    }

    printf("%ld %ld %ld",V.size(),maxV,maxCont);

    return 0;
}
