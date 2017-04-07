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

#define maxN 200011
#define maxLog 19

int n, i, j, pos, V, k, limit, id, conf, new_conf, mini;
int x[maxN];
vector<int> v;
int l[maxLog][maxN], r[maxLog][maxN];

int dpL[1 << maxLog], dpR[1 << maxLog];
vector< pair<int, int> > ord, que;

bool ans[maxN];

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &V);
    for (i = 1; i <= n; i++) scanf("%d", &x[i]);
    v = {V / 2};
    while (v.back() != 0) v.pb(v.back() / 2);
    k = v.size();

    for (i = 0; i < k; i++) {
        l[i][1] = 1;
        for (pos = 2; pos <= n; pos++) {
            if (x[pos] - x[pos - 1] <= v[i])
                l[i][pos] = l[i][pos - 1];
            else
                l[i][pos] = pos;
        }

        r[i][n] = n;
        for (pos = n - 1; pos > 0; pos--) {
            if (x[pos + 1] - x[pos] <= v[i])
                r[i][pos] = r[i][pos + 1];
            else
                r[i][pos] = pos;
        }
    }

    limit = 1 << k;
    for (i = 0; i < limit; i++) {
        dpL[i] = 0;
        dpR[i] = n + 1;
    }

    for (conf = 0; conf < limit; conf++) {
        for (id = 0; id < k; id++) {
            if (conf & (1 << id)) continue;
            new_conf = conf | (1 << id);

            dpL[new_conf] = max(dpL[new_conf], min(n, r[id][ dpL[conf] + 1 ]));
            dpR[new_conf] = min(dpR[new_conf], max(1, l[id][ dpR[conf] - 1 ]));
        }
    }

    for (conf = 0; conf < limit; conf++)
        ord.pb(mp(dpL[conf], dpR[(limit - 1) ^ conf]));

    sort(ord.begin(), ord.end());
    reverse(ord.begin(), ord.end());

    for (i = 1; i <= n; i = j) {
        for (j = i + 1; j <= n && x[j] - x[j - 1] <= V; j++);
        que.pb(mp(i, j - 1));
    }

    reverse(que.begin(), que.end());

    pos = 0;
    mini = n + 2;

    for (auto e : que) {
        while (pos < ord.size()) {
            if (ord[pos].first + 1 < e.first) break;
            mini = min(mini, ord[pos].second);
            pos++;
        }

        if (mini <= e.second + 1) {
            for (i = e.first; i <= e.second; i++)
                ans[i] = true;
        }
    }

    for (i = 1; i <= n; i++) {
        if (ans[i])
            printf("Possible\n");
        else
            printf("Impossible\n");
    }


    return 0;
}
