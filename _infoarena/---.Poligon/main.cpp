#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

#define maxN 810
#define x first
#define y second
#define p1 first
#define p2 second
#define angle 0.73
#define eps 1e-6
#define pb push_back
#define A first
#define B second

typedef pair<double,double> Point;
typedef pair<Point,Point> Segment;
typedef pair<double,double> CordSegment;

long n,m,i,gr;
Point p[maxN];
vector<double> vx;
Segment sgm[maxN];
vector<CordSegment> group[maxN << 1];
Point aux;
Segment saux;
CordSegment caux;
double start,stop;
long Answer;
long step,cbGroup,pos,sgmCont;

Point Rotate(Point p){
    Point ans;
    ans.x = cos(angle)*p.x - sin(angle)*p.y;
    ans.y = sin(angle)*p.x + cos(angle)*p.y;
    return ans;
}

bool cmp(const CordSegment& a,const CordSegment& b){
    double y1,y2,mid=(start+stop)/2;
    y1 = a.A*mid+a.B;
    y2 = b.A*mid+b.B;
    return y1 < y2;
}

bool Equal(double a,double b){
    double dif = a - b;
    if(dif < 0) dif = -dif;
    return dif < eps;
}

bool isBelow(Point p,CordSegment segm){
    return p.y > segm.A*p.x+segm.B;
}

bool onEdge(Point p,CordSegment segm){
    return Equal(p.y,segm.A*p.x+segm.B);
}

int main()
{
    freopen("poligon.in","r",stdin);
    freopen("poligon.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++){
        scanf("%lf %lf",&aux.x,&aux.y);
        aux = Rotate(aux);
        p[i] = aux;
        vx.pb(aux.x);
    }
    p[n+1] = p[1];
    for(i=1;i<=n;i++){
        saux.p1 = p[i];
        saux.p2 = p[i+1];
        if(saux.p1.x > saux.p2.x){
            saux.p1 = p[i+1];
            saux.p2 = p[i];
        }
        sgm[sgmCont++]=saux;
    }
    sort(vx.begin(),vx.end());

    for(gr=1;gr<vx.size();gr++){
        start = vx[gr-1]; stop = vx[gr];
        for(i=0;i<sgmCont;i++){
            if(sgm[i].p1.x <= start && stop <= sgm[i].p2.x){
                caux.A = (sgm[i].p1.y - sgm[i].p2.y)/(sgm[i].p1.x - sgm[i].p2.x);
                caux.B = ((sgm[i].p2.y * sgm[i].p1.x)-(sgm[i].p1.y * sgm[i].p2.x))/(sgm[i].p1.x - sgm[i].p2.x);
                group[gr].pb(caux);
            }
        }

        sort(group[gr].begin(),group[gr].end(),cmp);
    }

    for(i=1;i<=m;i++){
        scanf("%lf %lf",&aux.x,&aux.y);
        aux = Rotate(aux);
        if((aux.x < vx[0])||(vx[vx.size()-1] < aux.x))
            if((!Equal(aux.x,vx[0]))&&(!Equal(vx[vx.size()-1],aux.x)))
                continue;

        step = 1; cbGroup = -1;
        while(step <= vx.size()) step <<= 1;
        for(;step;step >>= 1){
            if(cbGroup+step < vx.size()){
                if(vx[cbGroup+step] <= aux.x) cbGroup += step;
            }
        }
        cbGroup++;

        step = 1; pos = -1;
        while(step <= group[cbGroup].size()) step <<= 1;
        for(;step;step >>= 1){
            if(step+pos < group[cbGroup].size()){
                if(onEdge(aux,group[cbGroup][step+pos])){
                    pos = 0; break;
                } else
                if(isBelow(aux,group[cbGroup][step+pos])) pos += step;
            }
        }
        pos++;
        Answer += pos&1;
    }

    printf("%ld\n",Answer);

    return 0;
}
