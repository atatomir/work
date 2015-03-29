#include <iostream>
#include <cstdio>

using namespace std;

struct Point{
    long long x,y;
};

long n,i,p1,p2,p3,q;
Point p[1024];

long area(Point p1,Point p2,Point p3){
    long long ans =0;
    ans += (p1.x*p2.y-p2.x*p1.y)+(p2.x*p3.y-p3.x*p2.y)+(p3.x*p1.y-p1.x*p3.y);
    if(ans<0) return -1;
    return 1;
}

int main()
{
    freopen("tri2.in","r",stdin);
    freopen("tri2.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%ld%ld",&p[i].x,&p[i].y);

    scanf("%ld",&q);
    for(;q;q--){
        scanf("%ld%ld%ld",&p1,&p2,&p3);
        long ans=0;
        for(i=1;i<=n;i++){
            if(i==p1 || i==p2 || i==p3) continue;
            if(area(p[i],p[p1],p[p2])==area(p[i],p[p2],p[p3]))
                if(area(p[i],p[p1],p[p2])==area(p[i],p[p3],p[p1])) ans++;
        }
        printf("%ld\n",ans);
    }

    return 0;
}
