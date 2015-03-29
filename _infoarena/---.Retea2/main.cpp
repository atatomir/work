#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

#define maxN 4015
#define INF 200000000000000.00

struct Point {
    double x,y;
};

long n,m,i,j;
bool used[maxN];
Point p[maxN];
double dist[maxN],ans;

double minVal;
long minPos;

inline double getDist(Point& p1,Point& p2){
    return sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}

int main()
{
    freopen("retea2.in","r",stdin);
    freopen("retea2.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++) scanf("%lf %lf",&p[i].x,&p[i].y);
    for(i=n+1;i<=n+m;i++) scanf("%lf %lf",&p[i].x,&p[i].y);

    for(i=1;i<=n;i++) used[i]=true;
    for(i=1;i<=n;i++){
        for(j=n+1;j<=n+m;j++){
            double dst = getDist(p[i],p[j]);
            if(dist[j]==0.00 || dist[j]>dst) dist[j] = dst;
        }
    }

    for(long cnt=m;cnt;cnt--){
        minVal = INF;
        for(i=n+1;i<=n+m;i++){
            if(used[i]) continue;
            if(minVal > dist[i]){
                minVal = dist[i];
                minPos = i;
            }
        }

        ans += minVal;
        used[minPos] = true;
        for(i=n+1;i<=n+m;i++){
            if(used[i]) continue;
            dist[i] = min(dist[i],getDist(p[minPos],p[i]));
        }
    }

    printf("%.6lf",ans);

    return 0;
}
