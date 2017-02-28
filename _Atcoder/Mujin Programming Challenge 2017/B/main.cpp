#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 555

int n, i, j, ans;
char s[maxN][maxN];
bool found, ok, any;
int cnt[maxN];

queue< pair<int, int> > Q;
int dp[maxN][maxN];

bool is_good[maxN];
int cnt_good;

void solve() {
    int i, j;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (s[i][j] == '#') {
                dp[i][j] = 1;
                Q.push(mp(i, j));
            }
        }
    }

    while (!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();

        for (i = 1; i <= n; i++) {
            if (dp[y][i] == 0) {
                dp[y][i] = dp[x][y] + 1;
                Q.push(mp(y, i));
            }
        }
    }
}

int main()
{
    freopen("test.in","r",stdin);

    found = false;

    scanf("%d\n", &n);
    for (i = 1; i <= n; i++) {
        scanf("%s\n", s[i] + 1);

        if (!found) {
            found = true;
            for (j = 1; j <= n; j++)
                if (s[i][j] == '.')
                    found = false;
        }

        for (j = 1; j <= n; j++) {
            if (s[i][j] == '.')
                cnt[i]++;
            else
                any = true;
        }
    }

    if (!any) {
        printf("-1");
        return 0;
    }


    for (j = 1; j <= n; j++) {
        ok = true;

        for (i = 1; i <= n; i++)
            if (s[i][j] == '.')
                ok = false;

        is_good[i] = ok;
        if (ok) cnt_good++;
    }

    if (found) {
        ans = n - cnt_good;

        printf("%d", ans);

        return 0;
    }

    solve();

    ans = 2 * n;
    /*for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (dp[i][j] > 0)
                ans = min(ans, n + cnt[j] + 2 * (dp[i][j] - 1));*/

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (s[i][j] == '#')
                ans = min(ans, n - cnt_good + cnt[j]);

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (i == j) continue;
            if (cnt[i] == n) continue;

            ans = min(ans, n - cnt_good + cnt[i] + 1 );
        }
    }

    printf("%d", ans);




    return 0;
}
