#include <iostream>
#include <cstdio>
#include <vector>
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

#define maxN 200011
long n,i,k,cnt,x,y;
bool vis[maxN];
long l[maxN];
vector<long> list[maxN];

bool cmpB(long a,long b){
    return vis[a] < vis[b];
}
bool cmp(long a,long b){
    return l[a] < l[b];
}

void dfs(long node){
    vis[node] = true; cnt++; l[node] = 1;

    sort(list[node].begin(),list[node].end(),cmpB);

    bool leaf=true;
    long ind=0;
    for(long i=0;i<list[node].size();i++){
        long newNode = list[node][i];
        if(!vis[newNode]) dfs(newNode),leaf=false,ind++;
    }
    if(leaf) return;

    list[node].resize(ind);
    sort(list[node].begin(),list[node].end(),cmp);
    long i=0,j=list[node].size()-2,m;
    while(i<=j){
        m = (i+j)>>1;
        long newNode1 = list[node][m];
        long newNode2 = list[node][m+1];
        if(l[newNode1]+l[newNode2]<=k)
            i = m+1;
        else
            j = m-1;
    }
    if(j>=0){
        cnt -= j+2;
        l[node] = l[list[node][j+1]]+1;
    } else {
        if(l[list[node][0]]<=k){
            cnt--;
            l[node] = l[list[node][0]]+1;
        }
    }
}

int main()
{
    Buffer cin("kdtree.in",1024*1024);
    freopen("kdtree.out","w",stdout);

    cin >> n >> k;
    for(i=1;i<n;i++){
        cin >> x >> y;
        list[x].push_back(y);
        list[y].push_back(x);
    }

    dfs(1);
    printf("%ld",cnt-1);

    return 0;
}
