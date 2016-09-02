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

#define maxN 1024
#define base 10000

int n, m, B, i, x, y, d;
int S, D;
int pay[maxN];
vector< pair<int, int> > list[maxN];
priority_queue< pair<int, int> > H;
int dp[maxN][maxN];

int main()
{
    freopen("drum-bugetat.in","r",stdin);
    freopen("drum-bugetat.out","w",stdout);

    scanf("%d%d%d", &n, &m, &B);
    scanf("%d%d", &S, &D);
    for (i = 1; i <= n; i++) scanf("%d", &pay[i]);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &d);
        list[x].pb(mp(y, d));
        list[y].pb(mp(x, d));
    }

    dp[S][0] = 1;
    H.push(mp(-1, S * base + 0));

    int val, node, bug;

    while (!H.empty()) {
        auto top = H.top(); H.pop();
        val = -top.first;
        node = top.second / base;
        bug = top.second % base;

        if (dp[node][bug] != val) continue;

        for (auto to : list[node]) {
            if (bug + pay[to.first] > B) continue;

            if (dp[to.first][bug + pay[to.first]] == 0 ||
                dp[to.first][bug + pay[to.first]] > val + to.second) {
                    dp[to.first][bug + pay[to.first]] = val + to.second;
                    H.push(mp(-val - to.second, to.first * base + bug + pay[to.first] ));
                }
        }
    }

    for (i = 0; dp[D][i] == 0 && i <= B; i++);
    if (i == B + 1) {
        printf("-1");
        return 0;
    }

    pair<int, int> best = mp(1000000000, 0);
    for (i = 0; i <= B; i++) {
        if (dp[D][i] == 0) continue;
        best = min(best, mp(dp[D][i] - 1, i));
    }

    printf("%d %d", best.first, best.second);


    return 0;
}
