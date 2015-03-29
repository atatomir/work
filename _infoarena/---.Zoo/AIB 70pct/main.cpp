#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef pair<long,long> Point;
typedef pair<long,long> norY;
struct sQuery{
    Point p;
    long id,sign;
};

#define maxN 16010
#define maxM 100010
#define x first
#define y second
#define p1 first
#define p2 second
#define val first
#define ID second

Point p[maxN];
long Q[maxM];
sQuery sQ[maxM << 2];
norY nY[maxN];
long n,m,i,cQ;
Point p1,p2;
long pos=1,caut;

long aib[maxN];

inline void addQ(long xx,long yy,long s){
    sQ[++cQ].p.x  = xx;
    sQ[  cQ].p.y  = yy;
    sQ[  cQ].sign = s;
    sQ[  cQ].id   = i;
}

bool qCMP(const sQuery& a,const sQuery& b){
    return a.p.x < b.p.x;
}

bool yCMP(const norY& a,const norY& b){
    return a.val < b.val;
}

inline long zeros(long x){
    return (x^(x-1))&x;
}

void add(long pos){
    while(pos <= n){
        aib[pos]++;;
        pos += zeros(pos);
    }
}

long sum(long pos){
    long answer=0;
    while(pos){
        answer += aib[pos];
        pos -= zeros(pos);
    }
    return answer;
}

long cb(long src){
    long i=1,j=n,m;
    do {
        m = (i+j) >> 1;
        if(src < nY[m].val)
            j = m-1;
        else
            i = m+1;
    }   while(i<=j);
    return j;
}

int main()
{
    freopen("zoo.in","r",stdin);
    freopen("zoo.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld %ld",&p[i].x,&p[i].y);
    }
    sort(p+1,p+n+1);
    for(i=1;i<=n;i++) {
        nY[i].val = p[i].y;
        nY[i].ID  = i;
    }
    sort(nY+1,nY+n+1,yCMP);
    for(i=1;i<=n;i++) p[nY[i].ID].y = i;

    scanf("%ld",&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld %ld %ld",&p1.x,&p1.y,&p2.x,&p2.y);
        addQ(p2.x,p2.y,+1);
        addQ(p2.x,p1.y-1,-1);
        addQ(p1.x-1,p2.y,-1);
        addQ(p1.x-1,p1.y-1,+1);
    }
    sort(sQ+1,sQ+cQ+1,qCMP);

    for(i=1;i<=cQ;i++){
        while((p[pos].x <= sQ[i].p.x)&&(pos <= n))
            add(p[pos++].y);
        caut = cb(sQ[i].p.y);
        Q[sQ[i].id] += sQ[i].sign*sum(caut);
    }

    for(i=1;i<=m;i++) printf("%ld\n",Q[i]);

    return 0;
}
