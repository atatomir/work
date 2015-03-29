#include <iostream>
#include <cstdio>
#include <vector>

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

#define cin fin
#define maxN 1000111
#define lSon (node<<1)
#define rSon ((node<<1)|1)

long n,m,i,l,r;
long aMax[maxN<<2],aPos[maxN<<2],aRem[maxN<<2];
long a[maxN];

long ansMax,ansPos;

inline void updNode(long node){
    aRem[node] = aRem[lSon]+aRem[rSon];
    if(aMax[lSon]>aMax[rSon]||(aMax[lSon]==aMax[rSon] && aPos[lSon]<aPos[rSon])){
        aMax[node] = aMax[lSon];
        aPos[node] = aPos[lSon];
    }else{
        aMax[node] = aMax[rSon];
        aPos[node] = aPos[rSon];
    }
}

void check(long val,long pos){
    if((val == ansMax&&pos<ansPos)||val>ansMax){
        ansMax = val;
        ansPos = pos;
    }
}

void init(long node,long l,long r){
    if(l==r){
        aMax[node] = a[l];
        aPos[node] = l;
        aRem[node] = 1;
        return;
    }

    long m=(l+r)>>1;
    init(lSon,l,m);
    init(rSon,m+1,r);

    updNode(node);
}

long getPos(long node,long l,long r,long x){
    if(l==r) return aPos[node];

    long m = (l+r)>>1;
    if(x<=aRem[lSon]){
        return getPos(lSon,l,m,x);
    } else {
        return getPos(rSon,m+1,r,x-aRem[lSon]);
    }
}

void query(long node,long l,long r,long qL,long qR){
    if(qL<=l&&r<=qR) {check(aMax[node],aPos[node]);return;}

    long m=(l+r)>>1;
    if(qL<=m) query(lSon,l,m,qL,qR);
    if(qR>m)  query(rSon,m+1,r,qL,qR);
}

void update(long node,long l,long r,long x){
    if(l==r){
        aMax[node] = -1;
        aRem[node] = 0;
        return;
    }

    long m = (l+r)>>1;
    if(x<=m) update(lSon,l,m,x);
    else     update(rSon,m+1,r,x);

    updNode(node);
}

void Answer(long node,long l,long r){
    if(l==r){
        if(aMax[node] != -1) printf("%ld\n",aMax[node]);
        return;
    }

    long m=(l+r)>>1;
    Answer(lSon,l,m);
    Answer(rSon,m+1,r);
}

int main()
{
    Buffer cin("eliminare.in",1024*1024);
    freopen("eliminare.out","w",stdout);

    cin >> n >> m;
    for(i=1;i<=n;i++) cin >> a[i];

    init(1,1,n);

    for(;m;m--){
        cin >> l >> r;
        l = getPos(1,1,n,l); r = getPos(1,1,n,r);

        ansMax = -1;
        query(1,1,n,l,r);

        update(1,1,n,ansPos);
    }

    Answer(1,1,n);

    return 0;
}
