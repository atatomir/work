#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>

using namespace std;

#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 50011

struct Point{
    int x,y;

    void init(){
        scanf("%d%d",&x,&y);
    };
    bool operator<(const Point& who) const {
        if (x==who.x) return y < who.y;
        return x < who.x;
    }
};

int n,i,l,r,mid;
Point P[maxN];
bitset<maxN> valid[5];

void use_a_square(int how,int lim,int x,int y){
    int lim_x = x+lim;
    int lim_y = y+lim;

    for (int i=1;i<=n;i++){
        if (P[i].x>lim_x) break;
        if (P[i].x<x || P[i].y<y || P[i].y>lim_y) continue;
        valid[how][i] = true;
    }
}


bool check(int lim,int how){
    if (valid[how].count()==n) return true;
    if (how==0) return false;

    int Square_minx,Square_miny;
    int Square_maxx,Square_maxy;

    Square_minx = 1<<30;
    Square_maxx = -1;
    Square_miny = 1<<30;
    Square_maxy = -1;
    for (i=1;i<=n;i++){
        if(valid[how][i]) continue;

        Square_miny = min(Square_miny,P[i].y);
        Square_maxy = max(Square_maxy,P[i].y);
        Square_minx = min(Square_minx,P[i].x);
        Square_maxx = max(Square_maxx,P[i].x);
    }

    if(how==1) return max( Square_maxx-Square_minx,Square_maxy-Square_miny ) <= lim;


    //! case 1
        valid[how-1] = valid[how];
        use_a_square(how-1,lim,Square_minx,Square_miny);
        if ( check(lim,how-1) ) return true;

    //! case 2
        valid[how-1] = valid[how];
        use_a_square(how-1,lim,Square_minx,Square_maxy-lim);
        if ( check(lim,how-1) ) return true;

    if(how==2) return false;

    //! case 3
        valid[how-1] = valid[how];
        use_a_square(how-1,lim,Square_maxx-lim,Square_miny);
        if ( check(lim,how-1) ) return true;

    //! case 4
        valid[how-1] = valid[how];
        use_a_square(how-1,lim,Square_maxx-lim,Square_maxy-lim);
        if ( check(lim,how-1) ) return true;

    return false;
}

int main()
{
    freopen("patrate.in","r",stdin);
    freopen("patrate.out","w",stdout);

    scanf("%d",&n);
    for (i=1;i<=n;i++) P[i].init();
    sort(P+1,P+n+1);

    valid[4].reset();

    l=0;r=50000;
    while (l<=r) {
        mid = (l+r)>>1;
        if (check(mid,3))
            r = mid-1;
        else
            l = mid+1;
    }

    printf("%d",l);

    return 0;
}
