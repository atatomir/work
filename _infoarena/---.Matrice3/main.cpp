#include <iostream>
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

        Buffer& getBit(char &c){
            while(Buff[pos]!='0' && Buff[pos]!='1'){
                pos++;
                if(pos == maxBuf) reFill();
            }

            c = Buff[pos++];
            if(pos==maxBuf) reFill();
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
#define maxN 256
#define maxLog 8
#define x1 xx1
#define x2 xx2
#define y2 yy2
#define y1 yy1

long n,m,q,i,j,k,p,x1,x2,y1,y2;
char a[maxN][maxN],c;
char rmq[maxLog][maxLog][maxN][maxN]; // k-down p-right

inline long getMax(char v1,char v2,char v3,char v4){
    return max(max(v1,v2),max(v3,v4));
}

inline bool check(long x1,long y1,long x2 ,long y2,long L){
    long H = x2-x1+1;
    long W = y2-y1+1;

    long kk = 0;
    while((1<<(kk+1)) <= H) kk++;
    long pp = 0;
    while((1<<(pp+1)) <= W) pp++;

    long vK=1<<kk,vP=1<<pp;

    long val = getMax(rmq[kk][pp][x1][y1],
                      rmq[kk][pp][x2-vK+1][y1],
                      rmq[kk][pp][x1][y2-vP+1],
                      rmq[kk][pp][x2-vK+1][y2-vP+1]);

    if(val>=L) return true;
    return false;
}

long getAns(long x1,long y1,long x2,long y2){
    long i=0,j=min(x2-x1+1,y2-y1+1),m;
    while(i<=j){
        m = (i+j)>>1;
        if(check(x1+m-1,y1+m-1,x2,y2,m))
            i = m+1;
        else
            j = m-1;
    }
    return j;
}

int main()
{
    Buffer cin("matrice3.in",1024*1024);
    freopen("matrice3.out","w",stdout);

    cin >> n >> m >> q;

    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            cin.getBit(c);
            if(c=='1') continue;
            rmq[0][0][i][j] = min(rmq[0][0][i-1][j-1],min(rmq[0][0][i-1][j],rmq[0][0][i][j-1]))+1;
        }
    }

    for(k=1;k<maxLog;k++){  //!pt p==0
        long lK = 1<<k;
        long llK = lK>>1;

        for(i=1;i<=n-lK+1;i++){
            for(j=1;j<=m;j++){
                rmq[k][0][i][j] = max(rmq[k-1][0][i][j],rmq[k-1][0][i+llK][j]);
            }
        }
    }

    for(p=1;p<maxLog;p++){ //!pt k==0
        long lP = 1<<p;
        long llP = lP>>1;

        for(i=1;i<=n;i++){
            for(j=1;j<=m-lP+1;j++){
                rmq[0][p][i][j] = max(rmq[0][p-1][i][j],rmq[0][p-1][i][j+llP]);
            }
        }
    }

    for(k=1;k<maxLog;k++){  //! pt k!=0 si p!=0
        long lK = 1<<k;
        long llK = lK>>1;

        for(p=1;p<maxLog;p++){
            long lP = 1<<p;
            long llP = lP>>1;

            for(i=1;i<=n-lK+1;i++){
                for(j=1;j<=m-lP+1;j++){
                    rmq[k][p][i][j] = getMax(rmq[k-1][p-1][i][j],
                                             rmq[k-1][p-1][i+llK][j],
                                             rmq[k-1][p-1][i][j+llP],
                                             rmq[k-1][p-1][i+llK][j+llP]);
                }
            }
        }
    }

    for(;q;q--){
        cin >> x1 >> y1 >> x2 >> y2;
        printf("%ld\n",getAns(x1,y1,x2,y2));
    }


    return 0;
}
