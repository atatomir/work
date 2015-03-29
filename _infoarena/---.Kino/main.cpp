#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
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

#define maxL 55
#define maxN 20011
#define cin fin

long n,l,i,j,x;
long lim[maxL];
vector<long> e[maxL];
vector<long> et;
long usd[maxN+11];

long long ans;


int main()
{
    Buffer cin("kino.in",1024*1024);
    freopen("kino.out","w",stdout);

    cin >> n >> l;
    for(i=1;i<=l;i++) cin >> lim[i];
    for(i=1;i<=n;i++){
        for(j=1;j<=l;j++){
            cin >> x;
            if(x) e[j].push_back(x);
        }
    }

    for(i=1;i<=l;i++){
        memset(usd,0,sizeof(usd));
        et.clear();

        for(j=0;j<e[i].size();j++){
            if(e[i][j]<=maxN) usd[e[i][j]]++;
            else et.push_back(e[i][j]);
        }
        sort(et.begin(),et.end());

        long need = n - e[i].size();
        long vLim=1; lim[i] = min(lim[i],(long)maxN);
        while(need){
            for(j=1;j<=lim[i];j++){
                if(usd[j]<vLim) {
                    usd[j]++;
                    if((--need) == 0) break;
                }
            }
            vLim++;
        }

        long long sum = 0;
        for(j=1;j<=lim[i];j++){
            ans += sum*(usd[j]);
            sum += usd[j];
        }

        for(j=0;j<et.size();j++){
            long def = et[j];
            long cnt = 1;

            if(j+1<et.size())
            while(et[j+1]==def){
                cnt++; j++;
                if(j+1==et.size()) break;
            }

            ans += sum*cnt;
            sum += cnt;
        }
    }

    printf("%lld",ans);

    return 0;
}
