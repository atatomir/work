#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1050

int n, m, i, j;
int A[maxN], B[maxN];

int ss, dd;
int dp[2][maxN];
int prov[2][maxN];

vector< pair<int, int> > ans;
vector<int> sol;

void solve(int l1, int c1, int l2, int c2) {
    int i, j;

    if (l1 == l2) {
        for (i = c1 + 1; i < c2; i++)
            ans.pb(mp(l1, i));
        return;
    }

    if (l1 + 1 == l2) {
        int wh = c1;

        for (i = c1 + 1; i <= c2; i++)
            if (A[l2] == B[i])
                wh = i;

        for (i = c1 + 1; i < wh; i++)
            ans.pb(mp(l1, i));
        for (i = wh; i < c2; i++)
            ans.pb(mp(l2, i));

        return;
    }

    ss = 0;
    dd = 1;
    for (i = c1; i <= c2; i++)
        dp[ss][i] = 0;

    int mid = (l1 + l2) >> 1;

    for (i = l1 + 1; i <= mid; i++) {
        dp[dd][c1] = dp[ss][c1];
        for (j = c1 + 1; j <= c2; j++) {
            if (A[i] == B[j])
                dp[dd][j] = dp[ss][j - 1] + 1;
            else
                dp[dd][j] = max(dp[ss][j], dp[dd][j - 1]);
        }

        swap(ss, dd);
    }

    for (i = c1; i <= c2; i++)
        prov[ss][i] = i;

    for (i = mid + 1; i <= l2; i++) {
        dp[dd][c1] = dp[ss][c1];
        prov[dd][c1] = prov[ss][c1];

        for (j = c1 + 1; j <= c2; j++) {
            if (A[i] == B[j]) {
                dp[dd][j] = dp[ss][j - 1] + 1;
                prov[dd][j] = prov[ss][j - 1];
            } else {
                if (dp[ss][j] > dp[dd][j - 1])
                    prov[dd][j] = prov[ss][j];
                else
                    prov[dd][j] = prov[dd][j - 1];

                dp[dd][j] = max(dp[ss][j], dp[dd][j - 1]);
            }
        }

        swap(ss, dd);
    }

    int from = prov[ss][c2];

    solve(l1, c1, mid, from);
    ans.pb(mp(mid, from));
    solve(mid, from, l2, c2);
}

int main()
{
    freopen("cmlsc.in","r",stdin);
    freopen("cmlsc.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
        scanf("%d", &A[i]);
    for (i = 1; i <= m; i++)
        scanf("%d", &B[i]);

    A[0] = -1;
    B[0] = -2;

    ans.pb(mp(0, 0));
    solve(0, 0, n, m);
    ans.pb(mp(n, m));

    for (i = 1; i < ans.size(); i++) {
        if (ans[i].first != ans[i - 1].first &&
            ans[i].second != ans[i - 1].second)
                sol.pb(A[ ans[i].first ]);
    }

    printf("%d\n", sol.size());
    for (auto e : sol)
        printf("%d ", e);

    return 0;
}
