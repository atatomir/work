#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>

using namespace std;

#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 16011

class SlidingWindow{
    public:
        void init(int _lim,long long val){
            data.clear(); lim = _lim;
            data.push_back( mp(0,val) );
        }
        void addValue(int pos,long long val){
            while(!data.empty()){
                auto last = data.back();
                if(last.second < val) break;
                data.pop_back();
            }
            data.push_back( mp(pos,val) );
            if(data.front().first<=pos-lim) data.pop_front();
        }
        long long getBest(){
            return data.front().second;
        }

    private:
        int lim;
        deque< pair<int, long long > > data;
        //! position , value
};

int n,i,color,s,q;
int Type[maxN];
long long Cost[2][maxN];
int dim;
long long pay,act;
SlidingWindow White,Black;
long long dp[maxN];

int main()
{
    freopen("trans.in","r",stdin);
    freopen("trans.out","w",stdout);

    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("%d%d",&color,&s);
        Type[i] = color;

        Cost[color][i] = s;
    }
    for(i=n-1;i>0;i--) {
        Cost[0][i] += Cost[0][i+1];
        Cost[1][i] += Cost[1][i+1];
    }

    scanf("%d",&q);
    for(;q--;){
        scanf("%d%lld",&dim,&pay);
        White.init(dim, Cost[0][1] );
        Black.init(dim, Cost[1][1] );
        memset(dp,0,sizeof(dp));

        for(i=1;i<=n;i++){
            dp[i] = 1LL<<60;

            act = pay + White.getBest() - Cost[0][i+1];
            dp[i] = min( dp[i],act );

            act = pay + Black.getBest() - Cost[1][i+1];
            dp[i] = min( dp[i],act );

            act = dp[i];
            White.addValue(i,act+Cost[0][i+1]);
            Black.addValue(i,act+Cost[1][i+1]);
        }

        printf("%lld\n",dp[n]);
    }


    return 0;
}
