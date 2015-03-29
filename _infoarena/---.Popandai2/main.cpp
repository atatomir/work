#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 2011

struct Point{
    double x,y;
};

long n,i,a,b,c,d;
Point P[maxN];
double ans=-1,act,maxAr,maxPos;
bool do_it;

double Area(Point p1,Point p2,Point p3){
    double ans=0;
    ans = (p1.x*p2.y)-(p2.x*p1.y)+
          (p2.x*p3.y)-(p3.x*p2.y)+
          (p3.x*p1.y)-(p1.x*p3.y);
    if(ans<0) ans*=-1.00;
    return ans/2;
}
double Area(Point p1,Point p2,Point p3,Point p4){
    return Area(p1,p2,p3)+Area(p1,p3,p4);
}

int main()
{
    freopen("popandai2.in","r",stdin);
    freopen("popandai2.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) {scanf("%lf%lf",&P[i].x,&P[i].y);P[i+n]=P[i];}

    for(a=1;a<=n;a++){
        b = a+1; c=b+1;
        act = Area(P[a],P[b],P[c]);

        maxAr = Area(P[a],P[c],P[c+1]); maxPos = c+1;
        for(d=c+2;d-n<a;d++){
            double actAr = Area(P[a],P[c],P[d]);
            if(actAr>maxAr){
                maxAr = actAr;
                maxPos = d;
            }
        }
        d=maxPos; act += maxAr;

        for(;c-n<a-1;c++){
            if(c==d) d++;
            act = Area(P[a],P[b],P[c],P[d]);

            do_it=true;
            while(do_it){
                do_it=false;
                if(b+1!=c){
                    double tmp = Area(P[a],P[b+1],P[c],P[d]);
                    if(tmp>act){
                        act = tmp;
                        b++; do_it=true;
                    }
                }
            }

            do_it=true;
            while(do_it){
                do_it=false;
                if(d+1!=a){
                    double tmp = Area(P[a],P[b],P[c],P[d+1]);
                    if(tmp>act){
                        act = tmp;
                        d++; do_it=true;
                    }
                }
            }

            //!!
            ans = max(ans,act);
        }
    }

    printf("%.1lf",ans);

    return 0;
}
