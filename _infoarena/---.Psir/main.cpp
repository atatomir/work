#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 2015

const long long mod = (1LL<<32);
int n,i,last;
int v[maxN];
long long ans;
unsigned int wh[maxN][maxN];

int diff(int a,int b){
    a -= b;
    if (a<0) return -a;
    return a;
}

template< typename __T >
void keep(__T &who){
    while (who<0) who += mod;
    while (who>=mod) who-=mod;
}

void Minimize(){
    vector< pair<int,int> > aux; aux.clear();

    for (int i=1;i<=n;i++) aux.pb( mp(v[i],i) );
    sort(aux.begin(),aux.end());

    v[ aux[0].second ] = 1;
    for (int i=1;i<aux.size();i++){
        if (aux[i].first==aux[i-1].first)
            v[ aux[i].second ] = v[ aux[i-1].second ];
        else
            v[ aux[i].second ] = v[ aux[i-1].second ]+1;
    }
}

int main()
{
    freopen("psir.in","r",stdin);
    freopen("psir.out","w",stdout);

    scanf("%d",&n);
    for (i=1;i<=n;i++) scanf("%d",&v[i]);

    Minimize();
    memset(wh,0,sizeof(wh));

    for (i=2;i<=n;i++) {

        for (last=i-1;last>0;last--) {
            long long act = 1;

            if ( diff(v[last],v[i]) == 0) {
                wh[ i ][ v[last] ] += act;
                continue;
            }

            if (v[last]<v[i]) {
                //! find value in interval ( v[i],-- )
                act += wh[ last ][ n ] - wh[ last ][ v[i] ];
            } else {
                //! find value in interval ( --,v[i] )
                act += wh[ last ][ v[i]-1 ];
            }

            keep(act);
            wh[ i ][ v[last] ] += act;
        }

        for (int j=1;j<=n;j++) {
            wh[i][j] += wh[i][j-1];
            keep( wh[i][j] );
        }

        ans += wh[ i ][ n ];
        keep(ans);
        //cerr << ans << '\n';
    }


    printf("%lld",ans);


    return 0;
}
