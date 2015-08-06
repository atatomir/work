#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 100011
#define maxVal 1000011

struct Point{
    int x,y;
    void read(){scanf("%d%d",&x,&y);}
    bool operator<(const Point& who)const{
        if(x!=who.x) return x<who.x;
        return y<who.y;
    }
};

int n,i,l,r,mid;
Point P[maxN];
int ymin[maxN],ymax[maxN];

int abss(int x){
    if(x<0) return -x;
    return x;
}
bool check(int lim){
    int p1,p2;

    p1 = 0; p2=1;
    fordef(p1,1,n){
        while(P[p2].x-P[p1].x < lim) p2++;
        if(p2==n+1) return false;

        int yy = ymin[p2];
        if( abss(P[p1].y-yy) >= lim) return true;

        /**/ yy = ymax[p2];
        if( abss(P[p1].y-yy) >= lim) return true;
    }

    return false;
}

int main()
{
    freopen("dist2.in","r",stdin);
    freopen("dist2.out","w",stdout);

    scanf("%d",&n);
    fordef(i,1,n) P[i].read();
    sort(P+1,P+n+1);
    P[n+1].x = P[n+1].y = 1e9;

    ymin[n]=ymax[n] = P[n].y;
    for(i=n-1;i>0;i--) {
        ymin[i]=min(ymin[i+1],P[i].y);
        ymax[i]=max(ymax[i+1],P[i].y);
    }

    l = 0; r=10000000;
    while(l<=r){
        mid = (l+r)>>1;
        if(check(mid))
            l = mid+1;
        else
            r = mid-1;
    }

    printf("%d",r);

    return 0;
}
