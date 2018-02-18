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

#define maxN 111

int n, i, j;
int a[5][maxN], dp[5][maxN];

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= 2; i++) {
        for (j = 1; j <= n; j++) {
            cin >> a[i][j];
            dp[i][j] += a[i][j];

            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            dp[i][j + 1] = max(dp[i][j + 1], dp[i][j]);
        }
    }

    cout << dp[2][n];


    return 0;
}
