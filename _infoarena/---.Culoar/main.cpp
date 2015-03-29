#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

#define maxN 1011
#define maxDist 16000.00
#define defCnt 45
#define eps 0.0000000000001
#define rAng 0.0012

#define pb push_back

inline bool Equal(double x,double y){
    x -= y; if(x<0) x=-x;
    return x<=eps;
}

struct Point{
    double x,y;
};
struct iElem{
    double alfa;
    long val;
};
iElem mp(double aalfa,long vval){
    iElem ans; ans.alfa=aalfa;ans.val=vval;
    return ans;
}
bool cmp(const iElem& a,const iElem& b){
    if(Equal(a.alfa,b.alfa)) return a.val > b.val;
    return a.alfa<b.alfa;
}

inline void Rotation(Point& p){
    Point tmp=p;
    p.x = tmp.x*cos(rAng) - tmp.y*sin(rAng);
    p.y = tmp.x*sin(rAng) + tmp.y*cos(rAng);
}

long n,cnt,i;
Point pct[maxN];
double PI;
vector<iElem> mom;

double sqr(double x){return x*x;}
double getDist(Point p1,Point p2){
    return sqrt(sqr(p1.x-p2.x)+sqr(p1.y-p2.y));
}
inline double getAngle(double y,double x){
    double ans = atan2(y,x);
    if(ans<0) ans += 2*PI;
    return ans;
}

bool check(double d){
    long i;
    for(long id=1;id<=n;id++){
        mom.clear();
        for(i=1;i<=n;i++){
            if(i==id) continue;

            double angle = getAngle(pct[i].y-pct[id].y,pct[i].x-pct[id].x);
            double start = PI-angle; if(start<0) start += 2*PI;
            double stop = 2*PI-angle; if(stop<0) stop += 2*PI;
            while(stop<start) stop += 2*PI; /**/ start-=eps; stop += eps;
            mom.pb(mp(start,1)); //mom.pb(mp(start-2*PI,1)); mom.pb(mp(start+2*PI,1));
            mom.pb(mp(stop,-1)); //mom.pb(mp(stop-2*PI,-1)); mom.pb(mp(stop+2*PI,-1));

            double l = getDist(pct[i],pct[id]); if(l<=d) continue;
            double xx = sqrt(sqr(l)-sqr(d));
            double alfa = getAngle(d,xx);

            start = alfa-angle; if(start<0) start += 2*PI;
            stop = (PI-alfa)-angle; if(stop<0) stop += 2*PI;
            while(stop<start) stop += 2*PI; /**/ start-=eps; stop += eps;
            mom.pb(mp(start,3)); //mom.pb(mp(start-2*PI,3)); mom.pb(mp(start+2*PI,3));
            mom.pb(mp(stop,-3)); //mom.pb(mp(stop-2*PI,-3)); mom.pb(mp(stop+2*PI,-3));
        }


        sort(mom.begin(),mom.end(),cmp);

        long cnt=0,up=0;
        for(i=0;i<mom.size();i++){
            if(mom[i].val>0) cnt++; else cnt--;
            if(mom[i].val==3) up++; else if(mom[i].val==-3) up--;
            if((cnt==n-1) && up) return true;
        }
    }
    return false;
}

int main()
{
    freopen("culoar.in","r",stdin);
    freopen("culoar.out","w",stdout);

    scanf("%ld",&n); PI = acos(-1.00);
    for(i=1;i<=n;i++) {scanf("%lf%lf",&pct[i].x,&pct[i].y);Rotation(pct[i]); }

    double i=0,j=maxDist,m; cnt = defCnt;
    while(cnt){
        cnt--; m=(i+j)/2;
        if(check(m))
            i=m;
        else
            j=m;
    }

    printf("%.6lf",(i+j)/2);

    return 0;
}
