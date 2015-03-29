#include <iostream>
#include <cstdio>
#include <vector>
#include <ctime>

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
#define maxN 100011
#define lSon (node<<1)
#define rSon ((node<<1)|1)

struct aNode{
    unsigned long long val,st,k;
};

long n,m,i,op,l,r,dif,qL,qR,kk;
aNode aint[maxN<<2];
unsigned long long k;

inline void UpdateNode(long node){
    aint[node].val = aint[lSon].val+aint[rSon].val;
}
inline unsigned long long sum(unsigned long long l,unsigned long long r){
    return ((r-l+1)*(r+l))>>1;
}
inline void Expand(long node,long l,long r){
    long m=(l+r)>>1;
    aint[lSon].val += aint[node].st*(m-l+1) + sum(1,m-l)*aint[node].k;
    aint[lSon].st += aint[node].st; aint[lSon].k += aint[node].k;

    aint[rSon].val += aint[node].st*(r-m) + sum(m-l+1,r-l)*aint[node].k;
    aint[rSon].st += aint[node].st+aint[node].k*(m-l+1); aint[rSon].k += aint[node].k;

    aint[node].st=aint[node].k=0;
}

void init(long node,long l,long r){
    aint[node].val = 0;
    aint[node].st=0; aint[node].k=0;
    if(l==r) return;
    long m=(l+r)>>1;
    init(lSon,l,m);
    init(rSon,m+1,r);
}

void Update(long node,long l,long r,unsigned long long remL,unsigned long long remR){
    if(qL<=l&&r<=qR){
        aint[node].val += sum(remL,remR)*k;
        aint[node].st += remL*k; aint[node].k += k;
        return;
    }

    if(aint[node].k) Expand(node,l,r);
    long m =(l+r)>>1;
    if(qL<=m) Update(lSon,l,m,remL,min((long)remR,(long)m-dif));
    if(qR>m)  Update(rSon,m+1,r,max((long)remL,(long)m+1-dif),remR);

    UpdateNode(node);
}

unsigned long long query(long node,long l,long r){
    if(qL<=l&&r<=qR) return aint[node].val;
    //!! Atentie ca iarna nu-i ca vara(qL<=l&&r<=qR nu e ca l==r)
    if(aint[node].k)Expand(node,l,r);
    long m=(l+r)>>1;
    unsigned long long ans=0;
    if(qL<=m) ans += query(lSon,l,m);
    if(qR>m)  ans += query(rSon,m+1,r);
    return ans;
}

int main()
{
    Buffer cin("numerex.in",1024*1024);
    freopen("numerex.out","w",stdout);

    cin >> n >> m;
    init(1,1,n);

    for(;m;m--){
        cin >> op;
        if(op==0){
            cin >> l >> r >> kk; r += l-1; k=kk;
            dif = l-1;
            qL = l; qR = r;
            Update(1,1,n,1,r-l+1);
        } else {
            cin >> l >> r;
            qL = l; qR = r;
            printf("%llu\n",query(1,1,n));
        }
    }

    return 0;
}
