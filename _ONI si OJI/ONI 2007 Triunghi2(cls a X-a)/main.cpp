#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

#define x first
#define y second
#define n1 first
#define n2 second.first
#define n3 second.second
#define maxN 75

typedef pair<long,long> Point;
typedef pair<Point,pair<Point,Point> > Triangle;

long n,i,j,k;
Triangle v[maxN];
Point f;

vector<long> ans;
long Answer;

long Sign(Point a,Point b,Point c){
    long ans = a.x*b.y-a.y*b.x + b.x*c.y-b.y*c.x + c.x*a.y-c.y*a.x;
    if(ans < 0) ans = -1;
    if(ans > 0) ans = 1;
    return ans;
}
bool Inside(Triangle tr,Point p){
    long sign1 = Sign(tr.n1,tr.n2,p);
    long sign2 = Sign(tr.n2,tr.n3,p);
    long sign3 = Sign(tr.n3,tr.n1,p);

    if(sign1 != sign2 && sign1*sign2 != 0) return false;
    if(sign2 != sign3 && sign2*sign3 != 0) return false;
    if(sign1 != sign3 && sign1*sign3 != 0) return false;
    return true;
}

bool isAnswer(long s){
    for(long i=1;i<=n;i++){
        if(i==s) continue;
        if(!Inside(v[s],v[i].n1) || !Inside(v[s],v[i].n2) || !Inside(v[s],v[i].n3)) return false;
    }
    return true;
}

int main()
{
    freopen("triunghi2.in","r",stdin);
    freopen("triunghi2.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%ld %ld %ld %ld %ld %ld",&v[i].n1.x,&v[i].n1.y,&v[i].n2.x,&v[i].n2.y,&v[i].n3.x,&v[i].n3.y);
    scanf("%ld %ld",&f.x,&f.y);

    for(i=1;i<=n;i++) if(Inside(v[i],f)) ans.push_back(i);

    for(i=1;i<=n;i++){
        if(isAnswer(i)) {Answer = i;break;}
    }

    printf("%ld ",ans.size());
    for(i=0;i<ans.size();i++) printf("%ld ",ans[i]);
    printf("\n%ld\n",Answer);

    return 0;
}
