#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdio>
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

#define maxN 1024
#define act M[ln][i]

typedef pair<long,long> mPair;

long n,m,i,j;
long a[maxN],M[maxN][maxN];

long cnt,ans;
mPair st[maxN];

void cManacher(long ln){
    long i,C=0,fC=0;
    for(i=1;i<=m;i++){
        M[ln][i] = 0;
        if(i<=fC) M[ln][i] = min(fC-i,M[ln][2*C-i]);
        while(a[i-act-1]==a[i+act+1]) act++;

        if(i+act > fC){
            fC = i+act;
            C = i;
        }
    }
}

void Sky(long co){
    long i,j,tmp; cnt = 0;
    for(i=1;i<=n;i++){
        mPair curr = make_pair(M[i][co],i);
        while(cnt && st[cnt].first > curr.first){
            curr.second = st[cnt--].second;
        }
        if(!cnt || (cnt && st[cnt].first != curr.first)) st[++cnt] = curr;

        for(j=1;j<=cnt;j++){
            tmp = (st[j].first*2+1) * (i-st[j].second+1);
            if(tmp > ans) {
                ans = tmp;
            }
        }
    }
}

int main()
{
    Buffer cin("dreptpal.in",1048576);
    freopen("dreptpal.out","w",stdout);

    cin >> n >> m;
    a[0] = -7; a[m+1] = -6;
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++) cin >> a[j];
        cManacher(i);
    }

    for(i=1;i<=m;i++) Sky(i);

    printf("%ld",ans);

    return 0;
}
