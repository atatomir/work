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

const int maxN = 2018;

int t, ti;
int n, k, i, a[maxN], b[maxN];
vector<int> pre, post;
vector<int> list[maxN];
bool us[maxN];
int ans[maxN], cnt;

void dfs_pre(int node) {
    pre.pb(node);
    if (a[node]) dfs_pre(a[node]);
    if (b[node]) dfs_pre(b[node]);
}

void dfs_post(int node) {
    if (a[node]) dfs_post(a[node]);
    if (b[node]) dfs_post(b[node]);
    post.pb(node);
}

void dfs(int node) {
    us[node] = true;
    ans[node] = cnt;

    for (auto to : list[node])
        if (!us[to])
            dfs(to);
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out", "w", stdout);

    scanf("%d", &t);
    cerr << "Solve " << t << " tests\n";

    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << '\n';

        scanf("%d%d", &n, &k);
        for (i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]);

        pre = post = {};
        dfs_pre(1);
        dfs_post(1);

        for (i = 1; i <= n; i++) {
            list[i].clear();
            us[i] = false;
        }

        for (i = 0; i < n; i++) {
            list[pre[i]].pb(post[i]);
            list[post[i]].pb(pre[i]);
        }

        cnt = 0;
        for (i = 1; i <= n; i++) {
            if (us[i]) continue;
            cnt = min(k, cnt + 1);
            dfs(i);
        }

        if (cnt < k) {
            printf("Case #%d: Impossible\n", ti);
            continue;
        }

        printf("Case #%d: ", ti);
        for (i = 1; i <= n; i++) printf("%d ", ans[i]);
        printf("\n");
    }


    return 0;
}
