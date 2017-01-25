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

#define maxN 100011
#define mod 1000000007

int n, i, j, cnt;
int to[maxN], in[maxN], gr[maxN];
int h[maxN];
queue<int> Q;
bool us[maxN];
vector<int> ord;
ll ans;

int fr[maxN];
ll dp[maxN][2];

ll combs[maxN];

ll check(int bg) {
    int i;
    int pos[2];
    ll aux;

    pos[0] = h[ord[0]];
    pos[1] = h[ord[0]] + 1;

    for (i = 0; i <= cnt; i++) dp[i][0] = dp[i][1] = 0;
    dp[0][bg] = 1;

    for (i = 1; i < cnt; i++) {
        int node = ord[i];

        if (h[node] == 0) {
            dp[i][0] = dp[i - 1][0];
            dp[i][1] = dp[i - 1][1];
            continue;
        }

        aux = 0;
        if (pos[0] <= i) aux += dp[i - 1][0];
        if (pos[1] <= i) aux += dp[i - 1][1];
        dp[i][0] = aux % mod;

        aux = 0;
        if (pos[0] <= i) aux += dp[i - 1][0];
        if (pos[1] <= i) aux += dp[i - 1][1];
        dp[i][1] = aux % mod;

        pos[0] = i + h[node];
        pos[1] = i + h[node] + 1;
    }

    int allow = cnt;
    ll ans = 0;

    if (pos[0] <= allow) ans += dp[cnt - 1][0];
    if (pos[1] <= allow) ans += dp[cnt - 1][1];

    return ans % mod;
}

void solve() {
    int i, j;
    bool is_free = true;

    reverse(ord.begin(), ord.end());

    cnt = ord.size();
    for (i = 0; i < ord.size(); i++) {
        if (h[ord[i]] == 0) continue;
        is_free = false;

        for (j = 0; j < i; j++) ord.pb(ord[j]);
        for (j = 0; j < cnt; j++) ord[j] = ord[i + j];
        ord.resize(cnt);
        break;
    }

    if (is_free) {
        fr[ord.size()]++;
        return;
    }



    ll local_ans = 0;
    local_ans += check(0);
    local_ans += check(1);
    local_ans %= mod;

    if (cnt == 1 && h[ord[0]] == 1) local_ans = 1;

    ans = (ans * local_ans) % mod;
}

bool doub(int x) {
    return (x % 2 == 1) && (x > 1);
}

void add_comb(ll tp, int nr) {
    combs[1] = ( doub(tp) ? 2 : 1);
    combs[2] = (combs[1] * ( doub(tp) ? 2 : 1)  + tp) % mod;

    for (int i = 3; i <= nr; i++) {
        combs[i] = combs[i - 1] * ( doub(tp) ? 2 : 1) + ((1LL * (i - 1) * combs[i - 2]) % mod) * tp;
        combs[i] %= mod;
    }

    ans = (ans * combs[nr]) % mod;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &to[i]);
        in[ to[i] ]++;
    }

    for (i = 1; i <= n; i++) {
        if (in[i] == 0) {
            h[i] = 0;
            Q.push(i);
        }

        if (in[i] > 2) {
            printf("0");
            return 0;
        }
    }

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();
        us[node] = true;

        if (in[node] >= 2) {
            printf("0");
            return 0;
        }

        h[to[node]] = h[node] + 1;
        if (++gr[to[node]] == in[to[node]])
            Q.push(to[node]);
    }

    ans = 1;
    for (i = 1; i <= n; i++) {
        if (us[i]) continue;

        ord.clear();
        for (int node = i; us[node] == false; us[node] = true, node = to[node])
            ord.pb(node);

        solve();
    }


    for (i = 1; i <= n; i++) {
        if (fr[i] == 0) continue;
        add_comb(i, fr[i]);
    }


    printf("%lld", ans);



    return 0;
}
