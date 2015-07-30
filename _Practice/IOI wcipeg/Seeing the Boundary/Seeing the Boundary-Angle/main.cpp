#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

#ifndef ONLINE_JUDGE
    #define DEBUG @atatomir
#endif // ONLINE_JUDGE


#define mp make_pair
#define eps 0.00000000001
#define rAng 0.000003

#ifdef DEBUG
    #define err(x) cerr<<"!"<<x<<"\n";
#else
    #define err(x) /* tractoreala */
#endif

long n,m,i,cnt,pos,Answer,activ;
vector< pair<double,double> > need;
vector< pair<double,bool> > upd;
vector< double > act;
double x,y,xx,yy,T;
double ang,maxAng,minAng;

double rcos,rsin;

bool equal(double x,double y){
    x -= y; if(x<0) x*=-1;
    return x <=eps;
}
bool cmp(const pair<double,bool>& a,const pair<double,bool>& b){
    if(equal(a.first,b.first)) return a.second > b.second;
    return a.first < b.first;
}

void rotate(double& _x,double& _y){
    double xx = _x;
    double yy = _y;

    _x = xx*rcos - yy*rsin;
    _y = xx*rsin + yy*rcos;
}

void reCalc(){  //! daca nu se incadreaza in cerc
    minAng = 5*T; maxAng = -3*T;
    cnt = need.size()-1;
    for(;cnt >= 0;cnt--){
        xx = need[cnt].first; yy = need[cnt].second;
        ang = atan2( yy-y,xx-x );
        minAng = min(minAng,ang);
        maxAng = max(maxAng,ang);
    }
    minAng += 2.00*T;
    maxAng += 2.00*T;
}

double getAng(double _x,double _y){
    rotate(_x,_y);

    _y -= y;
    _x -= x;

    double ans = atan2(_y,_x);
    if(ans<0) ans += 2.00*T;
    return ans;
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif

    T = acos(-1.00);
    rsin = sin(rAng);
    rcos = cos(rAng);

    scanf("%ld %ld",&n,&m);
    scanf("%lf %lf",&x,&y); rotate(x,y);

    for(;m--;){
        scanf("%ld",&cnt);

        minAng = 3*T; maxAng = -T;
        need.clear();
        for(;cnt--;){
            scanf("%lf %lf",&xx,&yy);   rotate(xx,yy);
            need.push_back(mp(xx,yy));

            ang = atan2( yy-y,xx-x ); if(ang < 0.00) ang += 2.00*T;
            minAng = min(minAng,ang);
            maxAng = max(maxAng,ang);
        }

        if(maxAng - minAng > T) { //! inversare
            reCalc();
            upd.push_back( mp(minAng-eps,true) );
            upd.push_back( mp(2.00*T-eps,false) );

            upd.push_back( mp(0.00-eps,true) );
            upd.push_back( mp(maxAng-2.00*T+eps,false) );
        } else {
            upd.push_back( mp(minAng-eps,true) );
            upd.push_back( mp(maxAng+eps,false) );
        }
    }

    sort(upd.begin(),upd.end(),cmp);
    act.clear();
    for(i=0;i<n;i++){
        act.push_back( getAng(0,i) );
        act.push_back( getAng(i,n) );
        act.push_back( getAng(n,n-i) );
        act.push_back( getAng(n-i,0) );
    }
    sort(act.begin(),act.end());

    for(i=0;i<upd.size();i++){
        err( setprecision(3) <<  upd[i].first*180.00/T << ' '<<(upd[i].second?1:0) );
    }

    pos = 0;
    for(i=0;i<act.size();i++){
        double now = act[i];

        if(pos<upd.size())
        while(now > upd[pos].first){
            if(upd[pos].second) activ++; else activ--;

            if(++pos>=upd.size()) break;
        }

        if(!activ) Answer++;
    }

    printf("%ld",Answer);

    return 0;
}



