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
#define iLeft first
#define iRight second

class myDeque{
    public:
        vector<long> a;

        void push_back(long x){
            a.push_back(x);
        }
        void push_front(long x){
            a.push_back(x);
        }
};

typedef deque<long>::iterator myIter;
typedef pair<myIter,myIter> mPair;

long n,i,bg,en,op,x,y,k;
long v[maxN<<1];
myDeque cnt[maxN];


long getNext(long v){
    return v^((v^(v-1)&v));
}

void addLeft(long pos,long v){
    cnt[v].push_front(pos); v = getNext(v);
    while(v){
        cnt[v].push_front(pos);
        v = getNext(v);
    }
}

void addRight(long pos,long v){
    cnt[v].push_back(pos); v = getNext(v);
    while(v){
        cnt[v].push_back(pos);
        v = getNext(v);
    }
}
/*
void removeLeft(long v){
    cnt[v].pop_front(); v = getNext(v);
    while(v){
        cnt[v].pop_front();
        v = getNext(v);
    }

}

void removeRight(long v){
    cnt[v].pop_back(); v = getNext(v);
    while(v){
        cnt[v].pop_back();
        v = getNext(v);
    }
}

long kth(long st,long dr,long k){
    long ans = 0,onIntr = dr-st+1;
    for(long i=1<<20;i;i>>=1){
        if((ans^i) > lim) continue;
        ans ^= i;
        mPair tmp;
        tmp.iLeft = lower_bound(cnt[ans].begin(),cnt[ans].end(),st);
        tmp.iRight = upper_bound(cnt[ans].begin(),cnt[ans].end(),dr);
        long withOne = tmp.iRight-tmp.iLeft;
        long withZero = onIntr - withOne;

        if(k <= withZero){
            ans ^= i;
            onIntr = withZero;
        } else {
            k -= withZero;
            onIntr = withOne;
        }
    }
    return ans;
}

*/

int main()
{
    Buffer cin("kthvalue.in",1024*1024);
    freopen("kthvalue.out","w",stdout);


    cin >> n;
    bg = lim+1; en = bg-1;
    for(;n;n--){
        cin >> op;
        switch(op){
            case 1:{
                        cin >> x; bg--; v[bg] = x;
                        addLeft(bg,x);
                        break;
                   }
            case 2:{
                        cin >> x; en++; v[en] = x;
                        addRight(en,x);
                        break;
                   }
            /*case 3:{
                        removeLeft(v[bg]); bg++;
                        break;
                   }
            case 4:{
                        removeRight(v[en]); en--;
                        break;
                   }
            case 5:{
                        cin >> x >> y >> k; x+=bg-1; y+=bg-1;
                        printf("%ld\n",kth(x,y,k));
                        break;
                   }*/
        }
    }

    return 0;
}
