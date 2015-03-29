#include <iostream>
#include <cstdio>
#include <set>
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
mPair pos[maxN*maxN];

set<long> V;
set<mPair> ans;
set<mPair>::iterator it;

mPair act,lUp,rDown;

void delVal(){
    long i,j;
    for(i=lUp.first;i<act.first;i++)
        for(j=act.second+1;j<=rDown.second;j++)
            V.erase(a[i][j]);

    for(i=act.first+1;i<=rDown.first;i++)
        for(j=lUp.second;j<act.second;j++)
            V.erase(a[i][j]);
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

    for(i=1;i<=n*m;i++) V.insert(i);
    V.erase(a[1][1]); V.erase(a[n][m]);
    ans.insert(mp(1,1)); ans.insert(mp(n,m));

    for(t=n+m-3;t;t--){
        val = *V.begin();
        act = pos[val];

        it = ans.lower_bound(act);
        it--;
        lUp = *it;
        it++;
        rDown = *it;

        delVal();

        V.erase(val);
        ans.insert(act);
    }

    for(it=ans.begin(),i=1;it!=ans.end();it++,i++){
        act = *it; printf("%ld ",a[act.first][act.second]);
    }

    return 0;
}
