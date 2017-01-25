#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

const int n = 15;
const int maxN = n + 11;

int i, j;
vector<int> divs[maxN];
int dp[maxN][maxN];


int main()
{

    for (i = 1; i <= n; i++)
        for (j = 1; j <= i; j++)
            if (i % j == 0)
                divs[i].pb(j);

    for (i = 1; i <= n; i++) {
        dp[0][i] = 1;


        int aux = i;
        for (j = 2; j <= aux; j++) {
            if (aux % j != 0) continue;
            dp[0][i] <<= 1;
            while (aux % j == 0) aux /= j;
        }
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            for (auto e : divs[j])
                dp[i][j] += dp[i - 1][e];
        }
    }

    for (i = 1; i <= n; i++)
        cerr << i << ' ';
    cerr << '\n';
    for (i = 1; i <= n; i++)
        cerr << "--";
    cerr << '\n';

    for (i = 0; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            cerr << dp[i][j] << ' ';
        }
        cerr << '\n';
    }


    return 0;
}
