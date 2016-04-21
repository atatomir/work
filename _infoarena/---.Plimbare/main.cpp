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

#define maxN 111

int n, i, j, x, y, m;
bool adj[maxN][maxN];
bool rev[maxN][maxN];
stack<int> S;
vector<int> act;

bool us[maxN];
vector<int> path;



void dfs_to(int node) {
    us[node] = true;
    for (int i = 1; i <= n; i++)
        if (adj[node][i] && !us[i])
            dfs_to(i);
    S.push(node);
}

void dfs_from(int node) {
    us[node] = true;
    for (int i = 1; i <= n; i++)
        if (rev[node][i] && !us[i])
            dfs_from(i);
    act.pb(node);
}

bool find_three() {
    path.clear();
    sort(act.begin(), act.end());
    for (int p1 : act) {
        for (int p2 : act) {
            if (p1 == p2 || adj[p1][p2] == 0) continue;
            for (int p3 : act) {
                if (p1 == p3 || p2 == p3) continue;
                if (adj[p1][p2] && adj[p2][p3]) {
                    path = {p1, p2, p3};
                    return true;
                }
            }
        }
    }

    return false;
}

bool get_new_path() {
    int i, j, k;

    if(!find_three()) return false;
    memset(us, 0, sizeof(us));
    for (int e : path) us[e] = true;

    for (i = 0; i < act.size(); i++) {
        if (!us[act[i]]) continue;
        act[i] = act.back();
        act.pop_back();
        i--; continue;
    }

    path.pb(path[0]);
    while (!act.empty()) {
        bool found = false;
        for (i = 0; i < act.size() && !found; i++) {
            int node = act[i];

            for (j = 1; j < path.size(); j++) {
                if (adj[path[j - 1]][node] && adj[node][path[j]]) {
                    found = true;
                    us[node] = true;

                    for (k = path.size() - 1; k > j; k--) path[k] = path[k - 1];
                    path[j] = node;

                    act[i] = act.back();
                    act.pop_back();

                    break;
                }
            }
        }

        if (!found) {
            path.pop_back();

            //! find two nodes to add to the cycle
            int node = -1, node2 = -1;
            for (i = 0; i < act.size(); i++) {
                node = act[i];
                if (adj[path.back()][node] == 0) continue;

                us[node] = true;
                act[i] = act.back(); act.pop_back();
                path.pb(node);

                break;
            }

            for (i = 0; i < act.size(); i++) {
                node2 = act[i];
                if (adj[node2][path[0]] == 0) continue;
                if (adj[node][node2] == 0) continue;

                us[node2] = true;
                act[i] = act.back(); act.pop_back();
                path.pb(node2);

                break;
            }
        }

        path.pb(path[0]);
    }

    path.pop_back();
    return true;
}


int main()
{
    freopen("plimbare.in","r",stdin);
    freopen("plimbare.out","w",stdout);

    scanf("%d", &n); m = (n * (n - 1)) / 2;
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        adj[x][y] = rev[y][x] = true;
    }

    for (i = 1; i <= n; i++)
        if (!us[i])
            dfs_to(i);

    path = {1};

    memset(us, 0, sizeof(us));
    while (!S.empty()) {
        int node = S.top(); S.pop();
        if (us[node]) continue;

        act.clear();
        dfs_from(node);

        if (act.size() > path.size() && act.size() >= 3)
            if (!get_new_path())
                cerr << "Error!";
    }

    printf("%d\n", path.size());
    for (int e : path) printf("%d ", e);

    /*printf("\n");
    for (i = 1; i < n; i++)
        for (j = i + 1; j <= n; j++)
            printf("%d %d\n", i, j);*/

    return 0;
}
