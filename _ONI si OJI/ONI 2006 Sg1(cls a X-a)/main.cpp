#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 111
#define def 35

class extra_long {
    public:
        int dim;
        char data[def];

        void init( int );
        void operator=( extra_long& );
        void operator+=( extra_long& );
        void operator-=( extra_long& );
        void write();
};

int n,k,i,j,low,high,pos,cnt;
int Start,Stop;
extra_long dp[maxN][maxN];
/*
 *  dp[pos][cnt] - nr de conf de la 1..pos cu cnt selectate
 */

void extra_long :: init(int v){
    //! v is a digit
    memset(data,0,sizeof(data));

    if (v == 0) {
        dim = 1;
        return;
    }

    dim = 0;
    while (v > 0) {
        data[ ++dim ] = v % 10;
        v /= 10;
    }
}
void extra_long :: operator=(extra_long& who){
    dim = who.dim;
    memcpy(data,who.data, sizeof(data) );
}
void extra_long :: operator+=(extra_long& who){
    int i;
    dim = max(dim,who.dim);
    data[dim+1] = 0;

    for (i = 1; i <= dim; i++) data[i] += who.data[i];
    for (i = 1; i <= dim; i++) {
        if (data[i] < 10) continue;
        data[i+1] += data[i]/10;
        data[i] %= 10;
    }

    if( data[dim+1]!=0 ) dim++;
}
void extra_long :: operator-=(extra_long& who){
    int i ;

    for (i = 1; i <= dim; i++) {
        data[i] -= who.data[i];
        while (data[i] < 0) {
            data[i] += 10;
            data[i+1]--;
        }
    }

    while ( dim > 1 && data[dim] == 0 ) dim--;
}
void extra_long :: write(){
    for (int i = dim; i > 0; i--) printf("%d",data[i]);
}

int main()
{
    freopen("sg1.in","r",stdin);
    freopen("sg1.out","w",stdout);

    scanf("%d%d%d%d",&n,&k,&low,&high);
    low++; high++;

    for (i = 0; i <= n; i++)
        for (j = 0; j <= k; j++)
            dp[i][j].init(0);

    for (i = 1; i <= n; i++) dp[1][i].init(i);

    for (cnt = 2; cnt <= k; cnt++) {
        for (pos = 1; pos <= n; pos++) {
            dp[cnt][pos] = dp[cnt][pos-1];

            Start = max(pos - high - 1,0);
            Stop  = max(pos - low     ,0);

            dp[cnt][pos] += dp[cnt-1][Stop] ;
            dp[cnt][pos] -= dp[cnt-1][Start];
        }
    }

    dp[k][n].write();

    return 0;
}
