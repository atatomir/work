#include <iostream>
#include <iomanip>

using namespace std;

#define maxN 100011

long n,i;
double m;
double dp[maxN];

int main()
{
    cin >> m >> n;
    dp[1] = 1;
    for(i=2;i<=n;i++) dp[i] = ((dp[i-1]*dp[i-1]) + (m-dp[i-1])*(dp[i-1]+1))/m;
    cout << setprecision(10) << dp[n];

    return 0;
}
