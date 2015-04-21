#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

long lim;
bool warn;

struct Bulk{
    long cnt,bestPos;
    long long sum,best;
    vector<long> v;

    void init(long val){
        cnt = 1; bestPos = 1;
        sum = val; best = val;
        v.clear(); v.push_back(val);
    }
    void update(){
        sum = v[0]; best = v[0]; bestPos = 0;
        for(long i=1;i<cnt;i++){
            sum += v[i];
            if(best > sum){
                best = sum;
                bestPos =i;
            }
        }
    }
    void getVals(long st,long _cnt,vector<long>& vals){
        cnt = _cnt; v.resize(cnt);
        for(long i=st;_cnt;_cnt--,i++) v[i-st]= vals[i];
        update();
    }
    void OverTurn(long st,vector<long>& vals){
        for(long i=0;i<v.size();i++) vals[st++] = v[i];
    }

    void addPos(long pos,long val){
        v.push_back(0); pos--; cnt++; if(cnt==lim) warn=true;
        for(long i=v.size()-1;i>pos;i--) v[i] = v[i-1];
        v[pos] = val;
        update();
    }
    void rmPos(long pos){
        pos--; cnt--; if(cnt==0) warn = true;
        for(long i=pos;i<(long)v.size()-2;i++) v[i] = v[i+1];
        v.pop_back();
        update();
    }
};

#define maxN 200011
#define maxBulks 505

long n,m,i,x,y,op,act;
vector<long> vals;
Bulk B[maxBulks];
long bDim,bCnt;

long long bestVal,bestPos;
long long sumNow,howNow;

void FillVals(){
    vals.resize(n+10);
    long rem = 1;
    for(long i=1;i<=bCnt;rem+=B[i].cnt,i++) B[i].OverTurn(rem,vals);
}

void makeBulks(){
    if(n==0){
        bCnt = 0; bDim = 0;
        B[1].update();
        return;
    }

    bDim = (long)sqrt(n); lim = bDim<<1;
    if(n%bDim==0) bCnt =  n/bDim;
    else          bCnt = (n/bDim)+1;

    long rem=1;
    for(long i=1;i<=bCnt;i++,rem+=bDim)
        B[i].getVals(rem,min(bDim,n-rem+1),vals);
}

void ReNew(){
    FillVals();
    makeBulks();
}

int main()
{
    freopen("rotatii.in","r",stdin);
    freopen("rotatii.out","w",stdout);

    scanf("%ld%ld",&n,&m);
    vals.resize(n+10);
    for(i=1;i<=n;i++) scanf("%ld",&vals[i]);

    makeBulks();
    for(;m--;){
        scanf("%ld",&op);
        if(op==0){
            scanf("%ld %ld",&x,&y); n++; x++;
            act = 1;
            while(x > B[act].cnt && act<bCnt) x-=B[act++].cnt;
            B[act].addPos(x,y);
        } else
        if(op==1){
            scanf("%ld",&x); n--;
            act = 1;
            while(x > B[act].cnt) x-=B[act++].cnt;
            B[act].rmPos(x);
        } else {
            long long sumAll =0;
            for(i=1;i<=bCnt;i++) sumAll += B[i].sum;
            if(sumAll<0){
                printf("-1\n");
            } else {
                bestVal = 1LL<<60; sumNow = 0; howNow = 0;
                for(i=1;i<=bCnt;i++){
                    long vv = sumNow + B[i].best;
                    if(vv < bestVal){
                        bestVal = vv;
                        bestPos = howNow + B[i].bestPos+1;
                    }
                    sumNow += B[i].sum;
                    howNow += B[i].cnt;
                }

                if(bestPos==n) bestPos=0;
                printf("%lld\n",bestPos);
            }

        }

        if(warn){
            warn = false;
            ReNew();
        }

    }

    return 0;
}
