#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define x first
#define y second
#define ff first
#define ss second
typedef pair<long long,long long> Point;

#define maxN 100011

long n,m,i;
Point a[maxN],v[maxN],tmp,tmpL;
long f[maxN],s[maxN];
long long fX[maxN],fY[maxN];
long long sX[maxN],sY[maxN];
long posF,posS;

long long Ans;

long getFirst(Point p){
    // y = x + b;
    long b = p.y-p.x;
    return -b;
}
long getSecond(Point p){
    // y = -x + b;
    long b = p.y+p.x;
    return b;
}

bool cmpF(long aa,long bb){
    return a[aa].ff < a[bb].ff;
}
bool cmpS(long aa,long bb){
    return a[aa].ss < a[bb].ss;
}

long getPosF(long x){
    long i=1,j=n,m;
    while(i<=j){
        m = (i+j)/2;
        if(x<=a[f[m]].ff)
            j = m-1;
        else
            i = m+1;
    }
    return j;
}
long getPosS(long x){
    long i=1,j=n,m;
    while(i<=j){
        m = (i+j)/2;
        if(x<=a[s[m]].ss)
            j = m-1;
        else
            i = m+1;
    }
    return j;
}

long long CalcY(){
    long long v1 = fY[posF] - posF*tmp.y;
    long long v2 = sY[posS] - posS*tmp.y;
    if(v1 > v2) return v1-v2;
    return v2-v1;
}
long long CalcX(){
    long long v1 = fX[posF] - posF*tmp.x;
    long long v2 = sX[n]-sX[posS] - (n-posS)*tmp.x;
    if(v1 > v2) return v1-v2;
    return v2-v1;
}

int main()
{
    freopen("distancesum.in","r",stdin);
    freopen("distancesum.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++) {
        scanf("%lld %lld",&tmp.x,&tmp.y);
        v[i] = tmp;
        a[i].ff = getFirst(tmp); a[i].ss = getSecond(tmp);
        f[i] = s[i] = i;
    }

    sort(f+1,f+n+1,cmpF);
    sort(s+1,s+n+1,cmpS);

    for(i=1;i<=n;i++){
        fX[i] = fX[i-1] + v[f[i]].x;
        fY[i] = fY[i-1] + v[f[i]].y;

        sX[i] = sX[i-1] + v[s[i]].x;
        sY[i] = sY[i-1] + v[s[i]].y;
    }

    for(;m;m--){
        scanf("%lld %lld",&tmp.x,&tmp.y);
        tmpL.ff = getFirst(tmp);
        tmpL.ss = getSecond(tmp);

        posF = getPosF(tmpL.ff);
        posS = getPosS(tmpL.ss);

        Ans  = CalcY();
        Ans += CalcX();

        printf("%lld\n",Ans);
    }

    return 0;
}
