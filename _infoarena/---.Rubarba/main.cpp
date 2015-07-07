#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

#define maxN 100011

double PI = acos(-1.00);

struct dPoint{
    double x,y;

    void Rotate(double ang){
        double angsin = sin(ang);
        double angcos = cos(ang);

        dPoint vaj ; vaj.x = x; vaj.y = y;

        x = 1.00*vaj.x*angcos - 1.00*vaj.y*angsin;
        y = 1.00*vaj.x*angsin + 1.00*vaj.y*angcos;
    }
    void apply(double trX,double trY,double trAng){
        x -= trX; y -= trY;
        Rotate(trAng);
    }

    double getAngle(dPoint& who){
        double ans = atan2( who.y-y,who.x-x );
        return ans;
    }
};

struct Point{
    int x,y;

    void read(){ scanf("%d %d",&x,&y); }
    bool operator<(const Point& who)const{
        if(x==who.x) return (y<who.y);
        return (x<who.x);
    }
    bool upper(Point& who1,Point& who2){
        long long area = 1LL*x*who1.y - 1LL*y*who1.x +
                         1LL*who1.x*who2.y - 1LL*who1.y*who2.x +
                         1LL*who2.x*y - 1LL*who2.y*x ;
        return (area >= 0);
    }
    void operator=(const Point& who){
        x = who.x; y = who.y;
    }

    dPoint Rotate(double ang){
        dPoint ans ;

        ans.x = x; ans.y = y;
        ans.Rotate(ang);

        return ans;
    }

    double getAngle(){
        double ans = atan2( 1.00*y,1.00*x );
        return ans;
    }
};

int ConvexHull(int n,Point *P){
    Point tmp[maxN]; //! pe stiva...
    sort(P+1,P+n+1);

    int k = 1,i; tmp[k] = P[1];
    for(i=2;i<=n;i++){
        while(k>1 &&  P[i].upper(tmp[k-1],tmp[k]) ) k--;
        tmp[++k] = P[i];
    }

    int tt = k;
    for(i=n-1;i;i--){
        while(k>tt && P[i].upper(tmp[k-1],tmp[k]) ) k--;
        tmp[++k] = P[i];
    }

    //! in ordine trigonometrica
    for(i=1;i<=k;i++) P[k-i+1] = tmp[i];

    return k-1;
}

long n,i;
Point P[maxN];
dPoint act[maxN];
int whoLeft,whoRight,whoUp;

double trX,trY,trAng;
double ans;

double abss(double x){
    if(x>0) return x;
    return -x;
}
double testAnswer(){
    dPoint _up,_left,_right;
    _up = act[whoUp];
    _left = act[whoLeft];
    _right = act[whoRight];

    _up.apply(trX,trY,trAng);
    _left.apply(trX,trY,trAng);
    _right.apply(trX,trY,trAng);

    //cerr << abss(_up.y) * abss(_right.x - _left.x) << '\n';

    return abss(_up.y) * abss(_right.x - _left.x);
}

bool betterUp(int last,int nowp){
    if(nowp==n+1) nowp=1;
    dPoint _last = act[last];
    dPoint _now  = act[nowp];

    _last.apply(trX,trY,trAng);
    _now.apply(trX,trY,trAng);

    return(abss(_last.y) <= abss(_now.y));
}
bool betterLeft(int last,int nowp){
    if(nowp==n+1) nowp=1;
    dPoint _last = act[last];
    dPoint _now  = act[nowp];

    _last.apply(trX,trY,trAng);
    _now.apply(trX,trY,trAng);

    return(_last.x >= _now.x);
}
bool betterRight(int last,int nowp){
    if(nowp==n+1) nowp=1;
    dPoint _last = act[last];
    dPoint _now  = act[nowp];

    _last.apply(trX,trY,trAng);
    _now.apply(trX,trY,trAng);

    return(_last.x <= _now.x);
}
/*bool better(int lastA,int lastB,int nowp){
    if(nowp==n+1) nowp=1;
    dPoint _last1 = act[lastA];
    dPoint _last2 = act[lastB];
    dPoint _now  = act[nowp];

    _last1.apply(trX,trY,trAng);
    _last2.apply(trX,trY,trAng);
    _now.apply(trX,trY,trAng);

    double dd = abss( _last1.x-_last2.x );
    double dd2= abss( _last1.x-_now.x);

    return(dd2 >= dd);
}
*/

int main()
{
    freopen("rubarba.in","r",stdin);
    freopen("rubarba.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) P[i].read();
    n = ConvexHull(n,P);

    //! aducem pct in origine
    for(i=n+1;i;i--) { P[i].x -= P[1].x; P[i].y -= P[1].y; }

    //! rotim planul pt a avea prima latura pe OX cu un vf in O
    double ang = P[2].getAngle();
    for(i=1;i<=n+1;i++) act[i] = P[i].Rotate(-ang);

    //! setam datele initiale
    whoLeft = whoRight = whoUp = 1;
    for(i=2;i<=n;i++){
        if(act[whoLeft].x > act[i].x) whoLeft = i;
        if(act[whoRight].x < act[i].x) whoRight = i;
        if(act[whoUp].y < act[i].y) whoUp = i;
    }

    //! coliniare
    if( abss(act[whoUp].y) < 1e-15 ){
        printf("0.00");
        return 0;
    }

    //! setam ca solutie datele initiale
    trX = trY = trAng = 0;
    ans = testAnswer();

    //! hai la treaba..
    for(i=2;i<=n;i++){
        trX = act[i].x; trY = act[i].y;
        trAng = -act[i].getAngle(act[i+1]);

        while(betterUp( whoUp,whoUp+1 ))
            if(++whoUp==n+1) whoUp=1;
        while(betterLeft(whoLeft,whoLeft+1))
            if(++whoLeft==n+1) whoLeft=1;
        while(betterRight(whoRight,whoRight+1))
            if(++whoRight==n+1) whoRight=1;

        ans = min(ans,testAnswer());
    }

    printf("%.2lf",ans);
    cerr << setprecision(4) << ans;

    return 0;
}
