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

int n, i, x, y, R;
vector<int> list[maxN];
ll v[maxN];

ll sum[maxN];
ll here[maxN];
ll down[maxN];

ll total;

void no_sol() {
    printf("NO");
    exit(0);
}

void dfs(int node, int root) {
    int i;

    for (i = 0; i < list[node].size(); i++) {
        if (root == list[node][i]) {
            list[node][i] = list[node].back();
            list[node].pop_back();
            i--;
            continue;
        }

        dfs(list[node][i], node);
        down[node] += down[list[node][i]];
        sum[node] += sum[list[node][i]];
    }

    if (list[node].empty()) {
        sum[node] = v[node];
        here[node] = down[node] = 0;
        return;
    }

    ll aux = sum[node] - v[node] - down[node];
    aux *= 2;

    if (aux < 0) no_sol();
    here[node] = aux;
    down[node] += aux;

    total += aux;

    if (here[node] == 0) return;

    vector<int> need = {};
    for (auto to : list[node])
        need.pb(sum[to] - down[to]);

    sort(need.begin(), need.end());
    reverse(need.begin(), need.end());

    if (need.size() == 1) no_sol();
    ll auxi = 0;
    for (int i = 1; i < need.size(); i++)
        auxi += need[i];

    if (here[node] / 2 > auxi) no_sol();
    if (here[node] / 2 > (auxi + need[0]) / 2) no_sol();

}


int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%lld", &v[i]);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    if (n == 2) {
        if (v[1] == v[2])
            printf("YES");
        else
            printf("NO\n");
        return 0;
    }

    for (R = 1; list[R].size() == 1; R++);
    dfs(R, 0);

    if (total != sum[R]) no_sol();

    printf("YES");

    return 0;
}
