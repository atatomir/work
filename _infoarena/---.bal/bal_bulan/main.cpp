//!bulaneala

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define mod 66013
class Hash{
    private :
        vector<long long> C[mod];

    public:
        Hash(){
            for(long i=0;i<mod;i++) C[i].clear();
        }
        bool alrdn(long long v){
            long id = v%mod;
            for(auto it = C[id].begin();it!=C[id].end();it++)
                if(*it == v) return true;
            return false;
        }
        void operator<<(long long v){
            long id = v%mod;
            C[id].push_back(v);
        }
};

#define maxN 100011

long n,m,i;
Hash H;
vector<long> list[maxN];
long l[maxN],r[maxN],rez[maxN];
long long x,y;
bool u[maxN];

void nope(){
    printf("NU");
    exit(0);
}
void dap(){
    printf("DA\n");
    for(long i=1;i<=n;i++) printf("%ld\n",l[i]);
    exit(0);
}

bool pairUp(long node){
    if(u[node]) return false;
    u[node]=true;

    for(auto it=list[node].begin();it!=list[node].end();it++){
        if(r[*it] == 0){
            l[node] = *it;
            r[*it] = node;
            return true;
        }
    }

    for(auto it=list[node].begin();it!=list[node].end();it++){
        if( pairUp( r[*it] ) ){
            l[node] = *it;
            r[*it] = node;
            return true;
        }
    }

    return false;
}

void cuplaj(){
    memset(l,0,sizeof(l));
    memset(r,0,sizeof(r));
    long i;

    bool ok = true;
    while(ok){
        ok = false;
        memset(u,0,sizeof(u));

        for(i=1;i<=n;i++)
            if(!l[i]) ok |= pairUp(i);
    }

    for(i=1;i<=n;i++)
        if(!l[i]) nope();
}

void swapEdges(long node){
    long i=0,j=list[node].size()-1;

    while(i<j){
        swap(list[node][i],list[node][j]);
        i++; j--;
    }
}

int main()
{
    freopen("bal.in","r",stdin);
    freopen("bal.out","w",stdout);

    H = Hash();

    scanf("%ld %ld",&n,&m);
    for(;m--;){
        scanf("%lld %lld",&x,&y);
        long long vv = x*(1LL<<30) + y;
        if(H.alrdn(vv)) continue;
        H << vv;

        list[x].push_back(y);
    }

    cuplaj();
    for(i=1;i<=n;i++) rez[i]=l[i];

    for(i=1;i<=n;i++) swapEdges(i);
    cuplaj();

    for(i=1;i<=n;i++)
        if(rez[i]!=l[i]) nope();

    dap();

    return 0;
}
