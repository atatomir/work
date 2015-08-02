#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxN 22
#define rAlfa 0.00001
#define eps 0.0000000000001

struct Point{
    double x,y;
};
struct iPoint{
    Point p;
    double angle;
};
iPoint mp(double xx,double yy,double angl){
    iPoint ans;
    ans.p.x=xx;ans.p.y=yy;
    ans.angle=angl;
    return ans;
}
bool cmp(const iPoint& a,const iPoint& b){
    return a.angle < b.angle;
}

long n,m,i,j,k,l;
Point Poly[2][maxN],p;
vector<iPoint> vfs;
double PI,ans;

void Rotate(Point& p){
    Point tmp = p;
    p.x = p.x*cos(rAlfa) - p.y*sin(rAlfa);
    p.y = p.x*sin(rAlfa) + p.y*cos(rAlfa);
}

double getArea(Point p1,Point p2,Point p3){
    return (p1.x*p2.y-p1.y*p2.x+p2.x*p3.y-p2.y*p3.x+p3.x*p1.y-p3.y*p1.x)/2;
}

bool Equal(double x,double y){
    x-=y;if(x<0) x=-x;
    return (x<=eps);
}

bool isIn(long id,long dim,Point p){
    double sign=1.00;
    if(getArea(Poly[id][1],Poly[id][2],p)<0) sign = -1.00;

    for(long i=1;i<=dim;i++)
        if(getArea(Poly[id][i],Poly[id][i+1],p)*sign<0) return false;
    return true;
}

int main()
{
    freopen("arie.in","r",stdin);
    freopen("arie.out","w",stdout);

    PI = acos(-1);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) {scanf("%lf %lf",&Poly[0][i].x,&Poly[0][i].y);Rotate(Poly[0][i]);}
    scanf("%ld",&m);
    for(i=1;i<=m;i++) {scanf("%lf %lf",&Poly[1][i].x,&Poly[1][i].y);Rotate(Poly[1][i]);}

    Poly[0][n+1] = Poly[0][1]; Poly[1][m+1]=Poly[1][1];
    for(i=1;i<=n;i++){
        j=i+1;
        double a1 = (Poly[0][j].y-Poly[0][i].y)/(Poly[0][j].x-Poly[0][i].x);
        double b1 = Poly[0][i].y-a1*Poly[0][i].x;

        for(k=1;k<=m;k++){
            l=k+1;
            double a2 = (Poly[1][l].y-Poly[1][k].y)/(Poly[1][l].x-Poly[1][k].x);
            double b2 = Poly[1][k].y-a2*Poly[1][k].x;

            if(Equal(a1,a2)) continue;

            double x = (b1-b2)/(a2-a1);
            double y = a1*x+b1;

            double min0 = min(Poly[0][i].x,Poly[0][j].x);
            double max0 = max(Poly[0][i].x,Poly[0][j].x);
            double min1 = min(Poly[1][k].x,Poly[1][l].x);
            double max1 = max(Poly[1][k].x,Poly[1][l].x);
            if(min0<=x+eps && max0>=x-eps &&
               min1<=x+eps && max1>=x-eps ) vfs.push_back(mp(x,y,0));
        }
    }

    for(i=1;i<=n;i++)
        if(isIn(1,m,Poly[0][i])) vfs.push_back(mp(Poly[0][i].x,Poly[0][i].y,0));
    for(i=1;i<=m;i++)
        if(isIn(0,n,Poly[1][i])) vfs.push_back(mp(Poly[1][i].x,Poly[1][i].y,0));

    p.x=0;p.y=0;
    for(i=0;i<vfs.size();i++){
        p.x += vfs[i].p.x;
        p.y += vfs[i].p.y;
    }
    p.x /= vfs.size();
    p.y /= vfs.size();

    for(i=0;i<vfs.size();i++){
        vfs[i].angle = atan2(vfs[i].p.y-p.y,vfs[i].p.x-p.x);
        if(vfs[i].angle<0) vfs[i].angle += PI*2;
    }

    sort(vfs.begin(),vfs.end(),cmp);
    vfs.push_back(vfs[0]);

    Point zero; zero.x=0;zero.y=0;
    for(i=0;i<vfs.size()-1;i++){
        ans += getArea(zero,vfs[i].p,vfs[i+1].p);
    }
    if(ans<0) ans=-ans;
    printf("%.3lf",ans);

    return 0;
}
