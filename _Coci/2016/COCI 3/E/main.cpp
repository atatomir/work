#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define mod 1000000007
#define maxN 1016

int n, m, i, j, val;
int v[maxN];
vector<int> norm;
map<int, int> M;

pair<int, int> dp[maxN][maxN], aux[maxN][maxN];


inline void combine(pair<int, int>& a, pair<int, int> b) {
    if (a.first != b.first) {
        a = max(a, b);
    } else {
        a.second += b.second;
        if (a.second >= mod) a.second -= mod;
    }
}

void add_val(int tm) {
    int i, j;

    memcpy(aux, dp, sizeof(dp));

    for (i = 1; i <= m; i++)
        for (j = 1; j <= m; j++)
            if (dp[i][j].second > 0)
                combine(dp[i][j], dp[i][j]);
    combine(dp[val][val], mp(1, tm));

    for (i = val + 1; i <= m; i++)
        for (j = i; j <= m; j++)
            combine(dp[val][j], mp(aux[i][j].first + 1, aux[i][j].second));

    for (i = 1; i < val; i++)
        for (j = i; j < val; j++)
            combine(dp[i][val], mp(aux[i][j].first + 1, aux[i][j].second));
}

int main()
{
    //freopen("test.in","r",stdin);

    /*freopen("test.out", "w", stdout);

    printf("1000\n");
    for (i = 1; i <= 1000; i++) printf("%d ", i);

    return 0;*/

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        norm.pb(v[i]);
    }

    sort(norm.begin(), norm.end());
    norm.resize(unique(norm.begin(), norm.end()) - norm.begin());

    for (i = 0; i < norm.size(); i++) M[norm[i]] = i + 1;
    for (i = 1; i <= n; i++) v[i] = M[v[i]];
    m = norm.size();

    for (i = 1; i <= m; i++)
        for (j = 1; j <= m; j++)
            dp[i][j] = mp(- n - 1, 0);


    for (int step = 1; step <= n; step++) {
        val = v[step];
        add_val(min(2, step));
    }

    pair<int, int> ans = mp(-1, -1);
    for (i = 1; i <= m; i++)
        for (j = 1; j <= m; j++)
            combine(ans, dp[i][j]);

    printf("%d %d", ans.first, ans.second);

    return 0;
}
