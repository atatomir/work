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
#ifdef DEBUG
    #define err(x) cerr<<"!"<<x<<"\n";
#else
    #define err(x) /* tractoreala */
#endif

#define mp make_pair
#define fullAngle Angle(0,1,4)
#define zeroAngle Angle(0,1,1)
#define eps 0.0000000001
#define long long long


struct Angle{
    long up,down;
    short wh;

    Angle(){}
    Angle(long _up,long _down,short _wh){
        if(_up<0) _up *= -1;
        if(_down<0) _down *=-1;
        if(_wh==2||_wh==4) swap(_up,_down);
        up = _up; down = _down; wh = _wh;
    }
    Angle(long _up,long _down){
        if(_up >= 0 && _down >= 0) wh=1;
        if(_up >= 0 && _down <  0) wh=2;
        if(_up <  0 && _down <  0) wh=3;
        if(_up <  0 && _down >= 0) wh=4;

        if(wh==2||wh==4) swap(_up,_down);
        if(_up<0) _up *= -1;
        if(_down<0) _down *=-1;

        up = _up; down = _down;
    }
    bool operator<(const Angle& who)const{
        if(wh < who.wh) return true;
        if(wh > who.wh) return false;

        return (up*who.down)<(down*who.up);
    }
    bool operator<=(const Angle& who)const{
        if(wh < who.wh) return true;
        if(wh > who.wh) return false;

        return (up*who.down)<=(down*who.up);
    }
    bool operator==(const Angle& who)const{
        if(wh < who.wh) return false;
        if(wh > who.wh) return false;

        return (up*who.down)==(down*who.up);
    }
    pair<long,long> getPosition(){
        pair<long,long> ans;
        ans.first = down; ans.second = up;
        if(wh==2||wh==5) swap(ans.first,ans.second);
        if(wh==2)  ans.first *= -1;
        if(wh==3) {ans.first *= -1; ans.second *= -1;}
        if(wh==4)  ans.second *= -1;
        return ans;
    }
};

long n,m,i,cnt,pos,Answer,activ;
vector< pair<long,long> > need;
vector< pair<Angle,bool> > upd;
vector< Angle > act;
long x,y,xx,yy;
Angle ang,minAng,maxAng;

bool cmp(const pair<Angle,bool>& a,const pair<Angle,bool>& b){
    if(a.first == b.first) return a.second > b.second;
    return a.first < b.first;
}

bool needInvert(Angle aa,Angle bb){
    if(aa.wh==1) aa.wh=3; else
    if(aa.wh==2) aa.wh=4; else
    if(aa.wh==3) return false; else
    if(aa.wh==4) return false;


    return aa<bb;
}

void reCalc(){  //! daca nu se incadreaza in cerc
    //! max ang apartine cadranelor 1,2
    //! min ang apartine cadreanelor 3,4
    minAng = fullAngle; maxAng = zeroAngle;
    cnt = need.size()-1;
    for(;cnt >= 0;cnt--){
        xx = need[cnt].first; yy = need[cnt].second;
        ang = Angle(yy-y,xx-x);

        if(ang.wh<=2) maxAng = max(maxAng,ang);
        else          minAng = min(minAng,ang);
    }

}

Angle getAng(double _x,double _y){
    Angle ang;

    _y -= y;
    _x -= x;

    ang = Angle(_y,_x);
    return ang;
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif

    scanf("%lld %lld",&n,&m);
    scanf("%lld %lld",&x,&y);

    for(;m--;){
        scanf("%lld",&cnt);

        minAng = fullAngle; maxAng = zeroAngle;
        need.clear();
        for(;cnt--;){
            scanf("%lld %lld",&xx,&yy);
            need.push_back(mp(xx,yy));

            ang = Angle(yy-y,xx-x);
            if( ang < minAng ) minAng = ang;
            if( maxAng < ang ) maxAng = ang;
        }

        if( needInvert(minAng,maxAng) ) { //! inversare
            reCalc();
            upd.push_back( mp(minAng,true) );
            upd.push_back( mp(fullAngle,false) );

            upd.push_back( mp(zeroAngle,true) );
            upd.push_back( mp(maxAng,false) );
        } else {
            upd.push_back( mp(minAng,true) );
            upd.push_back( mp(maxAng,false) );
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

    pos = 0;
    for(i=0;i<act.size();i++){
        Angle now = act[i];

        if(pos<upd.size())
        while(upd[pos].first <= now ){
            if(upd[pos].first == now && upd[pos].second==false) break;
            if(upd[pos].second) activ++; else activ--;

            if(++pos>=upd.size()) break;
        }

        if(!activ) Answer++;
        if(now.wh == 4){
            i++;i--;
        }
    }

    printf("%lld",Answer);

    return 0;
}

