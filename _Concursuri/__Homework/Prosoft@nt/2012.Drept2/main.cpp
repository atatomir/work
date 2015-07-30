#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define p1 first
#define p2 second
#define x first
#define y second
#define mp make_pair

typedef pair<long,long> Point;
typedef pair<Point,Point> Drept;

long w,h,i;
long long aF,aI;
Drept def,tmp,act;
Point p;
vector<Drept> ans;

inline long abss(long x){
    if(x<0) return -x;
    return x;
}

void Try(){
    act = tmp;
    if(act.p1.x>act.p2.x) swap(act.p1.x,act.p2.x);
    if(act.p1.y>act.p2.y) swap(act.p1.y,act.p2.y);

    long xx1,xx2,yy1,yy2;
    xx1 = max(def.p1.x,act.p1.x);
    xx2 = min(def.p2.x,act.p2.x);
    yy1 = max(def.p1.y,act.p1.y);
    yy2 = min(def.p2.y,act.p2.y);

    if(xx1>=xx2 || yy1>=yy2) return;
    if(1LL*(xx2-xx1)*(yy2-yy1)!=aI) return;

    ans.push_back(act);
}

int main()
{
    freopen("drept2.in","r",stdin);
    freopen("drept2.out","w",stdout);

    scanf("%ld %ld",&w,&h);
    scanf("%ld%ld%ld%ld",&def.p1.x,&def.p2.x,&def.p1.y,&def.p2.y);
    scanf("%lld%lld",&p.x,&p.y);
    scanf("%lld%lld",&aF,&aI);

    if(def.p1.x>def.p2.x) swap(def.p1.x,def.p2.x);
    if(def.p1.y>def.p2.y) swap(def.p1.y,def.p2.y);

    tmp.p2 = p;
    for(tmp.p1.x=0;tmp.p1.x<=w;tmp.p1.x++){
        long long xAct,yAct;
        xAct = abss(p.x-tmp.p1.x); if(xAct==0) continue;

        if(aF%xAct!=0) continue;
        yAct = aF/xAct;

        tmp.p1.y = p.y-yAct;
        if(tmp.p1.y >= 0) Try();
        tmp.p1.y = p.y+yAct;
        if(tmp.p1.y <= h) Try();
    }

    printf("%ld\n",ans.size());
    for(i=0;i<ans.size();i++){
        printf("%ld %ld %ld %ld\n",ans[i].p1.x,ans[i].p2.x,ans[i].p1.y,ans[i].p2.y);
    }

    return 0;
}
