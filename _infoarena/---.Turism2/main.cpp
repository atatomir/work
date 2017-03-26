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

struct only_best {
    int a, b, c;

    only_best() {
        a = b = c = 0;
    }

    void operator<<(int x) {
        if (x >= a) {
            c = b;
            b = a;
            a = x;
        } else {
            if (x >= b) {
                c = b;
                b = x;
            } else {
                if (x >= c) {
                    c = x;
                }
            }
        }
    }

    pair<int, int> get_dif(int x) {
        if (a == x) return mp(b, c);
        if (b == x) return mp(a, c);
        return mp(a, b);
    }
};

int n, i, x, y;
int c[maxN];
vector<int> list[maxN];

int down[maxN], up[maxN];
int best_down[maxN], best_up[maxN];
int sol;

void dfs(int node, int root) {
    only_best bst;

    down[node] = best_down[node] = c[node];

    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i];

        if (to == root) {
            list[node][i] = list[node].back();
            list[node].pop_back();
            i--;
            continue;
        }

        dfs(to, node);
        down[node] = max(down[node], c[node] + down[to]);
        best_down[node] = max(best_down[node], best_down[to]);
        bst << down[to];
    }

    best_down[node] = max(best_down[node], bst.a + bst.b + c[node]);
}

void dfs_up(int node) {
    only_best bst, bst_best_up;

    sol = max(sol, best_down[node] + best_up[node]);

    bst << up[node];
    bst_best_up << best_up[node];

    for (auto to : list[node]) {
        bst << down[to];
        bst_best_up << best_down[to];
    }

    for (auto to : list[node]) {
        auto act = bst.get_dif(down[to]);
        auto act_best_up = bst_best_up.get_dif(best_down[to]);

        up[to] = c[node] + act.first;
        best_up[to] = max(act_best_up.first, c[node] + act.first + act.second);
        dfs_up(to);
    }
}

int main()
{
    freopen("turism2.in","r",stdin);
    freopen("turism2.out","w",stdout);

    while(scanf("%d", &n) == 1) {
        for (i = 1; i <= n; i++)
            scanf("%d", &c[i]);
        for (i = 1; i < n; i++) {
            scanf("%d%d", &x, &y);
            list[x].pb(y);
            list[y].pb(x);
        }

        sol = 0;
        dfs(1, 0);
        dfs_up(1);

        printf("%d\n", sol);

        for (i = 1; i <= n; i++) {
            list[i].clear();
            down[i] = up[i] = best_up[i] = best_down[i] = 0;
        }
    }


    return 0;
}
