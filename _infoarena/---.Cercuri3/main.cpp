#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

#define pas 0.02
#define eps 0.000000001

struct Point{
    double x,y;
};
struct Circle{
    Point C;
    double R;
};

long t;
Circle c1,c2;
double a,limUp,limDown,h,Area,xx;
Point intv[2];

double sqr(double x){return 1.00*x*x;}
double getArea(){
    if(intv[0].x>intv[1].x) swap(intv[0],intv[1]);
    if(intv[1].x>intv[0].y+eps) return 0;
    if(intv[1].y<intv[0].y) return intv[1].y-intv[1].x;
    return intv[0].y - intv[1].x;
}

int main()
{
    freopen("cercuri3.in","r",stdin);
    freopen("cercuri3.out","w",stdout);

    scanf("%ld",&t);
    for(;t;t--){
        scanf("%lf%lf%lf",&c1.C.x,&c1.C.y,&c1.R);
        scanf("%lf%lf%lf",&c2.C.x,&c2.C.y,&c2.R);
        scanf("%lf",&a);

        limUp = min(c1.C.y+c1.R,c2.C.y+c2.R);
        limDown = max(c1.C.y-c1.R,c2.C.y-c2.R);

        Area = 0;
        for(h=limDown;h<=limUp;h+=pas){
            xx = sqrt(sqr(c1.R)-sqr(h-c1.C.y));
            intv[0].x = c1.C.x-xx; intv[0].y = c1.C.x+xx;

            xx = sqrt(sqr(c2.R)-sqr(h-c2.C.y));
            intv[1].x = c2.C.x-xx; intv[1].y = c2.C.x+xx;

            Area += getArea();
        }
        Area *= pas;

        if(Area >= a-eps) printf("DA\n"); else printf("NU\n");
    }

    return 0;
}
