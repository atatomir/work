#include <iostream>
#include <cstdio>
#include <queue>

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
        Buffer& operator>>(long long &dest){
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

#define maxN 1000024
#define cin fin

struct State{
    long long h,cnt;
};
inline State mp(long long _h,long long _cnt){
    State ans;
    ans.h = _h; ans.cnt = _cnt;
    return ans;
}

long n,i;
long long B,a[maxN],ans,how;
deque<State> DQ;

inline void addValue(long _h){
    State act = mp(_h,1);

    if(!DQ.empty())
    while(act.h >= DQ.front().h){
        B = B - (act.h-DQ.front().h)*DQ.front().cnt;
        act.cnt += DQ.front().cnt;
        DQ.pop_front();

        if(DQ.empty()) break;
    }

    DQ.push_front(act); how++;
}

inline void rmValue(){
    long pos = i+how-1;

    B += DQ.back().h - a[pos];
    if(--DQ.back().cnt == 0 ) DQ.pop_back();
    how--;
}

int main()
{
    Buffer cin("calancea.in",1024*1024);
    freopen("calancea.out","w",stdout);

    cin >> n >> B;
    for(i=1;i<=n;i++) cin >> a[i];

    for(i=n;i;i--){
        addValue(a[i]);
        while(B<0) rmValue();

        ans += how;
    }

    printf("%lld",ans);

    return 0;
}
