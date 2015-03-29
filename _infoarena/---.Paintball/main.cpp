#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

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

#define maxN 1000011

long n,i,minDead,maxDead,act,j,cnt;
long dir[maxN],in[maxN];
bool dead[maxN];

queue<long> Q,rQ;

void DFS(long act){
    dead[act]=1; maxDead++;
    if(!dead[dir[act]]) DFS(dir[act]);
}

int main()
{
    Buffer cin("paintball.in",1024*1024);
    freopen("paintball.out","w",stdout);

    cin >> n;
    for(i=1;i<=n;i++){
        cin >> dir[i];
        in[dir[i]]++;
    }

    for(i=1;i<=n;i++){
        if(!in[i]) Q.push(i);
    }

    rQ = Q;
    while(!Q.empty()){
        act = Q.front(); Q.pop();
        if(!dead[dir[act]]){
            long nDir = dir[act];
            dead[nDir] = 1; minDead++;
            if(--in[dir[nDir]] == 0) Q.push(dir[nDir]);
        }
        dead[act] = 1;
    }

    for(i=1;i<=n;i++){
        if(dead[i]) continue;
        j = i; cnt = 1;
        while(dir[j] != i) {
            dead[j] = true;
            j = dir[j];
            cnt++;
        } dead[j] = true;
        minDead += (cnt+1)/2;
    }

    printf("%ld ",minDead);

    ////////////////////////////////////////////////maxDead

    memset(dead,0,sizeof(dead));
    Q = rQ;
    while(!Q.empty()){
        act = Q.front(); Q.pop();
        if(!dead[dir[act]])DFS(dir[act]);
        dead[act] = true;
    }

    for(i=1;i<=n;i++){
        if(dead[i]) continue;
        j = i; cnt = 1;
        while(dir[j] != i) {
            dead[j] = true;
            j = dir[j];
            cnt++;
        } dead[j] = true;
        if(cnt > 1)
            maxDead += cnt-1;
        else
            maxDead++;
    }

    printf("%ld",maxDead);

    return 0;
}
