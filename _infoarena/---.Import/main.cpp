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

#define maxN 256

int n, k, m, i;
int a, b, c, d;

vector<int> tree[maxN];
vector< pair<int, int> > list[maxN];

queue<int> Q;
bool inQueue[maxN];
int ans[maxN];
bool used[maxN];
int ans_tree[maxN];

void Bellman() {
    int i;

    for (i = 1; i <= n; i++) {
        inQueue[i] = true;
        ans[i] = 0;
        Q.push(i);
    }

    while (!Q.empty()) {
        int node = Q.front();
        Q.pop();
        inQueue[node] = false;

        for (auto to : list[node]) {
            if (ans[to.first] > ans[node] + to.second) {
                ans[to.first] = ans[node] + to.second;
                if (!inQueue[to.first]) {
                    inQueue[to.first] = true;
                    Q.push(to.first);
                }
            }
        }
    }
}

void dfs(int node) {
    used[node] = true;

    for (auto to : tree[node]) {
        if (used[to])
            continue;

        if (to > k && node == 1)
            ans_tree[to] = ans[to];
        else
            ans_tree[to] = ans[to] - ans[node];
        dfs(to);
    }
}

int main()
{
    freopen("import.in","r",stdin);
    freopen("import.out","w",stdout);

    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &a, &b);

        tree[a].pb(b);
        tree[b].pb(a);
    }

    for (i = 1; i <= m; i++) {
        scanf("%d%d%d%d", &a, &b, &c, &d);

        if (d == 0)
            list[a].pb(mp(b, -c));
        else
            list[b].pb(mp(a, c - 1));
    }

    Bellman();
    for (i = 1; i <= k; i++)
        ans[i] *= -1;

    ans_tree[1] = ans[1];
    dfs(1);

    for (i = 1; i <= n; i++)
        printf("%d ", ans_tree[i]);

    return 0;
}
