#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 1024
#define mp make_pair
#define last(a,b) wh[a][b][ wh[a][b].size()-1 ]

long n,i;
long a[maxN],cnt[4];
vector<long> wh[4][4];
vector<long> rr[4];
vector< pair<long,long> > ans;

void exchange(long a,long b){
    long cnt = min(wh[a][b].size(),wh[b][a].size());
    for(;cnt--;){
        ans.push_back( mp( last(a,b) , last(b,a) ) );
        wh[a][b].pop_back(); wh[b][a].pop_back();
    }
}

void putAll(long s){
    long def;
    for(def=1;def<=3;def++){
        if(def==s) continue;
        if(wh[s][def].size()>0) break;
    }

    rr[s] = wh[s][def];
}

void move(long a,long b){
    for(long i=0;i<rr[a].size();i++)
        ans.push_back( mp( rr[a][i],rr[b][i] )  );
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("test.in","r",stdin);
    #endif // ONLINE_JUDGE

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld",&a[i]);
        cnt[a[i]]++;
    }

    for(i=1;i<=cnt[1];i++)                  wh[ 1 ][ a[i] ].push_back(i);
    for(i=cnt[1]+1;i<=cnt[1]+cnt[2];i++)    wh[ 2 ][ a[i] ].push_back(i);
    for(i=cnt[1]+cnt[2]+1;i<=n;i++)         wh[ 3 ][ a[i] ].push_back(i);

    exchange(1,2);
    exchange(1,3);
    exchange(2,3);

    putAll(1);
    putAll(2);
    putAll(3);

    if(rr[1].size()>0){
        if( a[ rr[1][0] ] == 2 ){ //! 2 3 1
            move(1,2);
            move(1,3);
        } else { //! 3 1 2
            move(1,3);
            move(1,2);
        }
    }

    printf("%ld\n",ans.size());
    for(i=0;i<ans.size();i++) printf("%ld %ld\n", ans[i].first,ans[i].second );

    return 0;
}
