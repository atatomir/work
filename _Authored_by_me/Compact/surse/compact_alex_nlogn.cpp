#include <iostream>
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

pair<int, vector<int> > solve_quadratic(int n, int m, vector<int> v) {
    vector<int> min_pos, max_pos, cnt;
    vector<int> dp, from, keep_high;
    vector<int> sol = {};

    min_pos = vector<int>(m + 1, n + 1);
    max_pos = vector<int>(m + 1, -1);
    cnt = vector<int>(m + 1, 0);
    dp = vector<int>(m + 1, -n);
    from = vector<int>(m + 1, -1);
    keep_high = vector<int>(m + 1, -1);

    for (int i = 0; i < n; i++) {
        min_pos[v[i]] = min(min_pos[v[i]], i);
        max_pos[v[i]] = max(max_pos[v[i]], i);
        cnt[v[i]]++;
    }

    dp[0] = 0;
    for (int i = 0; i < m; i++) {
        int low = n + 1;
        int high = -1;
        int count = 0;

        for (int j = i + 1; j <= m; j++) {
            low = min(low, min_pos[j]);
            high = max(high, max_pos[j]);
            count += cnt[j];

            if (high - low + 1 == count) {
                if (dp[j] < dp[i] + 1) {
                    dp[j] = dp[i] + 1;
                    from[j] = i;
                    keep_high[j] = high;
                }
            }
        }
    }

    for (int i = m; i != 0; i = from[i])
        sol.pb(keep_high[i] + 1);

    sort(sol.begin(), sol.end());

    return mp(sol.size(), sol);
}

struct rmq {
    vector<vector<int>> data = {};
    vector<int> help = {};

    void init(vector<int> init) {
        int n = init.size();

        help = {0, 0};
        for (int i = 2; i <= n; i++)
            help.pb(help[i / 2] + 1);

        data.pb(init);
        for (int i = 1; i <= help[n]; i++) {
            int sz = 1 << i;
            data.pb({});
            for (int j = 0; j + sz - 1 < n; j++)
                data[i].pb(min(data[i - 1][j], data[i - 1][j + (sz >> 1)]));
        }
    }

    int query(int l, int r) {
        int sz = help[r - l + 1];
        return min(data[sz][l], data[sz][r - (1 << sz) + 1]);
    }
};

struct group {
    int pos_l, pos_r;
    int val_min, val_max;
};

pair<int, vector<int> > solve_linlog(int n, int m, vector<int> v) {
    vector<int> min_pos, max_pos, cnt;
    int low, high, l, r, go_right;
    stack<group> S; 
    rmq before;
    vector<int> sol = {};

    v.insert(v.begin(), 0);

    min_pos = vector<int>(m + 1, n + 1);
    max_pos = vector<int>(m + 1, -1);
    cnt = vector<int>(m + 1, 0);

    for (int i = 1; i <= n; i++) {
        min_pos[v[i]] = min(min_pos[v[i]], i);
        max_pos[v[i]] = max(max_pos[v[i]], i);
        cnt[v[i]]++;
    }

    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    before.init(min_pos);
    S.push({0, 0, 0, 0});

    while (S.top().pos_r != n) {
        l = r = S.top().pos_r + 1;
        low = high = v[l];
        go_right = max_pos[v[l]];
    
    

        while (true) {
            // go right if needed
            while (r < go_right) {
                r++;
                low = min(low, v[r]);
                high = max(high, v[r]);
                go_right = max(go_right, max_pos[v[r]]);
            }  
            
            // go left if needed
            int go_left = before.query(low, high);
            if (go_left < l) {
                while (S.top().pos_l > go_left) {
                    low = min(low, S.top().val_min);
                    high = max(high, S.top().val_max);
                    // go_right unchanged
                    
                    l = S.top().pos_l;
                    S.pop();
                }

                low = min(low, S.top().val_min);
                high = max(high, S.top().val_max);
                l = S.top().pos_l;
                S.pop();
                continue;
            }

            if (cnt[high] - cnt[low - 1] == r - l + 1) break;
            r++;
            low = min(low, v[r]);
            high = max(high, v[r]);
            go_right = max(go_right, max_pos[v[r]]);
        }
        S.push({l, r, low, high});
    }

    while (!S.empty()) {
        sol.pb(S.top().pos_r);
        S.pop();
    }
    sol.pop_back();
    reverse(sol.begin(), sol.end());

    return mp(sol.size(), sol);
}

const int maxN = 1000011;

int t, n, m;
vector<int> a;

int main()
{
    freopen("compact.in", "r", stdin);
    freopen("compact.out", "w", stdout);

    //scanf("%d", &t);
    t = 1;
    for (int ti = 1; ti <= t; ti++) {
        scanf("%d%d", &n, &m);
        a.resize(n);
        for (auto& e: a) scanf("%d", &e);
        
        //auto ans = solve_quadratic(n, m, a);
        auto ans = solve_linlog(n, m, a);

        printf("%d\n", ans.first);
        for (auto e : ans.second)
            printf("%d ", e);
        printf("\n");
    }


    return 0;
}
