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

#define maxN 2016

struct cuib {
    int type, xx1, yy1, xx2, yy2;
    int xx, yy, R;

    void read() {
        scanf("%d", &type);
        if (type == 0)
            scanf("%d%d%d%d", &xx1, &yy1, &xx2, &yy2);
        else
            scanf("%d%d%d", &xx, &yy, &R);
    }

    int dist (int xx1, int yy1, int xx2, int yy2) {
        return (xx1 - xx2) * (xx1 - xx2) + (yy1 - yy2) * (yy1 - yy2);
    }

    bool has_point(int wh_x, int wh_y) {
        if (type == 0) { //! rectangle
            return (xx1 <= wh_x && wh_x <= xx2 && yy1 <= wh_y && wh_y <= yy2);
        } else { //! circle
            return dist(xx, yy, wh_x, wh_y) <= R * R;
        }
    }

    bool has_in(const cuib& who) {
        if (type == 0) { //! rectangle
            if (who.type == 0) { //! rectangle
                return (xx1 <= who.xx1 && who.xx2 <= xx2 && yy1 <= who.yy1 && who.yy2 <= yy2);
            } else { //! circle
                return has_point(who.xx - who.R, who.yy) &&
                       has_point(who.xx + who.R, who.yy) &&
                       has_point(who.xx, who.yy - who.R) &&
                       has_point(who.xx, who.yy + who.R) ;
            }
        } else { //! circle
            if (who.type == 0) { //! rectangle
                return has_point(who.xx1, who.yy1) &&
                       has_point(who.xx1, who.yy2) &&
                       has_point(who.xx2, who.yy1) &&
                       has_point(who.xx2, who.yy2) ;
            } else { //! circle
                return sqrt(1.00 * dist(xx, yy, who.xx, who.yy) ) + who.R <= 1.00 * R;
            }
        }
    }
};

int n, i, j, ans;
cuib C[maxN];

vector<int> list[maxN];
int gr[maxN];
int dp[maxN];

queue<int> Q;

int main()
{
    freopen("cuiburi.in","r",stdin);
    freopen("cuiburi.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        C[i].read();

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            bool dir = C[i].has_in(C[j]);
            bool inv = C[j].has_in(C[i]);

            if (dir) {
                list[i].pb(j);
                gr[j]++;
            }
            if (!dir && inv) {
                list[j].pb(i);
                gr[i]++;
            }
        }
    }

    ans = 1;
    for (i = 1; i <= n; i++) {
        if (gr[i]) continue;
        Q.push(i);
        dp[i] = 1;
    }

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();

        for (auto to : list[node]) {
            if (--gr[to] == 0) Q.push(to);
            dp[to] = max(dp[node] + 1, dp[to]);
        }

        ans = max(ans, dp[node]);
    }

    printf("%d", ans);
    return 0;
}
