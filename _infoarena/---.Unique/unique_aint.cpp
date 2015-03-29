#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>
 
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
//////////////////////////////////////////////////////////////////
 
#define maxN 100011
 
struct Que{
    long l,r,need;
};
bool cmp(const Que& a,const Que& b){
    return a.r < b.r;
}
struct sElem{
    long pos,v;
};
sElem mp(long ppos,long vv){
    sElem tmp;
    tmp.pos = ppos; tmp.v = vv;
    return tmp;
}
 
////////////////////////////////////////////////////////////////////
 
long t,i,j,n,ans;
long v[maxN],aint[maxN<<2],prec[maxN];
Que Q[maxN];
stack<sElem> S;
long st[maxN],dr[maxN];
 
 
void add(long node,long l,long r,long pos,long val){
    if(l==r) {
        aint[node] += val;
        return;
    }
 
    long m = (l+r)>>1;
    if(pos<=m)
        add(node<<1,l,m,pos,val);
    else
        add((node<<1)|1,m+1,r,pos,val);
 
    aint[node] = aint[node<<1] + aint[(node<<1)|1];
}
long query(long node,long l,long r,long qL,long qR){
    if(l>=qL && r<=qR) return aint[node];
 
    long m=(l+r)>>1,ans=0;
    if(qL<=m) ans += query(node<<1,l,m,qL,qR);
    if(m+1<=qR) ans+= query((node<<1)|1,m+1,r,qL,qR);
    return ans;
}
 
void make_st(){
    while(!S.empty()) S.pop();
    S.push(mp(0,1000000000));
 
    for(long i=1;i<=n;i++){
        while(S.top().v <= v[i]) S.pop();
        st[i] = S.top().pos+1;
        S.push(mp(i,v[i]));
    }
}
 
void make_dr(){
    while(!S.empty()) S.pop();
    S.push(mp(n+1,1000000000));
 
    for(long i=n;i;i--){
        while(S.top().v <= v[i]) S.pop();
        dr[i] = S.top().pos-1;
        S.push(mp(i,v[i]));
    }
}
 
int main()
{
    Buffer cin("unique.in",1024*1024);
    freopen("unique.out","w",stdout);
 
    cin >> t;
    for(;t;t--){
        memset(aint,0,sizeof(aint));
        memset(prec,0,sizeof(prec));
        ans = 0;
 
        cin >> n;
        for(i=1;i<=n;i++) cin >> v[i];
        make_st(); make_dr();
 
        for(i=1;i<=n;i++){
            Q[i].l = st[i]; Q[i].r = dr[i];
            Q[i].need = v[i];
        }
        sort(Q+1,Q+n+1,cmp);
 
        j = 1;
        for(i=1;i<=n;i++){
            for(;j<=Q[i].r;j++){
                if(prec[v[j]]) add(1,1,n,prec[v[j]],-1);
                add(1,1,n,j,1);
                prec[v[j]] = j;
            }
 
            long val = query(1,1,n,Q[i].l,Q[i].r);
            if(val == Q[i].need)
                ans = max(ans,Q[i].r-Q[i].l+1);
        }
 
        printf("%ld\n",ans);
    }
 
    return 0;
}
