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

#define maxN 100011

int n, i, x, y, cnt, limit;
vector<int> list[maxN];
int dp[maxN];
bool bad;
vector<int> aux;

bool good(int deny) {
    int p1, p2;

    p1 = 0; p2 = aux.size() - 1;
    while (p1 < p2) {
        if (deny == p1) {
            p1++; continue;
        }
        if (deny == p2) {
            p2--; continue;
        }

        if (aux[p1] + aux[p2] > limit) return false;
        p1++; p2--;
    }

    return true;
}

void dfs(int node, int root) {
    for (auto to : list[node])
        if (to != root && bad == false)
            dfs(to, node);

    if (bad) return;

    aux.clear();

    for (auto to : list[node])
        if (to != root)
            aux.pb(dp[to] + 1);

    if (node != 1 && aux.size() % 2 == 0) aux.pb(0), cnt++;
    sort(aux.begin(), aux.end());
    cnt -= aux.size() / 2;

    if (aux.size() % 2 == 0) {
        if (!good(-1)) bad = true;
        return;
    }

    int ans = -1;
    for (int step = 1 << 20; step > 0; step >>= 1)
        if (ans + step < aux.size())
            if (!good(ans + step))
                ans += step;

    ans++;
    if (ans == aux.size()) {
        bad = true;
        return;
    }

    dp[node] = aux[ans];
    if (dp[node] > limit) bad = true;
}

bool check(int _limit) {
    cnt = 0;
    limit = _limit;
    bad = false;
    dfs(1, 0);
    if (bad) return false;
    return true;
}

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i < n; i++) {
        cin >> x >> y;
        list[x].pb(y);
        list[y].pb(x);
    }

    int ans = 0;
    for (int step = 1 << 20; step > 0; step >>= 1)
        if (ans + step < n)
            if (!check(ans + step))
                ans += step;

    //cerr << check(1);

    check(ans + 1);
    cout << cnt << ' ' << ans + 1;


    return 0;
}
