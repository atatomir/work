#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

#define x first
#define y second
#define mp make_pair
#define maxN 1011
#define eps 0.000001

typedef pair<double,double> mPair;

long n,i,j;
mPair P[maxN],p1,p2,p3,p4;
long ans;
double xx,yy;

bool dEqual(double d){
    return d>-eps&&d<eps;
}
bool Equal(mPair p1,mPair p2){
    double d = p1.x-p2.x;
    if(d<-eps||d>eps) return false;
    d = p1.y-p2.y;
    if(d<-eps||d>eps) return false;
    return true;
}

bool lessORequal(mPair p1,mPair p2){
    if(Equal(p1,p2)) return true;
    if(dEqual(p1.x-p2.x)) return p1.y < p2.y;
    return p1.x<p2.x;
}

bool check(mPair p){
    long i=1,j=n,m;
    while(i<=j){
        m = (i+j)>>1;
        if(lessORequal(p,P[m]))
            j=m-1;
        else
            i=m+1;
    }

    printf("%.4lf %.4lf\n%.4lf %.4lf\n\n",p.x,p.y,P[i].x,P[i].y);

    if(Equal(p,P[i])) return true;
    return false;
}

int main()
{
    freopen("patrate3.in","r",stdin);
    freopen("patrate3.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%lf %lf",&P[i].x,&P[i].y);
    }
    sort(P+1,P+n+1);

    for(i=1;i<=n;i++){
        for(j=i+1;j<=n;j++){
            p1=P[i]; p2=P[j];

            xx = p1.y-p2.y; yy = p2.x-p1.x;
            //if(xx<0) xx=-xx;
            //if(yy<0) yy=-yy;

            p3 = p1; p3.x += xx; p3.y += yy;
            p4 = p2; p4.x += xx; p4.y += yy;

            if(check(p3)==true)
                if(check(p4)==true)
                    ans++;
        }
    }

    printf("%ld",ans>>1);

    return 0;
}
