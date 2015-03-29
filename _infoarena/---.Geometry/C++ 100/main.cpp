#include <iostream>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

#define x first
#define y second
#define a first
#define b second
#define start first
#define stop second
#define maxN 505
#define eps (0.000001)

typedef pair<double,double> Point;
typedef pair<Point,Point> Segment;

long n,i,j;
Segment sgm[maxN];
long ans;
double alfa;


Point Rotate(Point p){
    Point ans = p;
    ans.x = cos(alfa)*p.x - sin(alfa)*p.y;
    ans.y = cos(alfa)*p.x + sin(alfa)*p.y;
    return ans;
}

double getA(double x1,double y1,double x2,double y2){
    return (y2-y1)/(x2-x1);
}

int main()
{
    freopen("geometry.in","r",stdin);
    freopen("geometry.out","w",stdout);

    srand(time(NULL));
    alfa = 1.00/((double)(rand() % 1000));

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%lf %lf %lf %lf",&sgm[i].start.x,&sgm[i].start.y,&sgm[i].stop.x,&sgm[i].stop.y);
        sgm[i].start = Rotate(sgm[i].start);
        sgm[i].stop  = Rotate(sgm[i].stop);
        if(sgm[i].start.x > sgm[i].stop.x) {
            Point t = sgm[i].start; sgm[i].start = sgm[i].stop; sgm[i].stop = t;
        }
    }

    for(i=1;i<=n;i++){
        for(j=i+1;j<=n;j++){
            Point f1,f2,p;
            f1.a = getA(sgm[i].start.x,sgm[i].start.y,sgm[i].stop.x,sgm[i].stop.y);
            f1.b = sgm[i].start.y - f1.a*sgm[i].start.x;

            f2.a = getA(sgm[j].start.x,sgm[j].start.y,sgm[j].stop.x,sgm[j].stop.y);
            f2.b = sgm[j].start.y - f2.a*sgm[j].start.x;

            if(f1.a-f2.a >= -eps && f1.a-f2.a <= eps) {
                if(f1.b-f2.b >= -eps && f1.b-f2.b <= eps )
                    if(sgm[i].start.x < sgm[j].start.x){
                        if(sgm[i].stop.x >= sgm[j].start.x ) ans++;
                    }else {
                        if(sgm[j].stop.x >= sgm[i].start.x) ans++;
                    }
                continue;
            }

            p.x = (f1.b-f2.b)/(f2.a-f1.a);
            p.y = f1.a*p.x + f1.b;

            if(sgm[i].start.x <= p.x+eps && sgm[i].stop.x >= p.x-eps &&
               sgm[j].start.x <= p.x+eps && sgm[j].stop.x >= p.x-eps) ans++;
        }
    }

    printf("%ld",ans);

    return 0;
}
