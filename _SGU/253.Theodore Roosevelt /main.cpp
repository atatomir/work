#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

#define DEBUG
#define maxN 100011
#define mm(x) (x<0?-x:x)
#define eps 1e-9

double PI;

class Point{
    public:
        int x,y;
        double alfa;

        Point(){}
        void read(){
            scanf("%ld %ld",&x,&y);
            alfa = 1.00;
        }

        bool operator<(const Point& who)const{
            return alfa < who.alfa;
        }
};

int n,m,k,i;
Point P[maxN];
Point act;

long cb(double x){
    long l=2,r=n-1,mid;
    while(l<=r){
        mid = (l+r)>>1;
        if(x < P[mid].alfa-eps)
            r = mid-1;
        else
            l = mid+1;
    }

    if(r==1) r=2;

    return r;
}

long long area(Point& p1,Point& p2,Point& p3){
    return 1LL*p1.x*p2.y-1LL*p1.y*p2.x +
           1LL*p2.x*p3.y-1LL*p2.y*p3.x +
           1LL*p3.x*p1.y-1LL*p3.y*p1.x ;
}
bool isIn(Point& p1,Point& p2,Point& p3,Point& act){
    long long A1 = mm(area(p1,p2,act)) + mm(area(p2,p3,act)) + mm(area(p3,p1,act));
    long long A2 = mm(area(p1,p2,p3));

    if(A1==A2 && A1 == 0) return act.x >= min(min(p1.x,p2.x),p3.x)
                              && act.x <= max(max(p1.x,p2.x),p3.x);

    return (A1==A2);
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG
    PI = acos(-1.00);

    scanf("%ld %ld %ld",&n,&m,&k);
    for(i=1;i<=n;i++) P[i].read();
    for(i=2;i<=n;i++) P[i].alfa = atan2( P[i].y-P[1].y,P[i].x-P[1].x );

    for(i=3;i<=n;i++)
        if(P[i].alfa< P[i-1].alfa) P[i].alfa += 2.00*PI;
    //! ai grija sa fie ordonate crescator dupa unghi
    //! incepand de la pct 1 pana la n

    if(k==0) {printf("YES"); return 0;}

    for(;m--;){
        act.read();
        act.alfa = atan2( act.y-P[1].y,act.x-P[1].x );

        if(act.x==P[1].x && act.y==P[1].y) k--; else {
            long pos = cb(act.alfa);

            Point p1 = P[pos];
            Point p2 = P[pos+1];

            if(isIn( P[1],p1,p2,act )) k--;
        }

        if(k==0) {
            printf("YES");
            return 0;
        }
    }

    printf("NO");

    return 0;
}
