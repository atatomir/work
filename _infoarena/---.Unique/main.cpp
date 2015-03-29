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
long v[maxN],aib[maxN],prec[maxN];
Que Q[maxN];
stack<sElem> S;
long st[maxN],dr[maxN];

inline long zeros(long x){
    return (x^(x-1))&x;
}
void add(long pos,long val){
    while(pos<=n){
        aib[pos]+=val;
        pos += zeros(pos);
    }
}
long sum(long pos){
    long ans=0;
    while(pos){
        ans += aib[pos];
        pos -= zeros(pos);
    }
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
        memset(aib,0,sizeof(aib));
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
                if(prec[v[j]]) add(prec[v[j]],-1);
                add(j,1);
                prec[v[j]] = j;
            }

            if(Q[i].need > Q[i].r-Q[i].l+1) continue;
            long val = sum(Q[i].r) - sum(Q[i].l-1);
            if(val == Q[i].need)
                ans = max(ans,Q[i].r-Q[i].l+1);
        }

        printf("%ld\n",ans);
    }

    return 0;
}
