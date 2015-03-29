#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxN 311
#define alfa 0.0012
#define eps 0.00000000001
#define x1 xx1
#define x2 xx2
#define y1 yy1
#define y2 yy2
#define INF 20000000000000.000

const double aCos= cos(alfa);
const double aSin = sin(alfa);

struct Point{
    double x,y;
    void Rotate(){
        double xx=x,yy=y;
        x = xx*aCos - yy*aSin;
        y = xx*aSin + yy*aCos;
    }
};

long n,k,i,j,howEqual,K;
Point p[maxN];
double aEc,bEc,Ans;

vector<double> before,after;

bool Equal(double x,double y){
    x -= y; if(x<0) x=-x;
    return (x<=eps);
}

double getDist(double x1,double y1,double x2,double y2){
    return sqrt((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1));
}

inline void TryWith(double a1,double b1,double b2){
    double x0 = (-b2)/a1;

    double a2 = -1.00/(a1);b2 = -a2*x0;
    double xI = (b2-b1)/(a1-a2),yI=a1*xI+b1;

    double dist = getDist(xI,yI,x0,0);
    Ans = min(Ans,dist);
}

int main()
{
    freopen("geom.in","r",stdin);
    freopen("geom.out","w",stdout);

    scanf("%ld%ld",&n,&K); Ans = INF;
    for(i=1;i<=n;i++) {scanf("%lf%lf",&p[i].x,&p[i].y);p[i].Rotate();}

    for(i=1;i<n;i++){
        for(j=i+1;j<=n;j++){
            aEc = (p[i].y-p[j].y)/(p[i].x-p[j].x);
            bEc = p[i].y-aEc*p[i].x;

            before.clear(); after.clear(); howEqual = 2;
            for(k=1;k<=n;k++){
                if(k==i || k==j) continue;

                double actB = p[k].y-aEc*p[k].x;
                if(Equal(actB,bEc)) howEqual++; else{
                    if(actB < bEc) before.push_back(actB); else
                                   after.push_back(actB);
                }
            }

            long need = K - howEqual;
            if(need <= 0) Ans = 0; else
            if(need <= after.size()){
                nth_element(after.begin(),after.begin()+need-1,after.end());
                TryWith(aEc,bEc,after[need-1]);
            }
            need = before.size()-need+(1-1);
            if(need >= (long)before.size()) Ans=0; else
            if(need >= 0){
                nth_element(before.begin(),before.begin()+need,before.end());
                TryWith(aEc,bEc,before[need]);
            }

        }
    }

    printf("%.3f",Ans);

    return 0;
}
