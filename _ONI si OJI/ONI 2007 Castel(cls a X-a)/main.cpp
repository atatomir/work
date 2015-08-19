#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 170

const int defX[4] = {0,0,-1,1};
const int defY[4] = {-1,1,0,0};

int n,m,i,j,prov,cnt,x_prov,y_prov;
int id[maxN][maxN];
int need[maxN][maxN];
vector< pair<int,int> > depend[maxN*maxN];

bool unlocked[maxN][maxN];
bool visited[maxN][maxN];
queue< pair<int,int> > Q;

/*
 * 1. Get a visited room from queue
 * 2. Unlock other rooms
 * 3. Try to expand the way + add to queue
 */

 bool canVisit(pair<int,int> cell){
    if ( visited[cell.first][cell.second] ) return false;

    for (int i = 0; i < 4; i++) {
        auto aux = cell;
        aux.first  += defX[i];
        aux.second += defY[i];

        if ( visited[aux.first][aux.second] ) return true;
    }

    return false;
 }

 void dfs(pair<int,int> cell){
    visited[ cell.first ][ cell.second ] = true;
    Q.push( cell );

    for (int i = 0; i < 4; i++) {
        auto aux = cell;
        aux.first  += defX[i];
        aux.second += defY[i];

        if ( unlocked[aux.first][aux.second] && !visited[aux.first][aux.second] )
            dfs(aux);
    }
 }

int main()
{
    freopen("castel.in","r",stdin);
    freopen("castel.out","w",stdout);

    scanf("%d%d%d",&n,&m,&prov);
    for (i = 1; i <= n; i++){
        for (j = 1; j <= m; j++){
            id[i][j] = ++cnt;
            scanf("%d",&need[i][j]);
            depend[ need[i][j] ].pb( mp(i,j) );

            if (cnt == prov) {
                x_prov = i;
                y_prov = j;
            }
        }
    }

    unlocked[x_prov][y_prov] = visited[x_prov][y_prov] = true;
    Q.push( mp( x_prov,y_prov ) );

    while (!Q.empty()) {
        auto act = Q.front(); Q.pop();

        for (auto e:depend[ id[ act.first ][ act.second ] ] ) {
            unlocked[ e.first ][ e.second ] = true;
        }
        for (auto e:depend[ id[ act.first ][ act.second ] ] ) {
            if ( canVisit(e) ) dfs(e);
        }
    }

    int ans = 0;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++){
            if ( visited[i][j] ) ans++;
        }
    }
    printf("%d",ans);

    return 0;
}
