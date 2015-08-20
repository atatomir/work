#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011

struct Point {
    int q_id;
    int x,y;

    bool operator<(const Point& who)const {
        return 1LL*y*who.x > 1LL*x*who.y;
    }
    void read(int id) {
        scanf("%d%d",&x,&y);
        q_id = id;
    }
};

int n,q,i,all,last;
Point P[maxN<<1];

int dim;
Point S[maxN]; //! stack;
double ans[maxN];

bool cmp(const Point& a,const Point& b) {
    return a.x < b.x;
}

bool isTrigo(const Point& p1,const Point& p2,const Point& p3) {
    long long aux = p1.x * p2.y - p1.y * p2.x +
                    p2.x * p3.y - p2.y * p3.x +
                    p3.x * p1.y - p3.y * p1.x ;
    return aux > 0 ;
}

void addPoint( Point& who ) {
    while ( dim > 0 && S[dim].x > who.x ) dim--;
    while ( dim > 1 ) {
        if ( isTrigo(S[dim-1],S[dim],who) ) break;
        if ( --dim <= 1 ) break;
    }

    S[++dim] = who;
}

bool EraseStack( const Point& Line ) {
    if ( dim <= 1 ) return false;

    return 1LL * (S[dim].y - S[dim-1].y)*Line.x >=  1LL * (S[dim].x - S[dim-1].x)*Line.y;
}

double getHight( const Point& Line , double x ) {
    double alfa = 1.00*Line.y/Line.x;
    return alfa*x;
}

int main()
{
    freopen("ydist.in","r",stdin);
    freopen("ydist.out","w",stdout);

    scanf("%d%d",&n,&q);
    for (i = 1; i <= n; i++) P[i].read(0);
    for (i = 1; i <= q; i++) P[i+n].read(i);

    all = n+q;
    sort(P+1,P+all+1);

    last = 0;
    dim = 0; //! stack is empty

    for (i = 1; i <= all; i++) {
        if ( P[i].q_id == 0 ) continue; //! just a point.. add later
        sort( P+last+1,P+i,cmp );

        for (last++; last < i; last++) addPoint( P[last] );
        while ( EraseStack( P[i] ) ) dim--;

        ans[ P[i].q_id ] = S[dim].y - getHight( P[i] , S[dim].x );
    }

    for (i = 1; i <= q; i++) printf("%.7lf\n",ans[i]);

    return 0;
}
