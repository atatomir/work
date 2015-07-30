#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define maxN 100024
#define INF (1LL<<60)
#define mps StackElem

struct StackElem{
    long  long h,cnt;
    StackElem(){};
    StackElem(long long _h,long long _cnt){
        h = _h; cnt = _cnt;
    }
};

long t,n,i,qq;
long long act;
long long a[maxN];
pair<long long,long> Q[maxN];

long pos,wh,qPos;
StackElem S[maxN];

long long ansPos[maxN],ansA[maxN],ansB[maxN];
long long limR;

void getNew(){
    while(S[pos].h >= a[wh]){
        if(S[pos].h==a[wh]) {
            S[pos].cnt++;
            wh++;
        } else{
            S[++pos] = mps(a[wh++],1);
        }
    }

    limR = a[wh];
}

long long getNeed(){
    if(wh == n && pos==2) return INF;
    if(wh==n) return 1LL*S[pos].cnt*(S[pos-1].h-S[pos].h);
    return 1LL*S[pos].cnt*1LL*min(limR-S[pos].h,S[pos-1].h-S[pos].h);
}

void getNext(){
    if(limR-S[pos].h < S[pos-1].h-S[pos].h){
        S[pos].cnt++;
        S[pos].h = limR; limR = a[++wh];
    } else {
        S[pos].h = S[pos-1].h;
    }
    if(S[pos-1].h == S[pos].h) {
        S[pos-1].cnt += S[pos].cnt;
        pos--;
    }
}

void Simplifica(long long& _a,long long& _b){
    long long a=_a,b=_b;

    if(a<b) swap(a,b);
    while(b){
        a %= b;
        swap(a,b);
    }
    _a /= a;
    _b /= a;
}

int main()
{
    freopen("atlas.in","r",stdin);
    freopen("atlas.out","w",stdout);

    scanf("%ld",&t);
    for(;t--;){
        scanf("%ld",&n); n+=2; a[1]=a[n]=INF;
        for(i=2;i<n;i++) scanf("%lld",&a[i]);
        scanf("%ld",&qq);
        for(i=1;i<=qq;i++) {scanf("%lld",&Q[i].first); Q[i].second=i;}
        sort(Q+1,Q+qq+1);

        pos = 0; act = 0;
        S[++pos] = mps(a[1],1);
        S[++pos] = mps(a[2],1); wh=3; qPos = 1;
        limR = a[wh];

        while(qPos != qq+1){
            if(S[pos].h >= limR) getNew();

            long long need = getNeed();
            while(need >= Q[qPos].first-act){  //! rezolva query
                ansPos[Q[qPos].second] = wh-1;
                ansB  [Q[qPos].second] = S[pos].cnt;
                ansA  [Q[qPos].second] = Q[qPos].first-act + S[pos].h*S[pos].cnt;

                qPos++;
                if(qq+1==qPos) break;
            }

            act += need;
            getNext();
        }

        for(i=1;i<=qq;i++){
            Simplifica(ansA[i],ansB[i]);
            printf("%lld %lld/%lld\n",ansPos[i]-1,ansA[i],ansB[i]);
        }
    }


    return 0;
}
