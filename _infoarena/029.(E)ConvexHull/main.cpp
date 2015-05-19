#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define maxN 120022
#define eps 0.000000000001
#define PI pair<double,double>
#define x first
#define y second

long n,i,k;
pair<double,double> p[maxN];
pair<double,double> Hull[maxN];

bool upper(PI &p1,PI &p2,PI &p3){
    double Area = (p1.x*p2.y)-(p1.y*p2.x) +
                  (p2.x*p3.y)-(p2.y*p3.x) +
                  (p3.x*p1.y)-(p3.y*p1.x);

    if(Area >= -eps) return true;
    return false;
}

int main()
{
    freopen("infasuratoare.in","r",stdin);
    freopen("infasuratoare.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%lf%lf",&p[i].first,&p[i].second);
    sort(p+1,p+n+1);

    for(i=1;i<=n;i++){
        while(k>=2 && upper(Hull[k-1],Hull[k],p[i])) k--;
        Hull[++k] = p[i];
    }

    long lim = k;
    for(i=n-1;i;i--){
        while(k>=lim+1 && upper(Hull[k-1],Hull[k],p[i])) k--;
        Hull[++k] = p[i];
    }

    printf("%ld\n",k-1);
    for(i=k;i>1;i--) printf("%.6lf %.6lf\n",Hull[i].first,Hull[i].second);

    return 0;
}
