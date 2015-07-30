#include <iostream>
#include <fstream>

using namespace std;

#define mod 9001

ifstream fin("flori4.in");
ofstream fout("flori4.out");

long dp[10011],n;

int main()
{
    fin >> n;
    dp[1] = 1; dp[2] = 2;
    for(long i=3;i<=n;i++) dp[i] = (1 + dp[i-1] + dp[i-2])%mod;
    fout << dp[n];

    return 0;
}
