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

#define maxN 5011
#define mod 1000000007

int n, i, x, y;
int down[maxN];
vector<int> list[maxN], aux;

ll ans;
ll dp[maxN], loc[maxN], rez[maxN];

void compute_loc(int cnt) {
    int i, j;

    for (i = 0; i <= cnt; i++) loc[i] = 0;
    loc[0] = 1;

    for (i = 1; i <= cnt; i++) {
        for (j = i; j > 0; j--) {
            loc[j] += loc[j - 1] * (cnt - j + 1);
            loc[j] %= mod;
        }
    }
}

void solve() {
    int i, j, cnt;

    dp[0] = 1;
    for (auto v : aux) {
        cnt = v;

        compute_loc(cnt);
        for (i = 0; i <= n; i++) {
            rez[i] = dp[i];
            dp[i] = 0;
        }

        for (i = 0; i <= n; i++) {
            for (j = 0; j <= cnt && j <= i; j++) {
                dp[i] += rez[i - j] * loc[j];
                dp[i] %= mod;
            }
        }
    }

    for (i = 0; i <= n; i++) {
        for (j = 1; i + j <= n; j++)
            dp[i] = (dp[i] * j) % mod;

        if (i % 2 == 1) dp[i] = mod - dp[i];
        ans += dp[i];
    }

    ans %= mod;
    cout << ans;
}

void dfs(int node, int root) {
    bool ok = true;
    down[node] = 1;
    for (auto to : list[node]) {
        if (to == root) continue;
        dfs(to, node);
        down[node] += down[to];
        if (down[to] > n / 2) ok = false;
    }

    if (n - down[node] > n / 2) ok = false;

    if (ok) {
        if (down[node] * 2 == n) {
            ans = 1;
            for (i = 1; i <= down[node]; i++)
                ans = (ans * i) % mod;
            ans = (ans * ans) % mod;
            cout << ans;
            exit(0);
        } else {
            for (auto to : list[node])
                if (to != root)
                    aux.pb(down[to]);
            aux.pb(0);
            if (down[node] != n) aux.pb(n - down[node]);
            solve();
            exit(0);
        }
    }
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i < n; i++) {
        cin >> x >> y;
        list[x].pb(y);
        list[y].pb(x);
    }

    dfs(1, 0);


    return 0;
}
