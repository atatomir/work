#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

class Buffer{
    public:
        long maxBuf,pos;
        vector<char> Buff;

        Buffer(char fileName[],long buffSize){
            freopen(fileName,"r",stdin);
            maxBuf = buffSize; Buff.resize(maxBuf);
            reFill();
        }

        Buffer& operator>>(long &dest){
            while(!isDigit(Buff[pos])){
                pos++;
                if(pos == maxBuf) reFill();
            }
            dest = 0;
            while(isDigit(Buff[pos])){
                dest = dest*10 + Buff[pos++] - '0';
                if(pos == maxBuf) reFill();
            }
            return *this;
        }

    private:
        bool isDigit(char c){
            return c >= '0' & c <= '9';
        }
        void reFill(){
            fread(&Buff[0],1,maxBuf,stdin); pos = 0;
        }
};

#define maxN 1000011
#define lim 1000000

struct myTrie{
    public :
        myTrie *lSon,*rSon;
        long cnt;

        myTrie(long ccnt,myTrie* llSon,myTrie* rrSon){
            lSon = llSon; rSon = rrSon;
            cnt = ccnt;
        }
        myTrie(long l,long r){
            cnt = 0; lSon = NULL; rSon = NULL;
            if(l==r) return;
            long m=(l+r)>>1;
            lSon = new myTrie(l,m);
            rSon = new myTrie(m+1,r);
        }

        myTrie* Clone(long val,long l,long r){
            if(l==r) return new myTrie(cnt+1,NULL,NULL);

            myTrie* tmp;
            long m = (l+r)>>1;
            if(val<=m){
                tmp = new myTrie(cnt+1,lSon->Clone(val,l,m),rSon);
            } else {
                tmp = new myTrie(cnt+1,lSon,rSon->Clone(val,m+1,r));
            }
            return tmp;
        }
};


long n,i,bg,en,op,x,y,v,cnt;
myTrie *rTrie[maxN],*lTrie[maxN];
long lBG,lEN,rBG,rEN;


long kth(long st,long dr,long k){
    myTrie *lPlus,*lMinus,*rPlus,*rMinus;
    if(st>lEN-lBG+1){
        lPlus = lMinus = lTrie[0];
        st -= lEN-lBG+1; dr -= lEN-lBG+1;
        rMinus = rTrie[rBG+st-2];
        rPlus = rTrie[rBG+dr-1];
    } else
    if(dr<=lEN-lBG+1){
        long lung = lEN-lBG+1;
        st = lung-st+1; dr = lung-dr+1;

        rPlus = rMinus = lTrie[0];
        lMinus = lTrie[lBG+dr-2];
        lPlus = lTrie[lBG+st-1];
    }else {
        lMinus = lTrie[lBG-1];
        rMinus = rTrie[rBG-1];

        long lung = lEN-lBG+1;
        st = lung-st+1;
        lPlus = lTrie[lBG+st-1];

        dr -= lEN-lBG+1;
        rPlus = rTrie[rBG+dr-1];
    }


    st = 1; dr = lim;
    while(st!=dr){
        long m= (st+dr)>>1;
        long Smaller = lPlus->lSon->cnt + rPlus->lSon->cnt
                       -lMinus->lSon->cnt - rMinus->lSon->cnt;
        if(Smaller >= k){
            dr = m;
            lPlus = lPlus->lSon;
            lMinus = lMinus->lSon;
            rPlus = rPlus->lSon;
            rMinus = rMinus->lSon;
        } else {
            st = m+1; k-= Smaller;
            lPlus = lPlus->rSon;
            lMinus = lMinus->rSon;
            rPlus = rPlus->rSon;
            rMinus = rMinus->rSon;
        }
    }
    return st;
}


int main()
{
    Buffer cin("kthvalue.in",1024*1024);
    freopen("kthvalue.out","w",stdout);

    rTrie[0] = new myTrie(1,lim);
    lTrie[0] = new myTrie(1,lim);
    lBG = rBG = 1;
    lEN = rEN = 0;

    cin >> n;

    for(;n;n--){
        cin >> op;
        switch(op){
            case 1:{
                        cin >> v; cnt++;
                        lTrie[++lEN] = lTrie[lEN-1]->Clone(v,1,lim);
                        break;
                   }
            case 2:{
                        cin >> v; cnt++;
                        rTrie[++rEN] = rTrie[rEN-1]->Clone(v,1,lim);
                        break;
                   }
            case 3:{
                        cnt--;
                        if(lBG>lEN) rBG++; else lEN--;
                        break;
                   }
            case 4:{
                        cnt--;
                        if(rBG>rEN) lBG++; else rEN--;
                        break;
                   }
            case 5:{
                        cin >> x >> y >> v;
                        printf("%ld\n",kth(x,y,v));
                        break;
                   }
        }
    }

    return 0;
}
