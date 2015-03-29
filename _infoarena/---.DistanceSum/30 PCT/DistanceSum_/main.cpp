#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define maxBlocks 700
#define Blks Blocks

#define x first
#define y second
typedef pair<long,long> Point;
Point pp;

#define INF (1000000)
struct Area{
    long x1,x2,y1,y2;
    vector<Point> pts;
    long long sumX,sumY;

    void init(){
        x1 = y1 = INF;
        x2 = y2 = -INF;

        pts.clear();
        sumX = sumY = 0;
    }
    void add(Point p){
        pts.push_back(p);
        x1 = min(x1,p.x);
        y1 = min(y1,p.y);
        x2 = max(x2,p.x);
        y2 = max(y2,p.y);

        sumX += p.x ;
        sumY += p.y ;
    }
};

long n,m,i,x,y,posmpp,posspp;
long dim;
vector<Point> v;
long long Ans;

Area Blocks[maxBlocks];
long bMax;

inline long posMain(Point p){
    // y = x + b
    long b = p.y - p.x;
    return b;
}
inline long posSecond(Point p){
    // y = -x + b
    long b = p.y + p.x;
    return b;
}

long leftMain(Point p1){
    //if(posMain(p1) == posMain(p2)) return -1;
    return posMain(p1) > posmpp;
}
long leftSecond(Point p1){
    //if(posSecond(p1) == posSecond(p2)) return -1;
    return posSecond(p1) > posspp;
}

long getRegion(Point p){
    long b1 = leftMain(p);
    long b2 = leftSecond(p);

    if(b1 == 1 && b2 == 1) return 1;
    if(b1 == 1 && b2 == 0) return 2;
    if(b1 == 0 && b2 == 1) return 4;
    if(b1 == 0 && b2 == 0) return 3;
    return -1;
}

long getNeed(long id){
    long r[5];
    r[1] = getRegion(make_pair(Blks[id].x1,Blks[id].y1));
    r[2] = getRegion(make_pair(Blks[id].x1,Blks[id].y2));
    r[3] = getRegion(make_pair(Blks[id].x2,Blks[id].y1));
    r[4] = getRegion(make_pair(Blks[id].x2,Blks[id].y2));

    /* 0 brute */
    if(r[1] == r[2] && r[2] == r[3] && r[3] == r[4] && (r[4]%2)) return 2;
    if(r[1] == r[2] && r[2] == r[3] && r[3] == r[4] && !(r[4]%2)) return 1;
    return 0;

    if(Blks[id].x1 <= pp.x && Blks[id].x2 >= pp.x &&
       Blks[id].y1 <= pp.y && Blks[id].y2 >= pp.y) return 0;

    long cmp,i;
    for(i=1;i<=4;i++) if(r[i] != -1) cmp = r[i];
    for(i=1;i<=4;i++) if(r[i] != -1 && r[i] != cmp) return 0;

    /* 1 pt x ; 2 pt y */
    if(cmp == 1 || cmp == 3) return 1; else return 2;
}

inline long long abss(long long x){
    if(x < 0) return -x;
    return x;
}

void Brute(long id){
    for(long i=0;i<Blks[id].pts.size();i++){
        Ans += max(abss(pp.x-Blks[id].pts[i].x),abss(pp.y-Blks[id].pts[i].y));
    }
}

void fastX(long id){
    long long tmp = 0;
    tmp = 1LL*pp.x*Blks[id].pts.size() - Blks[id].sumX;

    Ans += abss(tmp);

}

void fastY(long id){
    long long tmp = 0;
    tmp = 1LL*pp.y*Blks[id].pts.size() - Blks[id].sumY;
    Ans += abss(tmp);
}

bool compare(Point a,Point b){
    a.x /= 100; a.y /= 100;
    b.x /= 100; b.y /= 100;
    if(a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}


int main()
{
    freopen("distancesum.in","r",stdin);
    freopen("distancesum.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    dim = (long)sqrt((double)n);
//dim = dim*10;
dim = dim / 2;
if (dim == 0 ) dim = 1;

    v.resize(n);
    for(i=0;i<n;i++) scanf("%ld %ld",&v[i].x,&v[i].y);
    sort(v.begin(),v.end(),compare);

    for(i=0;i<=maxBlocks-5;i++) Blks[i].init();

    for(i=0;i<n;i++) Blocks[i/dim].add(v[i]);
    bMax = (n-1)/dim;

    map<Point,long long> M;
    for(;m;m--){
        scanf("%ld %ld",&pp.x,&pp.y); Ans = 0;
        if(M.count(pp)){
            printf("%lld\n",M[pp]);
            continue;
        }
        posmpp= posMain(pp);
        posspp= posSecond(pp);
        for(i=0;i<=bMax;i++){
            long need = getNeed(i);

            if(need == 0) Brute(i); else
            if(need == 1) fastX(i); else
                          fastY(i);
            //Brute(i);
        }

        printf("%lld\n",Ans);
        M[pp] = Ans;
    }

    return 0;
}
