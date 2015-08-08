#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

class Buffer{
    private:
        int dim,pos;
        vector<char> Buff;

        void reFill(){
            pos = 0;
            memset(&Buff[0],0,sizeof(Buff));
            fread(&Buff[0],1,dim,stdin);
        }
        bool isDigit(char c){
            return (c>='0')&&(c<='9');
        }

    public:
        Buffer(string name,int _dim){
            freopen(name.c_str(),"r",stdin);
            Buff.resize(_dim);
            dim = _dim; reFill();
        }
        Buffer& operator>>(int &dest){
            while( !isDigit(Buff[pos]) )
                if(++pos==dim) reFill();

            dest=0;
            while( isDigit(Buff[pos]) ){
                dest = dest*10 + Buff[pos]-'0';
                if(++pos==dim) reFill();
            }
            return *this;
        }
};

#define maxN 4015

int n,t,i,j,x,y,l,r,mid,defT;
vector<int> list[maxN];
int nxt[maxN][maxN],T[maxN];
bool us[maxN];
bool allGood;

void dfsIni(int node){
    int i;
    us[node]=true;

    for(i=0;i<list[node].size();i++){
        if(us[ list[node][i] ]){
            list[node][i] = list[node][ list[node].size()-1 ];
            list[node].pop_back(); i--;
            continue;
        }
        dfsIni(list[node][i]);
    }
}

bool cmp(int a,int b){
    return T[a] > T[b];
}

void dfs(int node){
    if(!allGood) return;
    if(list[node].empty()){
        T[node] = defT;
        return ;
    }

    foreach(list[node]) dfs(*it);
    T[node] = defT;

    sort(list[node].begin(),list[node].end(),cmp);
    foreach(list[node]){
        int Time = T[*it]-1; Time = min(Time,T[node]-1);
        Time = nxt[node][Time];

        if(Time<=0){
            allGood=false;
            return;
        }
        T[node] = Time;
    }
}

bool check(int lim){
    defT = lim; allGood=true;
    dfs(1);

    return allGood;
}

int main()
{
    Buffer fin("tcast.in",1<<20);
    freopen("tcast.out","w",stdout);

    fin >> n >> t;
    fordef(i,1,n-1){
        fin >> x>> y;
        list[x].pb(y);
        list[y].pb(x);
    }

    fordef(i,1,n)
        fordef(j,1,t) fin >> nxt[i][j];

    fordef(i,1,n){
        fordef(j,1,n+t){
            if(nxt[i][j]) nxt[i][j] = nxt[i][j-1];
            else          nxt[i][j] = j;
        }
    }

    dfsIni(1);
    l=1;r=n+t+3;
    while(l<=r){
        mid = (l+r)>>1;
        if( check(mid) )
            r = mid-1;
        else
            l = mid+1;
    }
    printf("%d",l-1);

    return 0;
}
