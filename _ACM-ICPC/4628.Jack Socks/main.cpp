#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>
#include <functional>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 1011
#define maxM 10011

int t, ti;
int n, m, i, x, y;

vector< pair<int, int> > list[maxN];
pair<int, int> edges[maxM];
bool dead_edge[maxM];
int cnt_edges;

int low[maxN], lvl[maxN];
stack<int> S;

bool critic[maxN];
vector<int> nodes;

int comp_cnt;
int used_id[maxN];

vector< pair<int, int> > solution;
bool error;
bool coupled[maxN];

void kill_edges(int node, function<bool(int)> to_kill) {
    for (auto e : list[node]) {
        if (dead_edge[e.second]) continue;

        if (to_kill(e.first)) {
            dead_edge[e.second] = true;
            cnt_edges--;
        }
    }
}

void get_new_component(int id, int cr_node) {
    int last = -1;
    int crt = 0;

    comp_cnt++;
    nodes.clear();

    while (last != id) {
        // get nodes of the biconnected component
        last = S.top(); S.pop();

        if (used_id[edges[last].first] != comp_cnt)
            nodes.pb(edges[last].first);
        if (used_id[edges[last].second] != comp_cnt)
        nodes.pb(edges[last].second);

        used_id[edges[last].first] = used_id[edges[last].second] = comp_cnt;
    }

    for (auto e : nodes)
        if (critic[e])
            crt++;

    if (crt != 1) return;

    if (nodes.size() == 2) {
        // edge
        solution.pb(mp(nodes[0], nodes[1]));
        coupled[nodes[0]] = coupled[nodes[1]] = true;
        dead_edge[id] = true;
        cnt_edges--;

        kill_edges(cr_node, [](int node)->bool {
            return used_id[node] != comp_cnt;
        });

        return;
    }

    if (nodes.size() % 2 == 0) {
        error = true;
        return;
    }

    kill_edges(cr_node, [](int node)->bool {
        return used_id[node] == comp_cnt;
    });
}

void dfs(int node) {
    low[node] = lvl[node];

    for (int i = 0; i < list[node].size(); i++) {
        auto to = list[node][i];

        // cut edges
        if (dead_edge[to.second]) {
            list[node][i] = list[node].back();
            list[node].pop_back();
            i--; continue;
        }

        // continue dfs
        if (lvl[to.first] == 0) {
            lvl[to.first] = lvl[node] + 1;
            S.push(to.second);
            dfs(to.first);
            low[node] = min(low[node], low[to.first]);
        } else {
            if (lvl[to.first] >= lvl[node] - 1) continue;
            low[node] = min(low[node], lvl[to.first]);
            S.push(to.second);
            continue;
        }

        if (low[to.first] < lvl[node]) continue;
        // new biconnected component
        critic[node] = true;
        get_new_component(to.second, node);
    }
}

vector< pair<int, int> >& solve() {
    int i;
    cnt_edges = m;

    solution.clear();
    error = false;

    while (cnt_edges > 0 && error == false) {
        memset(low, 0, sizeof(low));
        memset(lvl, 0, sizeof(lvl));
        memset(critic, 0, sizeof(critic));

        for (i = 1; i <= n; i++) {
            if (lvl[i]) continue;

            lvl[i] = 1;
            dfs(i);
        }
    }

    for (i = 1; i <= n; i++)
        if (!coupled[i])
            error = true;

    if (error == true)
        solution.clear();

    return solution;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%d", &n, &m);

        for (i = 1; i <= n; i++) list[i].clear();
        memset(dead_edge, 0, sizeof(dead_edge));
        memset(coupled, 0, sizeof(coupled));

        for (i = 1; i <= m; i++) {
            scanf("%d%d", &x, &y);
            list[x].pb(mp(y, i));
            list[y].pb(mp(x, i));
            edges[i] = mp(x, y);
        }

        auto ans = solve();
        for (i = 0; i < ans.size(); i++)
            if (ans[i].first > ans[i].second)
                swap(ans[i].first, ans[i].second);
        sort(ans.begin(), ans.end());

        if (ans.empty()) {
            printf("NO\n");
        } else {
            printf("YES\n");
            for (auto e : ans)
                printf("%d %d\n", e.first, e.second);
        }
    }


    return 0;
}
