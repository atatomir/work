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

const int maxN = 311;

int n, k, m, i, j, p, aux;
int dp[maxN][maxN];
int sum[maxN][maxN];
int comb[maxN][maxN];

void add(int& a, int b) {
    a += b;
    if (a >= m) a -= m;
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n >> k >> m;
    n++; k++;

    for (i = 0; i <= n; i++) {
        comb[i][0] = 1;
        for (j = 1; j <= i; j++)
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % m;
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= k; j++) {
            if (i == 1) {
                dp[i][j] = 1;
            } else {
                for (p = 1; p < i; p++) {
                    aux = (1LL * dp[p][j] * sum[i - p][j - 1]) % m;
                    aux = (1LL * aux * comb[i - 2][p - 1]) % m;
                    add(dp[i][j], aux);
                }
            }

            sum[i][j] = (sum[i][j - 1] + dp[i][j]) % m;
        
            //cerr << dp[i][j] << ' ';
        }
        //cerr << '\n';
    }

    cout << dp[n][k];


    return 0;
}
