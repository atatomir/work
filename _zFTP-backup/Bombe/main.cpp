#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
 
using namespace std;
 
#define a first
#define b second
#define maxN 311
#define ec e
#define time ttime
#define eps 0.001
#define mp make_pair
 
typedef pair<double,double> EcLine;
 
long n,i,j;
double R;
EcLine e[maxN];
vector<double> pos;
vector<double> vf;
vector<pair<double,pair<long,long> > > ch;
long where[maxN];
vector<pair<long,long> > intr;
 
long ans;
double time=0;
 
void check(double t){
    long i;
    for(i=0;i<n;i++) pos[i] = t*e[i+1].a + e[i+1].b;
    //sort(pos.begin(),pos.end());
 
 
    long cnt = 0; i = 0;
    double maxR = -10000000000000.00;
    for(i=0;i<n;i++){
        if(pos[i]>maxR+eps){
            cnt++;
            maxR = pos[i]+R;
        }
    }
    if(cnt < ans || (cnt==ans && time > t)){
        ans = cnt;
        time = t;
    }
}
 
bool eq(double x){
    return x >= -eps && x<=eps;
}
long abss(long x){
    if(x < 0) return -x;
    return x;
}
 
bool swapV(pair<long,long> p){
    long d1=where[p.first],d2=where[p.second];
    if(abss(d1-d2) > 1) return false;
    EcLine tmp; long ttmp;
    ttmp = where[p.first]; where[p.first] = where[p.second]; where[p.second] = ttmp;
    tmp = ec[d1]; ec[d1] = ec[d2] ; ec[d2] = tmp;
    return true;
}
 
bool mCMP(const EcLine& a,const EcLine& b){
    if(a.b==b.b){
        return a.a < b.a;
    }
    return a.b < b.b;
}
 
void doIntr(){
    while(intr.size()){
        for(long i=0;i<intr.size();i++){
            if(swapV(intr[i])){
                intr[i] = intr[intr.size()-1];
                intr.pop_back();
                i--;
            }
        }
    }
}
 
int main()
{
    freopen("bombe.in","r",stdin);
    freopen("bombe.out","w",stdout);
 
    scanf("%ld %lf",&n,&R); R*=2; pos.resize(n); ans = n;
    for(i=1;i<=n;i++) scanf("%lf %lf",&e[i].b,&e[i].a);
 
    sort(ec+1,ec+n+1,mCMP);
 
    check(0);
    for(i=1;i<n;i++){
        for(j=i+1;j<=n;j++){
            if(eq(ec[i].a - ec[j].a)) continue;
            if(eq(ec[i].b - ec[j].b)) continue;
            double tt = (ec[j].b+R-ec[i].b)/(ec[i].a-ec[j].a);
            if(tt >= eps) vf.push_back(tt);
            tt = (ec[j].b-R-ec[i].b)/(ec[i].a-ec[j].a);
            if(tt >= eps) vf.push_back(tt);
 
            tt = (ec[j].b-ec[i].b)/(ec[i].a-ec[j].a);
            if(tt >= eps) ch.push_back(mp(tt,mp(i,j)));
        }
    }
 
    sort(vf.begin(),vf.end());
    sort(ch.begin(),ch.end());
    for(i=1;i<=n;i++) where[i] = i;
 
    long pWhere = 0;
    for(i=0;i<vf.size();i++){
        double tt = vf[i];
        intr.clear();
        while(pWhere<ch.size() && ch[pWhere].first<=tt+eps) intr.push_back(ch[pWhere].second),pWhere++;
        doIntr();
        check(tt);
    }
 
    printf("%ld %.3f",ans,time);
 
    return 0;
}