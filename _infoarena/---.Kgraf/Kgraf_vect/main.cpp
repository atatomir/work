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

#define maxN 311

struct elem {
    int k1, k2, val;

    bool operator<(const elem& who)const {
        return mp(mp(k1, k2), val) < mp(mp(who.k1, who.k2), who.val);
    }

    bool operator==(const elem& who)const {
        return mp(k1, k2) == mp(who.k1, who.k2);
    }
};

int n, m, k, i, x, y, c;
vector< pair<int, int> > list[maxN];
int gr[maxN];

queue<int> Q;
vector<elem> dp[maxN];
int ans = -1;

void norm(vector<elem>& v) {
    int pos = 0;

    // remove (a, b, c) if exists (a, b, c + d) , d > 0
    for (int i = 1; i < v.size(); i++) {
        if (v[i - 1] == v[i])
            v[pos] = v[i];
        else
            v[++pos] = v[i];
    }

    v.resize(pos + 1);
    if (v.back().k1 == k && v.back().k2 == k)
        ans = max(ans, v.back().val);

    // vraja
    if (v.size() > n) return;

    for (int i = 0; i < v.size(); i++) {
        bool good = true;

        for (int j = 0; j < v.size(); j++)
            if (v[i].k1 < v[k].k1 && v[i].k2 > v[j].k2 && v[i].val < v[j].val)
                {good = false; break;}

        if (!good) {
            v[i] = v.back();
            v.pop_back();
            i--;
            continue;
        }
    }
}

int main()
{
    freopen("kgraf.in","r",stdin);
    freopen("kgraf.out","w",stdout);

    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &c);
        list[x].pb(mp(y, c));
        gr[y]++;
    }

    for (i = 1; i <= n; i++)
        if (gr[i] == 0)
            dp[i] = {{0, 0, 0}}, Q.push(i);

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();

        //dp[node].pb({0, 0, 0});
        sort(dp[node].begin(), dp[node].end());
        norm(dp[node]);

        for (auto to : list[node]) {
            if (--gr[to.first] == 0)
                Q.push(to.first);

            for (auto e : dp[node]) {
                dp[to.first].pb(e);

                if (e.k1 < k)
                    dp[to.first].pb({e.k1 + 1, e.k2, e.val - to.second});
                if (e.k2 < k)
                    dp[to.first].pb({e.k1, e.k2 + 1, e.val + to.second});

                if (e.k1 < k && e.k2 < k)
                    dp[to.first].pb({e.k1 + 1, e.k2 + 1, e.val});
            }
        }

        dp[node].clear();
    }

    printf("%d", ans);

    return 0;
}
