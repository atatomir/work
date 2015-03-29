#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

#define maxN 1024
#define eps 0.000000000000001
#define rAlfa 0.000013

struct Point{
    long double x,y;
    long id;
};
bool cmp(const Point& a,const Point& b){
    return a.x < b.x;
}

struct Line{
    long double x,tg;
    long id;
};
bool cmpTg(const Line& a,const Line& b){
    return a.tg < b.tg;
}
bool cmpX(const Line& a,const Line& b){
    return a.x<b.x;
}

long n,i,j,q;
Point p[maxN];
long double cosAlfa,sinAlfa;
long downDr[maxN][maxN],upDr[maxN][maxN];

Line act[maxN];
long cnt;

long aib[maxN];
long idd[maxN],p1,p2,p3;

void Rotate(Point& p){
    static Point tmp;
    tmp = p;
    p.x = tmp.x*cosAlfa - tmp.y*sinAlfa;
    p.y = tmp.x*sinAlfa + tmp.y*cosAlfa;
}

inline long zeros(long x){return (x^(x-1))&x;}
void addAib(long x){
    while(x<=cnt){
        aib[x]++;
        x += zeros(x);
    }
}
long sumAib(long x){
    long ans=0;
    while(x){
        ans += aib[x];
        x -= zeros(x);
    }
    return ans;
}

inline bool under(long p1,long p2,Point pp){
    static long double tmp;
    tmp = (p[p1].x*p[p2].y - p[p2].x*p[p1].y) +
          (p[p2].x*pp.y - pp.x*p[p2].y) +
          (pp.x*p[p1].y - p[p1].x*pp.y) ;
    if(tmp < 0) return true;
    return false;
}

int main()
{
    freopen("tri2.in","r",stdin);
    freopen("tri2.out","w",stdout);

    sinAlfa = sin(rAlfa); cosAlfa = cos(rAlfa);
    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%llf %llf",&p[i].x,&p[i].y);
        Rotate(p[i]);
        p[i].id = i;
    }
    sort(p+1,p+n+1,cmp);
    for(i=1;i<=n;i++) idd[p[i].id] = i;

    for(i=1;i<n;i++){
        cnt = n-i;
        for(j=i+1;j<=n;j++){
            act[j-i].id = j;
            act[j-i].x = p[j].x;
            act[j-i].tg = (p[j].y-p[i].y)/(p[j].x-p[i].x);
        }

        sort(act+1,act+cnt+1,cmpX);
        for(j=1;j<=cnt;j++) {act[j].x = j;aib[j]=0;} //! normalizare

        sort(act+1,act+cnt+1,cmpTg); //! preprocesam
        for(j=1;j<=cnt;j++){
            long xx = act[j].x;
            downDr[i][act[j].id] = sumAib(xx);
            addAib(xx);
        }
    }

    for(i=1;i<=n;i++)
        for(j=i+1;j<=n;j++) upDr[i][j] = j-i-1 - downDr[i][j];

    scanf("%ld",&q);
    for(i=1;i<=q;i++){
        scanf("%ld %ld %ld",&p1,&p2,&p3);
        p1 = idd[p1]; p2 = idd[p2]; p3 = idd[p3];

        if(p[p2].x>p[p3].x) swap(p2,p3);
        if(p[p1].x>p[p2].x) swap(p1,p2);
        if(p[p2].x>p[p3].x) swap(p2,p3);

        Point tmp;
        tmp.x = (p[p1].x+p[p2].x+p[p3].x)/3;
        tmp.y = (p[p1].y+p[p2].y+p[p3].y)/3;

        long ans=p3-p1-2;
        if(under(p1,p2,tmp)) ans -= upDr[p1][p2]; else ans -= downDr[p1][p2];
        if(under(p2,p3,tmp)) ans -= upDr[p2][p3]; else ans -= downDr[p2][p3];
        if(under(p1,p3,tmp)) ans -= upDr[p1][p3]; else ans -= downDr[p1][p3];

        printf("%ld\n",ans);
    }

    return 0;
}
