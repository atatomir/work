#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 256
#define pi pair<int, int>

int n, k, i, last_open, cnt, last;
pi Player[maxN];
vector<int> larger;
vector<int> best_dims;
int ans;

int dp[maxN][maxN]; //! groups, pos

bool cmp(const pi a, const pi b) {
    if (a.second == b.second)
        return a.first > b.first;
    return a.second < b.second;
}

void make_dp() {
    int i, j, first_el;

    for (i = 1; i <= n; i++)
        dp[0][i] = -1000000000;

    for (i = 1; i <= k; i++) {
        for (j = 1; j <= n; j++) {
            dp[i][j] = dp[i - 1][j];
            for (first_el = 1; first_el <= j; first_el++)
                dp[i][j] = max(dp[i][j], dp[i - 1][first_el - 1] + Player[first_el].second - Player[j].first);
        }
    }
}

void try_no_groups() {
    int pos = best_dims.size() - 1;
    int how = k - 1;
    int sol = 0;

    sort(best_dims.begin(), best_dims.end());
    while (pos >= 0 && how > 0) {
        sol += best_dims[pos];
        pos--;
        how--;
    }

    ans = max(ans, sol);
}

int main()
{
    freopen("echipe.in","r",stdin);
    freopen("echipe.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &Player[i].first, &Player[i].second);
        best_dims.pb(Player[i].second - Player[i].first);
    }

    sort(Player + 1, Player + n + 1, cmp);

    last_open = -1;
    for (i = 1; i <= n; i++) {
        if (Player[i].first <= last_open) { //! is larger
            larger.pb(Player[i].second - Player[i].first);
        } else { //! good
            Player[++cnt] = Player[i];
        }

        last_open = max(last_open, Player[i].first);
    }

    n = cnt;
    make_dp();
    sort(larger.begin(), larger.end());

    ans = dp[k][n];
    try_no_groups();
    while (larger.size() > 0 && k > 0) {
        int el = larger[larger.size() - 1];
        larger.pop_back();

        last += el;
        ans = max(ans, last + dp[--k][n]);
    }

    printf("%d", ans);

    return 0;
}
