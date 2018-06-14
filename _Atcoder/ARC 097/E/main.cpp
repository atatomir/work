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

const int maxN = 2 * 2018;

int n, i, j;
char c[maxN];
int v[maxN];
int wh[2][maxN];

int data[maxN];
int dp[maxN][maxN];

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void add(int pos, int val) {
    while (pos <= 2 * n) {
        data[pos] += val;
        pos += zrs(pos);
    }
}

int sum(int pos) {
    int ans = 0;
    while (pos > 0) {
        ans += data[pos];
        pos -= zrs(pos);
    }
    return ans;
}

int main()
{
    freopen("test.in","r",stdin);
    
    scanf("%d\n", &n);
    for (i = 1; i <= 2 * n; i++) {
        scanf("%c %d\n", &c[i], &v[i]);

        if (c[i] == 'W') {
            wh[0][v[i]] = i;
        } else {
            wh[1][v[i]] = i;
        }
    }
    
    for (i = 0; i <= n; i++)
        for (j = 0; j <= n; j++)
            dp[i][j] = 10 * n * n;
    dp[0][0] = 0;

    for (i = 0; i <= n; i++) {
        if (i > 0) add(wh[0][i], +1);
        for (j = 0; j <= n; j++) {
            
            if (j > 0)
                add(wh[1][j], +1);

            if (i < n)
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + wh[0][i + 1] - 1 -
                sum(wh[0][i + 1]));

            if (j < n)
                dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + wh[1][j + 1] - 1 -
                sum(wh[1][j + 1]));
        }

        for (j = 1; j <= n; j++) 
            add(wh[1][j], -1);
    }

    /*for (i = 0; i <= n; i++, cerr << '\n') {
        for (j = 0; j <= n; j++)
            cerr << dp[i][j] << ' ';
    }*/

    printf("%d", dp[n][n]);

    return 0;
}
