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

#define maxN 1024
#define inf 1000000
#define edge_size 1

int n, k, i, x, y;
vector<int> list[maxN];

bool us[maxN];
int max_up[maxN]; //! how much i can go up
int min_down[maxN]; //! nearest hospital
vector<int> sol;

int act_dist;

void dfs(int node) {
    us[node] = true;

    max_up[node] = act_dist;
    min_down[node] = inf;

    for (int i = 0; i < list[node].size(); i++) {
        if (us[list[node][i]]) {
            //! clean..
            list[node][i] = list[node][ list[node].size() - 1 ];
            list[node].pop_back();
            i--;
            continue;
        }

        int to = list[node][i];
        dfs(to);
        max_up[node] = min(max_up[node], max_up[to] - 1);
        min_down[node] = min(min_down[node], min_down[to] + 1);
    }

    if (min_down[node] <= max_up[node]) {
        //! can satisfy with actual hospitals
        max_up[node] = inf;
        return;
    }

    if (max_up[node] < edge_size) {
        //! must set a new hospital
        sol.pb(node);
        max_up[node] = inf;
        min_down[node] = 0;
        return;
    }

    //! simply go up

    return;
}

bool check(int dist) {
    memset(us, 0, sizeof(us));
    memset(max_up, 0, sizeof(max_up));
    memset(min_down, 0, sizeof(min_down));
    sol.clear();
    act_dist = dist;

    dfs(1);
    if (max_up[1] < inf) sol.pb(1);

    return sol.size() <= k;
}


int main()
{
    freopen("salvare.in","r",stdin);
    freopen("salvare.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    int ans = -1;
    for (int step = 1 << 10; step; step >>= 1)
        if (!check(ans + step))
            ans += step;

    printf("%d\n", ans + 1);
    check(ans + 1);

    memset(us, 0, sizeof(us));
    for (int e : sol)
        us[e] = true, k--;

    for (i = 1; i <= n && k; i++)
        if (!us[i])
            sol.pb(i), k--;

    sort(sol.begin(), sol.end());
    for (int e : sol)
        printf("%d ", e);


    return 0;
}
