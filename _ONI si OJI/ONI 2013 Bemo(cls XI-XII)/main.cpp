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


#define maxN 1511
#define cin fin
#define mPair pair<long,long>
#define mp make_pair

long n,m,i,j,t,val;
long a[maxN][maxN];
mPair pos[maxN*maxN],act;

bool deny[maxN][maxN];


void delValUp(long x,long y){
    if(deny[x][y]) return;
    deny[x][y] = true;
    delValUp(x-1,y);
    delValUp(x,y+1);
}
void delValDown(long x,long y){
    if(deny[x][y]) return;
    deny[x][y] = true;
    delValDown(x+1,y);
    delValDown(x,y-1);
}

int main()
{
    Buffer cin("bemo.in",1024*1024);
    freopen("bemo.out","w",stdout);

    cin >> n >> m;
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            cin >> a[i][j];
            pos[a[i][j]] = make_pair(i,j);
        }
    }

    for(i=0;i<=n+1;i++){deny[i][0] = deny[i][m+1]=true;}
    for(i=0;i<=m+1;i++){deny[0][i] = deny[n+1][i]=true;}

    for(val=1;val<=n*m;val++){
        act = pos[val];
        if(deny[act.first][act.second]) continue;
        delValUp(act.first-1,act.second+1);
        delValDown(act.first+1,act.second-1);
    }

    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            if(!deny[i][j]) printf("%ld ",a[i][j]);


    return 0;
}
