#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

#define eps 0.0000000000001

struct Point{
    double x,y;
};
struct Circle{
    Point C;
    double R;
};

long t;
Circle c1,c2;
double alim,a,pi;

double getDist(Point a,Point b){
    return sqrt((a.x-b.x)*(a.x-b.x)-(a.y-b.y)*(a.y-b.y));
}

double getArea(){
    if(getDist(c1.C,c2.C)>c1.R+c2.R) return 0;
    if(getDist(c1.C,c2.C)+c1.R < c2.R && getDist(c1.C,c2.C)<c2.R) return 0;
    if(getDist(c1.C,c2.C)+c2.R < c1.R && getDist(c1.C,c2.C)<c1.R) return 0;


}

int main()
{
    freopen("cercuri3.in","r",stdin);
    freopen("cercuri3.out","w",stdout);

    scanf("%ld",&t); pi = acos(-1);
    for(;t;t--){
        scanf("%lf%lf%lf",&c1.C.x,&c1.C.y,&c1.R);
        scanf("%lf%lf%lf",&c2.C.x,&c2.C.y,&c2.R);
        scanf("%lf",&alim);
        a = getArea();
        if(a>=alim-eps) printf("DA\n"); else printf("NU\n");
    }

    return 0;
}
