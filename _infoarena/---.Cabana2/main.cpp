#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

struct Point{
    long x,y,id;
    Point(){x=y=id=0;}
    Point(long _x,long _y,long _id){
        x=_x; y=_y; id=_id;
    }
};
bool cmpX(const Point& a,const Point& b){
    if(a.x==b.x) return a.y < b.y;
    return a.x<b.x;
}
bool cmpY(const Point& a,const Point& b){
    if(a.y==b.y) return a.x < b.x;
    return a.y < b.y;
}

#define maxN 50011
#define lSon (node<<1)
#define rSon ((node<<1)|1)
#define x1 xx1
#define x2 xx2
#define y1 yy1
#define y2 yy2
#define INF 1000000005

long n,i,x,y,x2,y2;
Point byX[maxN],byY[maxN];
long nxt[maxN];
set<pair<long,long> > H;
long long Answer=0;

//!! ---------------------------------

vector<long> aint[maxN<<2];
vector<long> ids;

void makeAint(long node,long l,long r){
    if(l==r){
        aint[node].resize(1);
        aint[node][0] = byX[l].y;
        return;
    }

    long m = (l+r)>>1;
    makeAint(lSon,l,m);
    makeAint(rSon,m+1,r);

    aint[node].resize(aint[lSon].size()+aint[rSon].size());
    merge(aint[lSon].begin(),aint[lSon].end() , aint[rSon].begin(),aint[rSon].end() , aint[node].begin());
}

long cbF(long x){
    long i=1,j=n,m;
    while(i<=j){
        m = (i+j)>>1;
        if(x <= byX[m].x)
            j = m-1;
        else
            i = m+1;
    }
    return i;
}

long cbS(long x){
    long i=1,j=n,m;
    while(i<=j){
        m = (i+j)>>1;
        if(x < byX[m].x)
            j = m-1;
        else
            i = m+1;
    }
    return j;
}

long getLow(long id,long x){
    long node = id;
    long i=0,j=aint[node].size()-1,m;
    while(i<=j){
        m = (i+j)>>1;
        if(x <= aint[node][m])
            j = m-1;
        else
            i = m+1;
    }
    return i+1;
}

long getHigh(long id,long x){
    long node = id;
    long i=0,j=aint[node].size()-1,m;
    while(i<=j){
        m = (i+j)>>1;
        if(x < aint[node][m])
            j = m-1;
        else
            i = m+1;
    }
    return j+1;
}

void Query(long node,long l,long r,long qL,long qR){
    if(qL <= l && r <= qR) {ids.push_back(node);return;}
    if(l>r) return ;

    long m=(l+r)>>1;
    if(qL<=m) Query(lSon,l,m,qL,qR);
    if(qR> m) Query(rSon,m+1,r,qL,qR);
}

long howMany(long x1,long x2,long y1,long y2){
    ids.clear();
    Query(1,1,n,cbF(x1),cbS(x2));

    long ans = 0;
    for(vector<long>::iterator it=ids.begin();it!=ids.end();it++){
        ans += -getLow(*it,y1) + getHigh(*it,y2)+1;
    }

    return ans;
}

//!! ---------------------------------

int main()
{
    freopen("cabana2.in","r",stdin);
    freopen("cabana2.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld %ld",&x,&y);
        byX[i] = byY[i] = Point(x,y,i);
        H.insert(make_pair(x,y));
    }

    sort(byX+1,byX+n+1,cmpX);
    sort(byY+1,byY+n+1,cmpY);

    for(i=1;i<=n;i++) nxt[i] = INF;
    for(i=1;i<n;i++){
        if(byY[i].y != byY[i+1].y) continue;
        nxt[byY[i].id] = byY[i+1].x;
    }

    makeAint(1,1,n);
    for(i=1;i<n;i++){
        if(byX[i].x != byX[i+1].x) continue;

        x = byX[i].x; y = byX[i].y;
        x2 = nxt[byX[i].id]; y2 = byX[i+1].y;

        if(x2 == INF || H.count(make_pair(x2,y2))==0 ) continue;
        if(howMany(x,x2,y,y2)!=4) continue;
        Answer = max(Answer,1LL*(x2-x)*(y2-y));
    }

    printf("%lld",Answer);


    return 0;
}
