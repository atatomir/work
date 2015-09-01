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

#define maxN 55
#define eps 0.0000000000001

struct Position {
    int x,y;

    Position() {}
    Position(int _x,int _y) {
        reset(_x,_y);
    }
    void reset(int _x,int _y) {
        x = _x; y = _y;
    }
    void read() {
        scanf("%d%d",&x,&y);
    }
    bool operator==(const Position& who) {
        return (x==who.x)&&(y==who.y);
    }
};

struct Way {
    Position where;
    double ef;
    double dist;

    Way() {}
    Way(Position pos,double _ef,double _dist) {
        reset(pos,_ef,_dist);
    }
    void reset(Position pos,double _ef,double _dist) {
        where = pos;
        ef = _ef;
        dist = _dist;
    }

    bool isEqual(const double a,const double b)const {
        double aux = (a < b?b - a : a - b);
        return aux < eps;
    }
    bool operator<(const Way& who)const {
        if (isEqual(ef,who.ef)) return dist > who.dist;
        return ef > who.ef;
    }
};

const int defX[4] = {0,0,-1,1};
const int defY[4] = {-1,1,0,0};

int n,m,i,j;
double Lmax;
int matrix[maxN][maxN];
Position source,dest;

priority_queue<Way> H;
bool us[maxN][maxN];
double m_ef[maxN][maxN];
double m_dist[maxN][maxN];

int main()
{
    freopen("excursie.in","r",stdin);
    freopen("excursie.out","w",stdout);

    scanf("%d%d%lf",&n,&m,&Lmax);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            scanf("%ld",&matrix[i][j]);

    for (i = 0; i <= n+1; i++)
        us[i][0] = us[i][m+1] = true;
    for (j = 0; j <= m+1; j++)
        us[0][j] = us[n+1][j] = true;

    Lmax += eps;
    source.read();
    dest.read();

    H.push( Way(source,0,0) );
    while (!H.empty()) {
        Way act = H.top(); H.pop();

        if (us[act.where.x][act.where.y]) continue;
        us[act.where.x][act.where.y] = true;

        m_ef[act.where.x][act.where.y] = act.ef;
        m_dist[act.where.x][act.where.y] = act.dist;

        if (act.where == dest) break;

        for (int i = 0; i < 4; i++) {
            Position aux = act.where;
            aux.x += defX[i];
            aux.y += defY[i];

            if (us[aux.x][aux.y]) continue;

            int actHeight = matrix[act.where.x][act.where.y];
            int newHeight = matrix[aux.x][aux.y];
            double newDist = sqrt( 1.00 + 1.00*(newHeight-actHeight)*(newHeight-actHeight) );
            double newEf = 1.00*(newHeight-actHeight) * newDist;
            if (newEf < 0) newEf *= -(1.00/2.00);

            if (actHeight == newHeight) newEf = 1.00;

            H.push( Way(aux,act.ef+newEf,act.dist+newDist) );
        }
    }

    if (m_dist[dest.x][dest.y] > Lmax) {
        printf("-1");
        return 0;
    }
    printf("%.3lf %.3lf", m_ef[dest.x][dest.y], m_dist[dest.x][dest.y]);

    return 0;
}
