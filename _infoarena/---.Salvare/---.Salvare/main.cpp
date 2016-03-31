#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1024

int n, i, k, x, y;
vector<int> list[maxN];
bool us[maxN];
int lvl[maxN];
int dad[maxN];
vector<int> nodes;
int last_used[maxN];
int fill_id;
vector<int> ans_nodes;

void dfs(int node) {
    us[node] = true;

    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i];

        if (us[to]) continue;

        lvl[to] = lvl[node] + 1;
        dad[to] = node;
        dfs(to);
    }
}

bool cmp(int a, int b) {
    return lvl[a] > lvl[b];
}

void dfs_solve(int node, int dist) {
    last_used[node] = fill_id;
    if (dist == 0) return;

    for (auto to : list[node]) {
        if (last_used[to] != fill_id)
            dfs_solve(to, dist - 1);
    }
}

int get_count(int dist) {
    int ans = 0;
    memset(last_used, 0, sizeof(last_used));
    ans_nodes.clear();

    for (auto act : nodes) {
        if (last_used[act]) continue;

        int daddy = act;
        for (int how = dist; how > 0 && daddy != 1; how--)
            daddy = dad[daddy];

        ans++;
        fill_id = ans + 1;
        dfs_solve(daddy, dist);
        ans_nodes.pb(daddy);
    }

    return ans;
}

void add_unuseful_nodes() {
    int i;

    memset(us, 0, sizeof(us));
    for (auto who : ans_nodes)
        us[who] = true;

    int how = k - ans_nodes.size();
    for (i = 1; how > 0; i++) {
        if (us[i]) continue;
        how--;
        ans_nodes.pb(i);
    }
}

int main()
{
    freopen("salvare.in","r",stdin);
    freopen("salvare.ok","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    dfs(1);
    for (i = 1; i <= n; i++)
        nodes.pb(i);
    sort(nodes.begin(), nodes.end(), cmp);

    int ans = -1;
    for (int step = 1 << 10; step; step >>= 1) {
        if (get_count(ans + step) > k)
            ans += step;
    }

    get_count(ans + 1);
    add_unuseful_nodes();
    sort(ans_nodes.begin(), ans_nodes.end());

    printf("%d\n", ans + 1);
    for (auto who : ans_nodes)
        printf("%d ", who);

    return 0;
}
