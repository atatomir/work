#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define INF (1<<29)

class Buffer{
    private:
        long dim,pos;
        vector<char> Buff;

        bool isDigit(char c){
            return '0'<=c&&c<='9';
        }
        void reFill(){
            pos = 0; memset(&Buff[0],0,sizeof(Buff));
            memset(&Buff[0],0,sizeof(dim));
            fread(&Buff[0],1,dim,stdin);
        }

    public:
        Buffer(long _dim){
            dim = _dim; Buff.resize(dim);
            reFill();
        }
        Buffer& operator>>(long& ans){
            while(!isDigit(Buff[pos]))
                if(++pos == dim) reFill();
            ans = 0;
            while(isDigit(Buff[pos])){
                ans = ans*10 + Buff[pos]-'0';
                if(++pos == dim) reFill();
            }
            return *this;
        }
};

struct intrv{
    long l,r;
    intrv(){}
    intrv(long _l,long _r) {
        l = _l; r = _r;
    }
    void Reverse(long v){
        l = v-l; r = v-r;
        swap(l,r);
    }
    intrv& operator<<(intrv who){
        if(l>who.r || who.l>r) { l=1;r=0; }
        l = max(l,who.l);
        r = min(r,who.r);

        return *this;
    }
};

long n,i,a,b,c,A,B;
intrv act,tmp;

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("test.in","r",stdin);
    #endif // DEBUG
    Buffer fin(1<<20);

    fin >> n >> b >> c;
    act = intrv(0, c-b );
    for(i=3;i<=n;i++){
        a = b; b = c; fin >> c;
        A = b-a; B = c-b;

        tmp = intrv(-INF,+INF); act.Reverse(A);
        tmp << intrv(0,A) << intrv(0,B) << act;
        act = tmp;
    }

    if(act.r<act.l) printf("0");
    else            printf("%ld",act.r-act.l+1);

    return 0;
}
