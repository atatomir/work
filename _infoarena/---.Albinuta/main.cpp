#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define maxN 55

long n,i,j,k,q,mod;
vector<long> list[maxN];
long cmmdc=1,prod=1;

struct State{
    long node,time;

    State getNext(){
        State Ans;
        Ans.time = time+1;
        if(Ans.time == mod) Ans.time = 0;
        Ans.node = list[node][time%list[node].size()];
        return Ans;
    }
    State getNextNext(){
        State Ans = getNext();
        return Ans.getNext();
    }
    bool operator!=(State tmp){
        return (node != tmp.node)||(time != tmp.time);
    }
};

long gcd(long a,long b){
    long t;
    if(a <= b) {t=a;a=b;b=t;}
    while(b){
        a %= b;
        t=a;a=b;b=t;
    }
    return a;
}

State beg,p1,p2;
long lC,lCic,act;
vector<pair<long,long> > Quee;
vector<pair<long,long> > Que;
long ans[55];

int main()
{
    freopen("albinuta.in","r",stdin);
    freopen("albinuta.out","w",stdout);

    scanf("%ld %ld",&n,&q);
    for(i=1;i<=n;i++){
        scanf("%ld",&k); list[i].resize(k);
        cmmdc = (cmmdc*k)/gcd(cmmdc,k);
        for(j=1;j<k;j++) scanf("%ld",&list[i][j]);
        scanf("%ld",&list[i][0]);
    }

    Que.resize(q);
    for(i=0;i<q;i++) {
        scanf("%ld",&Que[i].first);
        Que[i].second = i;
    }
    mod = cmmdc;

    beg.node = 1; beg.time = 1;
    p1 = beg; p2 = p1.getNext();

    lCic = 1;
    while(p1 != p2){
        p1 = p1.getNext();
        p2 = p2.getNextNext();
        lCic++;
    }

    lC = 0; p2 = beg; p1 = p1.getNext();
    while(p1 != p2){
        p1 = p1.getNext();
        p2 = p2.getNext();
        lC++;
    }

    act = 1; sort(Que.begin(),Que.end());
    for(i=0;Que[i].first<=lC&&i<Que.size();i++){
        while(act != Que[i].first){
            beg = beg.getNext();
            act++;
        }
        ans[Que[i].second] = beg.node;
    }

    for(;i<Que.size();i++){
        long temp = (Que[i].first-lC)%lCic;
        if(!temp) temp = lCic;
        Quee.push_back(make_pair(temp,Que[i].second));
    }
    sort(Quee.begin(),Quee.end());

    beg = p1; act = 1;
    for(i=0;i<Quee.size();i++){
        while(act != Quee[i].first) {
            beg = beg.getNext();
            act++;
        }
        ans[Quee[i].second] = beg.node;
    }

    for(i=0;i<q;i++) printf("%ld\n",ans[i]);

    return 0;
}
