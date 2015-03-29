#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("energii.in");
ofstream fout("energii.out");

long q,w,i,s,d,j;
long dp[2][5005];
long cost,ener,dest;
const long def = 1 << 30;

void Reset(long d){
    for(long i= 0;i<=w;i++) dp[d][i] = dp[s][i];
}

int main()
{
    fin >> q >> w;

    s=0; d=1;
    dp[s][0] = 0;
    for(i=1;i<=w;i++) dp[s][i] = def;

    for(i=1;i<=q;i++){
        fin >> ener >> cost;
        Reset(d);
        for(j=w-1;j>=0;j--){
            if(dp[s][j] == def) continue;
            dest = j + ener; if(dest > w) dest = w;
            dp[d][dest] = min(dp[d][dest],dp[s][j] + cost);
        }
        s ^= 1; d ^= 1;
    }

    if(dp[s][w] == def) dp[s][w] = -1;
    fout << dp[s][w];

    return 0;
}
