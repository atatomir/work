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

#define maxN 100011
#define lSon (node<<1)
#define rSon (lSon|1)
#define def Events[pos].second

class Aint{
    private:
        int n,i;
        int *dp; //! cnt on
        int *burn; //! cnt burn

        void review(int node){
            if(burn[node]){
                dp[node] = 0;
                return;
            }
            dp[node] = dp[lSon]+dp[rSon];
        }
        void sreview(int node){
            if(burn[node])
                dp[node] = 0;
            else
                dp[node] = 1;
        }
        void makeTree(int node,int l,int r){
            if(l==r){
                dp[node]=1;
                burn[node]=0;
                return;
            }

            int mid = (l+r)>>1;
            makeTree(lSon,l,mid);
            makeTree(rSon,mid+1,r);

            review(node);
        }

    public:
        void init(int _n,int *_dp,int *_burn){
            n = _n; dp = _dp; burn = _burn;
            makeTree(1,1,n);
        }
        void update(int node,int l,int r,int qL,int qR,int vv){
            if(qL<=l&&r<=qR){
                burn[node] += (vv?-1:+1);
                if(l!=r) review(node);
                else sreview(node);
                return;
            }

            int mid = (l+r)>>1;
            if(qL<=mid) update(lSon,l,mid,qL,qR,vv);
            if(qR> mid) update(rSon,mid+1,r,qL,qR,vv);
            review(node);
        }
};

int n,i,m,x,y,z,k,pos;
vector<pa(int, pa(int,int) )> Events;
int T[maxN];
vector<int> list[maxN];

int l[maxN],r[maxN],cnt;
bool us[maxN];

int dp[maxN<<2];
int burn[maxN<<2];
Aint boss;

void dfs(int node){
    us[node] = true;
    l[node] = ++cnt;
    foreach(list[node]) dfs(*it);
    r[node] = cnt;
}

int main()
{
    freopen("curent.in","r",stdin);
    freopen("curent.out","w",stdout);

    scanf("%d",&n);
    fordef(i,2,n){
        scanf("%d",&x);
        list[x].pb(i);
    }
    scanf("%d",&m);
    fordef(i,1,m){
        scanf("%d%d%d",&x,&y,&z);
        Events.pb(mp(x,mp(y,z)));
    }
    scanf("%d",&k);
    fordef(i,1,k) scanf("%d",&T[i]);

    sort(Events.begin(),Events.end());
    dfs(1);

    boss.init(n,dp,burn); pos=0;
    fordef(i,1,k){
        while(pos<Events.size()){
            if(Events[pos].first > T[i]) break;
            boss.update(1,1,n,l[def.first],r[def.first],def.second);
            pos++;
        }

        printf("%d\n",dp[1]);
    }


    return 0;
}
