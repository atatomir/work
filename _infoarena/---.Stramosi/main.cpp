#include <iostream>
#include <cstdio>
#include <fstream>

using namespace std;

#define maxN 250005
#define maxLog 25
#define maxLLog 19

long n,m,i,j,q,p,tmp;
long dp[maxLog][maxN];
bool util;

int main()
{
    ifstream in("stramosi.in");
    ofstream out("stramosi.out");

    in >> n >> m;
    for(i=1;i<=n;i++) in >> dp[0][i];

    for(j=1;j<=maxLLog;j++){
        util = false;
        for(i=1;i<=n;i++){
            dp[j][i] = dp[j-1][dp[j-1][i]];
            if(dp[j][i]) util = true;
        }
        if(!util) break;
    }

    for(;m;m--){
        in >> q >> p;

        for(i=0;p;p>>=1,i++)
            if(p&1)
                q = dp[i][q];

        out << q << '\n';
    }

    return 0;
}
