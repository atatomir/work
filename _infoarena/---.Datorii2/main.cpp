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

#define maxN 22
#define inf 1000000000

int n, m, i, aux2;
int a, b, c, aux;
int dat[maxN];

int dp[1 << 20], sumi[1 << 20];
int from[1 << 20];

vector<int> ids, act, le, ri;
int ans2;

int abss(int x) {
    if (x < 0) return -x;
    return x;
}

void solve(vector<int>& ids) {
    int p1, p2, mini;

    le.clear();
    ri.clear();

    for (auto e : ids) {
        if (dat[e] > 0)
            le.pb(e);
        if (dat[e] < 0)
            ri.pb(e);
    }

    p2 = 0;
    for (p1 = 0; p1 < le.size(); p1++) {
        if (dat[ le[p1] ] == 0) continue;

        while (dat[ ri[p2] ] == 0) p2++;
        mini = min(dat[ le[p1] ], -dat[ ri[p2] ]);
        printf("%d %d %d\n", le[p1] + 1, ri[p2] + 1, mini);
        dat[ le[p1] ] -= mini;
        dat[ ri[p2] ] += mini;

        p1--;
    }
}

int main()
{
    freopen("datorii2.in","r",stdin);
    freopen("datorii2.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &a, &b, &c); a--; b--; swap(a, b);
        dat[a] -= c;
        dat[b] += c;
    }

    for (i = 0; i < n; i++) ans2 += max(0, dat[i]);

    int limit = (1 << n);
    for (int conf = 0; conf < limit; conf++) dp[conf] = n;
    dp[0] = 0;


    for (int conf = 0; conf < limit; conf++) {
        if (sumi[conf] == 0)
            aux = dp[conf];
        else
            aux = dp[conf] + 1;

        for (i = 0; i < n; i++) {
            if (conf & (1 << i)) continue;
            if (dp[conf | (1 << i)] > aux) {
                sumi[conf | (1 << i)] = sumi[conf] + dat[i];
                dp[conf | (1 << i)] = aux;
                from[conf | (1 << i)] = i;
            }
        }
    }

    for (int conf = limit - 1; conf != 0; conf ^= 1 << from[conf])
        ids.pb(from[conf]);

    printf("%d %d\n", dp[limit - 1], ans2);

    while (!ids.empty()) {
        int sumi;

        act = {ids.back()};
        sumi = dat[ids.back()];
        ids.pop_back();

        while (sumi != 0) {
            act.pb(ids.back());
            sumi += dat[ids.back()];
            ids.pop_back();
        }

        solve(act);
    }




    return 0;
}
