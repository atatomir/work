#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int maxN = 100011;

int n, i, cnt, n1, n2;
string a, b;
map<string, int> M;
int go[maxN];
vector<int> list[maxN];
bool us[maxN], paired[maxN];
bool on_cyc[maxN];

vector<int> nodes;
int saved;

void find_cyc(int node) {
    us[node] = true;
    nodes.pb(node);

    if (us[go[node]]) {
        reverse(nodes.begin(), nodes.end());
        while (nodes.back() != go[node]) nodes.pop_back();
        return;
    } else {
        find_cyc(go[node]);
    }
}

void dfs(int node, int root) {
    us[node] = true;

    for (auto to : list[node]) {
        if (on_cyc[to]) continue;
        if (to == root) continue;

        dfs(to, node);
        if (!paired[node] && !paired[to]) {
            paired[node] = paired[to] = true;
            saved++;
        }
    }
}

void solve(int node) {
    int i, cnt, pos;

    nodes.clear();
    find_cyc(node);

    for (auto e : nodes) on_cyc[e] = true;
    for (auto e : nodes)
        dfs(e, 0);

    if (nodes.size() <= 2) {
        if (nodes.size() == 1) {
            return;
        } else {
            saved += 2 - paired[nodes[0]] - paired[nodes[1]];
        }
    } else {
        for (i = 0; i < nodes.size(); i++)
            if (paired[nodes[i]])
                    break;

        pos = (i < nodes.size() ? i : 0);
        cnt = nodes.size();
        for (i = 0; i < cnt; i++) nodes.pb(nodes[i]);
        for (i = pos + 1; i <= pos + cnt - 1; i++) {
            if (!paired[nodes[i]] && !paired[nodes[i - 1]]) {
                paired[nodes[i]] = paired[nodes[i - 1]] = true;
                saved++;
            }
        }
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n;

    if (n & 1) {
        printf("-1");
        return 0;
    }

    for (i = 1; i <= n; i++) {
        cin >> a >> b;
        if (M[a] == 0) M[a] = ++cnt;
        if (M[b] == 0) M[b] = ++cnt;

        go[M[a]] = M[b];
        list[M[a]].pb(M[b]);
        list[M[b]].pb(M[a]);
    }

    for (i = 1; i <= n; i++) {
        if (us[i]) continue;
        solve(i);
    }

    int ans = (n - saved);
    printf("%d", ans);


    return 0;
}
