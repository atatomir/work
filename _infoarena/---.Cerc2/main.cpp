#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

#define eps 0.000000000000001

struct Point{
    double x,y;
};
Point mp(long xx,long yy){
    Point tmp;
    tmp.x=xx;tmp.y=yy;
    return tmp;
}

long t,jump;
double R,alfa,l,beta,PI,A1,A2,s;
Point p1,p2,ans,Orig;

bool Equal(double a,double b){
    double x = a-b;
    if(x<0) x=-x;
    return x<=eps;
}

double getDist(Point p1,Point p2){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

bool reverse(double x1,double y1){
    if(Equal(x1,p1.x)&&Equal(y1,p1.y)) return false;
    return true;
}

Point getPoint(){
    if(Equal(p1.x,p2.x)){
        double yMin=min(p1.y,p2.y);
        if(p1.y>p2.y) s = l-s;
        return mp(p1.x,yMin+s);
    }

    double a = (p2.y-p1.y)/(p2.x-p1.x);
    double b = p1.y-a*p1.x;

    double i=min(p1.x,p2.x),j=max(p1.x,p2.x),m;
    if(reverse(i,a*i+b)) {s = l-s;swap(p1,p2);}

    double tg = (p2.y-p1.y)/(p2.x-p1.x);
    double x = sqrt(s*s/(tg*tg+1));
    x += i;

    Point tmp;
    tmp.x = x; tmp.y = a*tmp.x+b;
    return tmp;
}

int main()
{
    freopen("cerc2.in","r",stdin);
    freopen("cerc2.out","w",stdout);

    scanf("%ld",&t); PI = acos(-1); Orig = mp(0,0);
    for(;t;t--){
        scanf("%lf%lf%lf",&R,&alfa,&s);
        beta = (180.00-alfa)/2;
        alfa = alfa*PI/180; beta = beta*PI/180;
        if(!Equal(R*sin(beta),0))
            l = (R*R*sin(alfa))/(R*sin(beta));
        else
            l = 2*R;

        jump = s/l;
        A1 = 1.00*alfa*jump; A2 = 1.00*alfa*(jump+1);

        p1.x = R*cos(A1); p1.y = R*sin(A1);
        p2.x = R*cos(A2); p2.y = R*sin(A2);

        s-= jump*l;

        ans = getPoint();
        printf("%.4lf\n",getDist(Orig,ans));
    }

    return 0;
}
