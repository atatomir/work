#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

#define maxN 100011

typedef pair<long,long> Point;

#define x first
#define y second
#define top first
#define bottom second
#define eps 0.000001

long n,p,i,par,s,cnt;
Point pts[maxN];
vector<Point> v;
Point val;

Point cAngle(long y,long x){
    Point Ans;
    Ans.top = y; Ans.bottom = x;
    if(Ans.bottom < 0){ Ans.top *= -1; Ans.bottom *= -1;}
    return Ans;
}

bool cmp(Point a,Point b){
    return 1LL*a.top*b.bottom < 1LL*b.top*a.bottom;
}

bool Equal(Point a,Point b){
    long long v1 = 1LL*a.top * b.bottom;
    long long v2 = 1LL*b.top * a.bottom;

    return v1 == v2;
}

int main()
{
    freopen("findinglines.in","r",stdin);
    freopen("findinglines.out","w",stdout);

    scanf("%ld %ld",&n,&p);
    if(n == 1){
        printf("possible");
        return 0;
    }

    p = n * p;
    if(p % 100 == 0){
        p = p/100;
    } else {
        p = (p/100) + 1;
    }
    p--;

    for(i=1;i<=n;i++) scanf("%ld %ld",&pts[i].x,&pts[i].y);

    srand(time(NULL));
    for(long t=500;t;t--){
        par = rand()%n + 1; s = -1; v.clear();
        for(i=1;i<=n;i++){
            v.push_back(cAngle(pts[i].y - pts[par].y , pts[i].x - pts[par].x));
        }
        sort(v.begin(),v.end(),cmp);

        if(v[0].top == 0 & v[0].bottom == 0) {
            Point tmp = v[0] ; v[0] = v[v.size()-1]; v[v.size()-1] = tmp;
        }

        val = v[0]; cnt = 1;
        for(i=1;i<v.size();i++){
            if(v[i].top == 0 && v[i].bottom == 0) continue;

            if(Equal(v[i],val)) cnt++; else {
                val = v[i]; cnt = 1;
            }

            if(cnt >= p){
                printf("possible");
                return 0;
            }
        }
    }

    printf("impossible");

    return 0;
}
