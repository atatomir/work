#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 9011
#define mod 9973

int n, pr, i, c, ss, dd;
int dp[2][maxN];
vector<int> divs;

int main()
{
    freopen("numere6.in","r",stdin);
    freopen("numere6.out","w",stdout);

    scanf("%d%d", &n, &pr);
    for (i = 1; i <= pr; i++)
        if (pr % i == 0)
            divs.pb(i);

    ss = 0; dd = 1;
    for (i = 1; i <= 9; i++)
        dp[ss][i] = 1;

    for (i = 2; i <= n; i++) {

        for (auto d : divs)
            dp[dd][d] = 0;

        for (auto d : divs) {
            dp[ss][d] %= mod;

            for (c = 1; c <= 9; c++)
                if (d * c <= pr)
                    dp[dd][d * c] += dp[ss][d];
        }

        swap(ss, dd);
    }

    printf("%d", dp[ss][pr] % mod);


    return 0;
}
