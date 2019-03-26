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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

const int defX[2] = {1, 0};
const int defY[2] = {0, 1};

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

const int maxN = 111;

int n, i, j, k, x, y, xx, yy, go_x, go_y, go_xx, go_yy, a, b;
char s[maxN][maxN];
int dp[2 * maxN][maxN][maxN];

void upd(int& a, int b) {
    if (a < b) a = b;
}

int take() {
    int ans = 0;

    if (s[go_x][go_y] == '1') ans++;
    if (s[go_xx][go_yy] == '1') ans++;
    if (go_x == go_xx && go_y == go_yy) ans = min(ans, 1);
    return ans;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d\n", &n);
    for (i = 1; i <= n; i++) scanf("%s\n", s[i] + 1);
    dp[2][1][1] = 1 + (s[1][1] == '1');

    for (i = 1; i <= 2 * n; i++) {
        for (j = 1; j <= n && j <= i; j++) {
            x = j;
            y = i - j;
            if (y < 1 || y > n) continue;

            for (k = 1; k <= n && k <= i; k++) {
                xx = k;
                yy = i - k;
                if (yy < 1 || yy > n) continue;
                if (dp[i][j][k] == 0) continue;


                //debug(i);
                //debug(j);
                //debug(k);

                for (a = 0; a < 2; a++) {
                    go_x = x + defX[a];
                    go_y = y + defY[a];
                    if (go_x < 1 || go_x > n) continue;
                    if (go_y < 1 || go_y > n) continue;

                    for (b = 0; b < 2; b++) {
                        go_xx = xx + defX[b];
                        go_yy = yy + defY[b];

                        if (go_xx < 1 || go_xx > n) continue;
                        if (go_yy < 1 || go_yy > n) continue;

                        upd(dp[go_x + go_y][go_x][go_xx], dp[i][j][k] + take());
                    }
                }
            }
        }
    }

    //debug(dp[2][1][2]);

    cout << dp[n + n - 1][n][n] - 1;

    return 0;
}
