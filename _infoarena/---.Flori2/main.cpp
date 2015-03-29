#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxN 1011
#define eps 0.0000000000001
#define INF 99999999999999

struct Point{
    long x,y;
};

long t,n,i,j,x,y,ans,act,cnt,pi;
Point pct[maxN];
double angle[maxN],def;

bool Equal(double x,double y){
    x-=y;if(x<0) x*= -1.00;
    return (x<=eps);
}

int main()
{
    freopen("flori2.in","r",stdin);
    freopen("flori2.out","w",stdout);

    scanf("%ld",&t); pi = acos(-1);
    for(;t;t--){
        scanf("%ld",&n); ans=1;
        for(i=1;i<=n;i++)scanf("%ld %ld",&pct[i].x,&pct[i].y);
        for(i=1;i<=n;i++){
            cnt=0;
            for(j=1;j<=n;j++){
                if(i==j) continue;
                if(pct[j].x==pct[i].x) angle[++cnt] = INF; else
                angle[++cnt] = 1.00*(pct[j].y-pct[i].y)/(pct[j].x-pct[i].x);
            }
            sort(angle+1,angle+cnt+1);

            j=1;
            for(;j<=cnt;j++){
                act = 2; def = angle[j];
                while(j<cnt&&Equal(angle[j+1],def)) {j++;act++;}
                ans = max(ans,act);
            }
        }

        printf("%ld\n",ans);
    }

    return 0;
}
