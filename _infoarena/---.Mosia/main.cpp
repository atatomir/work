#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxN 1024

struct Point{
    int x,y,d;

    void read(){scanf("%d %d %d",&x,&y,&d);}
    bool operator<(const Point& who)const{
        if(x==who.x) return y < who.y;
        return x < who.x;
    }
};

int n,i;
Point P[maxN];
int id[maxN];

double dp[maxN];
double ans;

bool soGood(int pp1,int pp2,int pp3){
    Point& p1 = P[pp1];
    Point& p2 = P[pp2];
    Point& p3 = P[pp3];

    long long area = 1LL*p1.x*p2.y - 1LL*p1.y*p2.x +
                     1LL*p2.x*p3.y - 1LL*p2.y*p3.x +
                     1LL*p3.x*p1.y - 1LL*p3.y*p1.x ;
    return (area > 0);
}
void convexHull(){
    long i,k,tt;

    id[1] = 1; k=1;
    for(i=2;i<=n;i++){
        while( k>1 && soGood(id[k-1],id[k],i) ) k--;
        id[++k] = i;
    }
    tt = k;

    for(i=n-1;i;i--){
        while(k>tt && soGood(id[k-1],id[k],i)) k--;
        id[++k] = i;
    }

    //cerr << k << '\n';
    //for(i=1;i<=k;i++) cerr << P[id[i]].x << ' ' <<P[id[i]].y <<  '\n';
}

double dist(Point& p1,Point& p2){
    return sqrt( 1.00*(p1.x-p2.x)*(p1.x-p2.x) + 1.00*(p1.y-p2.y)*(p1.y-p2.y) );
}
double getAdd(int id1,int id2,int id3){
    return 1.00*dist(P[id1],P[id3])*1.00*(double)P[id2].d;
}

int main()
{
    freopen("mosia.in","r",stdin);
    freopen("mosia.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) P[i].read();
    sort(P+1,P+n+1);

    convexHull();

    //! case I - first selected , cant select the last one
        dp[1] = getAdd( id[n],id[1],id[2] );
        dp[2] = dp[1];

        for(i=3;i<n;i++)
            dp[i] = max( dp[i-1],dp[i-2]+getAdd(id[i-1],id[i],id[i+1]) );

        ans = max(dp[n-1],dp[n-2]);

    //! case II - first unselected , can select the last one
        dp[1] = 0.00; dp[0] = 0.00;

        for(i=2;i<=n;i++)
            dp[i] = max( dp[i-1],dp[i-2]+getAdd(id[i-1],id[i],id[i+1]) );

        ans = max(ans,max( dp[n],dp[n-1] ));

    printf("%.4lf",ans/2.00);

    return 0;
}
