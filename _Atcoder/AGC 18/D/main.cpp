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

int n, i, R, vv;
ll A, B, C;
vector< pair<int, ll> > list[maxN];
int cnt[maxN];
ll ans;
ll mini = 1LL << 60;

int dfs(int node, int root) {
    bool ok = true;
    cnt[node] = 1;

    for (auto to : list[node]) {
        if (to.first == root) continue;
        int ans = dfs(to.first, node);
        if (ans != 0) return ans;

        cnt[node] += cnt[to.first];
        ok &= (cnt[to.first] <= n / 2);
    }

    ok &= (n - cnt[node] <= n / 2);
    if (ok && cnt[node] == n / 2) vv = root;

    if (ok) return node;
    return 0;
}

void dfs2(int node, int root, ll depth) {
    ans += 2LL * depth;
    for (auto to : list[node]) {
        if (to.first == root) continue;
        dfs2(to.first, node, depth + to.second);
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i < n; i++) {
        cin >> A >> B >> C;
        list[A].pb(mp(B, C));
        list[B].pb(mp(A, C));
    }

    R = dfs(1, 0);
    dfs2(R, 0, 0);

    for (auto to : list[R])
        mini = min(mini, to.second);

    if (vv != 0) {
        for (auto to : list[vv])
            if (to.first == R)
                mini = to.second;
    }

    cout << ans - mini;


    return 0;
}
