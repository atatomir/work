#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1024

vector< int > ans[2];
struct Point{
    int x,y;
    bool isRed;
    bool used;

    void read(){
        char color;
        scanf("%d%d %c\n",&x,&y,&color);
        isRed = (color == 'R');
        used = false;
    }
    void isSolution(){
        if (isRed) {
            ans[0].pb( x );
            ans[0].pb( y );
        } else {
            ans[1].pb( x );
            ans[1].pb( y );
        }
    }

    void write(){
        cerr << "Point info : " << x << ' ' << y << '-' << isRed << ' ' << used << '\n';
    }
};

int n,m,i,x,y;
Point P[2][maxN];
Point aux;
vector< Point* > way;
Point *act;

Point* Next(Point *who){
    if (who->isRed) {
        return &P[ 1 ][ who->y ];
    } else {
        return &P[ 0 ][ who->x ];
    }
}

int main()
{
    freopen("zaharel.in","r",stdin);
    freopen("zaharel.out","w",stdout);

    scanf("%d%d",&n,&m);
    for (i = 1; i <= n; i++) P[0][i].x = P[1][i].x = -1;
    for (i = 1; i <= m; i++){
        aux.read();
        if (aux.isRed) {
            if (P[0][ aux.x ].x == -1)
                P[0][ aux.x ] = aux;
        } else {
            if (P[1][ aux.y ].x == -1)
                P[1][ aux.y ] = aux;
        }
    }

    act = &P[0][1];
    way.pb( act ); act->used = true;

    while ( true ) {
        act = Next(act);

        if (act->used) break;
        act->used = true;
        way.pb( act );
    }

    for (i = 0; i < way.size(); i++){
        if (way[i] == act) break;
    }

    for (int kk = i; kk < way.size(); kk++) way[kk]->isSolution();
    printf("%d\n", ans[0].size()/2 );
    for (auto e: ans[0] ) printf("%d ",e); printf("\n");
    for (auto e: ans[1] ) printf("%d ",e); printf("\n");

    return 0;
}
