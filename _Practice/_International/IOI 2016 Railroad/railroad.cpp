/*
 *  flow[i] - how many times we passed (i -> i + 1) - (i + 1 -> i)
 *  flow[i] must be 1 for every i
 *  first increment(cost 0)/decrement(cost 1) the array to achive the goal
 *  then merge the components to build an Eulerian Path
 *  more details: http://pastebin.com/bQFBVV2x
 *
 *  PS: don't undefine BETTER :))
 */


#include "railroad.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define BETTER
#define maxN 200011
#define BAD 17

#ifdef BETTER

int n, i;
vector<int> nodes;
int flow[maxN << 1];
int dad[maxN << 1];

vector< pair<int, int> > tunnel;


int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

bool Merge(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x == y) return false;
    dad[x] = y;
    return true;
}

int get_id(int x) {
    return lower_bound(nodes.begin(), nodes.end(), x) - nodes.begin();
}

long long plan_roller_coaster(std::vector<int> s, std::vector<int> t) {
    ll ans = 0;
    n = (int) s.size();

    nodes.clear();
    for (i = 0; i < n; i++)
        nodes.pb(s[i]), nodes.pb(t[i]);

    sort(nodes.begin(), nodes.end());
    nodes.resize(unique(nodes.begin(), nodes.end()) - nodes.begin());

    for (i = 0; i < nodes.size(); i++) dad[i] = i, flow[i] = 0;

    for (i = 0; i < n; i++) {
        int id1 = get_id(s[i]);
        int id2 = get_id(t[i]);

        flow[id1]++;
        flow[id2]--;
        Merge(id1, id2);
    }

    for (i = 0; i < nodes.size(); i++) {
        if (i > 0) flow[i] += flow[i - 1];

        if (flow[i] != 1)
            Merge(i, i + 1);
        if (flow[i] > 1)
            ans += 1LL * (flow[i] - 1) * (nodes[i + 1] - nodes[i]);
    }

    tunnel.clear();
    for (i = 1; i < nodes.size(); i++)
        tunnel.pb(mp(nodes[i] - nodes[i - 1], i - 1));

    sort(tunnel.begin(), tunnel.end());

    for (auto e : tunnel)
        if (Merge(e.second, e.second + 1))
            ans += 1LL * e.first;

    return ans;
}











#else



int n, i, need;
pair<int, int> v[maxN];

set< pair< pair<int, int>, int> > S[maxN];
int fin;

ll brute_force();

int zrs(int x) {
    return (x & (x - 1)) ^ x;
}

int inv(int x) {
    return n - x + 1;
}

void add(int pos) {
    int x = inv(pos);
    while (x <= n) {
        S[x].insert(mp(v[pos], pos));
        x += zrs(x);
    }
}

void rm(int pos) {
    int x = inv(pos);
    while (x <= n) {
        S[x].erase(mp(v[pos], pos));
        x += zrs(x);
    }
}

int worst(int pos) {
    pair< pair<int, int> , int> ans = mp(mp(1 << 30, -1), -1);
    set< pair< pair<int, int> , int> >::iterator it;

    while (pos > 0) {
        if (S[pos].empty() == false) {
            it = S[pos].end();
            it--;

            ans = min(ans, *it);
        }
        pos -= zrs(pos);
    }

    return ans.second;
}

long long plan_roller_coaster(std::vector<int> s, std::vector<int> t) {
    n = (int) s.size();

    for (i = 0; i < n; i++)
        v[i + 1] = mp(s[i], -t[i]);

    if (n <= 16)
        return brute_force();

    sort(v + 1, v + n + 1);
    for (i = 1; i <= n; i++) S[i].clear();

    fin = 1;
    for (i = 2; i <= n; i++) {
        if (-v[i].second == -v[fin].second)
            if (v[i].first > v[fin].first)
                fin = i;
        if (-v[i].second > -v[fin].second)
            fin = i;
    }

    if (fin == 1) return 0;

    for (i = 2; i <= n; i++)
        if (i != fin)
            add(i);
    need = -v[1].second;

    for (i = 2; i <= n; i++) {
        if (i == fin) continue;

        int wh = lower_bound(v + 1, v + n + 1, mp(need, -(1 << 30))) - v;
        if (wh > n) return BAD;

        int id = worst(inv(wh));
        if (id == -1) return BAD;

        need = -v[id].second;
        rm(id);
    }

    if (need > v[fin].first) return BAD;

    return 0;
}

// -------------------------------------------- //
#define inf (1LL << 60)
ll dp[1 << 17][20];

ll mv(int a, int b) {
    return max(0, -v[a + 1].second - v[b + 1].first);
}

ll brute_force() {
    int i, j, conf;
    ll ans = inf;

    int st = (1 << n);
    for (i = 0; i < st; i++)
        for (j = 0; j < n; j++)
            dp[i][j] = inf;

    for (conf = 1; conf < st; conf++) {
        for (i = 0; i < n; i++) {
            if ( ((conf >> i) & 1) == 0) continue;

            if (conf == (1 << i))
                dp[conf][i] = 0;

            for (j = 0; j < n; j++) {
                if ( ((conf >> j) & 1) == 1) continue;

                dp[conf | (1 << j)][j] = min(dp[conf | (1 << j)][j], dp[conf][i] + mv(i, j));
            }
        }
    }

    for (i = 0; i < n; i++)
        ans = min(ans, dp[st - 1][i]);

    return ans;
}



#endif
