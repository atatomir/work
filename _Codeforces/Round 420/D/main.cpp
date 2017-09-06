#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <functional>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 200011
#define inf 1000000000

int ln, co, n, i, x, y, R;
pair<int, int> P[maxN];
vector< pair<int, int> > pos_ln[maxN];
vector< pair<int, int> > pos_co[maxN];
int up[maxN], down[maxN], le[maxN], ri[maxN];

priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > H;
int dist[maxN];
int ans = inf;

void upd(int where, int val) {
    if (dist[where] > val) {
        dist[where] = val;
        H.push(mp(val, where));
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d%d", &ln, &co, &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &x, &y);
        P[i] = mp(x, y);
        pos_ln[x].pb(mp(y, i));
        pos_co[y].pb(mp(x, i));

        if (x == 1 && y == 1) R = i;
    }

    for (i = 1; i <= ln; i++) sort(pos_ln[i].begin(), pos_ln[i].end());
    for (i = 1; i <= co; i++) sort(pos_co[i].begin(), pos_co[i].end());

    for (i = 1; i <= n; i++) {
        x = P[i].first;
        y = P[i].second;

        auto it = lower_bound(pos_ln[x].begin(), pos_ln[x].end(), mp(y, 0));
        if (it != pos_ln[x].begin()) {
            it--;
            le[i] = it->second;
            it++;
        }
        it++;
        if (it != pos_ln[x].end())
            ri[i] = it->second;
        it--;

        it = lower_bound(pos_co[y].begin(), pos_co[y].end(), mp(x, 0));
        if (it != pos_co[y].begin()) {
            it--;
            up[i] = it->second;
            it++;
        }
        it++;
        if (it != pos_co[y].end())
            down[i] = it->second;
        it--;
    }

    for (i = 1; i <= 20 * n; i++) dist[i] = inf;

    dist[R << 4] = 0;
    H.push(mp(0, R << 4));

    int to, cost, tp2;
    while (!H.empty()) {
        int node = H.top().second;
        int val = H.top().first;
        H.pop();

        if (dist[node] != val) continue;
        int id = node >> 4;
        int tp = node & 15;
        x = P[id].first;
        y = P[id].second;

        if (P[id] == mp(ln, co)) ans = min(ans, val);
        if (P[id].first == ln && tp == 1) ans = min(ans, val);
        if (P[id].second == co && tp == 4) ans = min(ans, val);
        if (P[id].first == ln && tp == 2) ans = min(ans, val + 1);
        if (P[id].second == co && tp == 8) ans = min(ans, val + 1);
        if (P[id].first == ln - 1 && tp == 1) ans = min(ans, val + 1);
        if (P[id].second == co - 1 && tp == 4) ans = min(ans, val + 1);

        //! lit this line
        upd(id * 16 + 1, dist[node] + 1);

    ///
        //! lit prev line
        if (pos_ln[x - 1].size() > 0)
            upd(pos_ln[x - 1][0].second * 16 + 1, val + 1);

        //! lit next line
        if (pos_ln[x + 1].size() > 0)
            upd(pos_ln[x + 1][0].second * 16 + 1, val + 1);

        //! lit prev line
        if (pos_ln[x - 2].size() > 0)
            upd(pos_ln[x - 2][0].second * 16 + 2, val + 1);

        //! lit next line
        if (pos_ln[x + 2].size() > 0)
            upd(pos_ln[x + 2][0].second * 16 + 2, val + 1);
    ///

        //! lit this column
        upd(id * 16 + 4, dist[node] + 1);

    ///
        //! lit prev column
        if (pos_co[y - 1].size() > 0)
            upd(pos_co[y - 1][0].second * 16 + 4, val + 1);

        //! lit next column
        if (pos_co[y + 1].size() > 0)
            upd(pos_co[y + 1][0].second * 16 + 4, val + 1);

        //! lit prev column
        if (pos_co[y - 2].size() > 0)
            upd(pos_co[y - 2][0].second * 16 + 8, val + 1);

        //! lit next column
        if (pos_co[y + 2].size() > 0)
            upd(pos_co[y + 2][0].second * 16 + 8, val + 1);
    ///



        //! jump on prev/next line
        if (tp == 1) {
            if (pos_ln[x - 1].size())
                upd(pos_ln[x - 1][0].second * 16 + 2, dist[node]);
            if (pos_ln[x + 1].size())
                upd(pos_ln[x + 1][0].second * 16 + 2, dist[node]);
        }

        //! jump on prev/next column
        if (tp == 4) {
            if (pos_co[y - 1].size())
                upd(pos_co[y - 1][0].second * 16 + 8, dist[node]);
            if (pos_co[y + 1].size())
                upd(pos_co[y + 1][0].second * 16 + 8, dist[node]);
        }

        //! move left
        to = le[id];
        tp2 = tp & 3;
        if (to != 0) {
            if (tp == 1 || P[id].second == P[to].second + 1) {
                upd(to * 16 + tp2, dist[node]);
            }
        }

        //! move right
        to = ri[id];
        tp2 = tp & 3;
        if (to != 0) {
            if (tp == 1 || tp == 2 || P[id].second + 1 == P[to].second) {
                upd(to * 16 + tp2, dist[node]);
            }
        }

        //! move up
        to = up[id];
        tp2 = tp & 12;
        if (to != 0) {
            if (tp == 4 || P[id].first == P[to].first + 1) {
                upd(to * 16 + tp2, dist[node]);
            }
        }

        //! move down
        to = down[id];
        tp2 = tp & 12;
        if (to != 0) {
            if (tp == 4 || tp == 8 || P[id].first + 1 == P[to].first) {
                upd(to * 16 + tp2, dist[node]);
            }
        }

    }

    if (ans >= inf) ans = -1;
    printf("%d\n", ans);

    return 0;
}
