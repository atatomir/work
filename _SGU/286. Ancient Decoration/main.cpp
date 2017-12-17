#include <iostream>
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

int n, k, m, i, j, x, y;
vector< pair<int, int> > edges;
vector<bool> us;
vector< vector<int> > list;

stack<int> S, S2;
vector<int> ans;

vector< vector<int> > adj;
vector<int> l, r;


void euler_cycle(int ini) {
    int node, i, id, to;
    bool any;

    S.push(ini);
    while (!S.empty()) {
        node = S.top();
        any = false;

        for (i = 0; i < list[node].size(); i++) {
            id = list[node][i];

            if (us[id]) {
                list[node][i] = list[node].back();
                list[node].pop_back();
                i--;
                continue;
            }

            any = true;
            us[id] = true;
            if (edges[id].first != node)
                swap(edges[id].first, edges[id].second);

            S.push(edges[id].second);
            S2.push(id);
            break;
        }

        if (any) continue;
        if (S2.size()) {
            ans.pb(S2.top());
            S2.pop();
        }

        S.pop();
    }

}

bool pairUp(int node) {
    if (us[node]) return false;
    us[node] = true;

    for (auto id : adj[node]) {
        int to = edges[id].second;

        if (r[to] == 0) {
            l[node] = to;
            r[to] = node;
            return true;
        }
    }

    for (auto id : adj[node]) {
        int to = edges[id].second;

        if (pairUp(r[to])) {
            l[node] = to;
            r[to] = node;
            return true;
        }
    }

    return false;
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n >> k;
    list = vector< vector<int> >(n + 11, vector<int>(0));
    for (i = 1, m = n * k / 2; i <= m; i++) {
        cin >> x >> y;
        edges.pb(mp(x, y));
        list[x].pb(i - 1);
        list[y].pb(i - 1);
        us.pb(false);
    }

    adj = vector< vector<int> >(n + 11, vector<int>(0));
    l = r = vector<int>(n + 11, 0);

    for (i = 1; i <= n; i++) {
        ans.clear();

        euler_cycle(i);

        for (auto e : ans) {
            int n1 = edges[e].first;
            int n2 = edges[e].second;
            adj[n1].pb(e);
        }
    }

    bool ok = true;
    while (ok) {
        us = vector<bool>(n + 11, false);
        ok = false;

        for (i = 1; i <= n; i++) {
            if (l[i]) continue;
            ok |= pairUp(i);
        }
    }

    cout << "YES\n";
    for (i = 1; i <= n; i++) {
        for (auto id : adj[i]) {
            int to = edges[id].second;

            if (l[i] == to) {
                cout << id + 1 << '\n';
                break;
            }
        }
    }



    return 0;
}
