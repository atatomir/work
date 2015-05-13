#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

#define maxN 50011

const double defX[4]={0.0,0.0,1.0,-1.0};
const double defY[4]={1.0,-1.0,0.0,0.0};

long n,i;
double xx[maxN],yy[maxN];
double x,y;

double act,actX,actY;
double eps = 0.00001;
double pas = 500.00;

double dist(double _x,double _y){
    return sqrt( (x-_x)*(x-_x) + (y-_y)*(y-_y)   );
}
double allDist(){
    double ans = 0.00;
    for(long i=1;i<=n;i++) ans += dist(xx[i],yy[i]);
    return ans;
}

int main()
{
    freopen("adapost2.in","r",stdin);
    freopen("adapost2.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%lf %lf",&xx[i],&yy[i]);

    actX = 500.00; actY = 500.00; x=actX; y=actY;
    act = allDist();

    while(pas>eps){
        bool modif = false;

        for(i=0;i<4;i++){
            x = actX + defX[i]*pas;
            y = actY + defY[i]*pas;

            double dd = allDist();
            if(dd<act){
                act = dd;
                actX = x; actY = y;
                modif = true;
            }
        }

        if(!modif) pas /= 2.00;
    }

    printf("%.4lf %.4lf",actX,actY);

    return 0;
}
