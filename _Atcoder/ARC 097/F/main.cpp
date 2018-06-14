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

const int maxN = 100011;

int n, i, j, x, y, R, ans, best;
vector<int> list[maxN];
char s[maxN];
int tp[maxN];
bool on[maxN];

int down[maxN][2];

void dfs(int node, int root) {
    if (tp[node] == 0) on[node] = true;
    for (auto to : list[node])
        if (to != root)
            dfs(to, node), on[node] |= on[to];
}

void solve(int node, int root)  {
    down[node][0] = 0;
    down[node][1] = (tp[node] == 0 ? -1 : 1);

    for (auto to : list[node]) {
        if (to == root) continue;
        solve(to, node);
        best = min(best, down[node][0] + down[to][1] - 1);
        best = min(best, down[node][1] + down[to][0] - 1);
        down[node][0] = min(down[node][0], down[to][0] + 
                                           (tp[node] == 0 ? -1 : 1) - 1);
        down[node][1] = min(down[node][1], down[to][1] +
                                           (tp[node] == 0 ? -1 : 1) - 1);
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i < n; i++) {
        scanf("%d%d\n", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    scanf("%s", s + 1);
    for (i = 1; i <= n; i++) 
        tp[i] = (s[i] == 'W' ? 0 : 1);

    for (i = 1; i <= n; i++)
        if (tp[i] == 0) 
            break;

    if (i > n) {
        printf("0");
        return 0;
    }

    R = i;
    dfs(R, 0);

    for (i = 1; i <= n; i++) {
       for (j = 0; j < list[i].size(); j++) {
            if (!on[list[i][j]]) {
                list[i][j] = list[i].back();
                list[i].pop_back();
                j--;
                continue;
            }
        }
    }

    for (i = 1; i <= n; i++) {
        if (!on[i]) continue;
        ans += list[i].size();
        tp[i] = ((tp[i] ^ list[i].size()) & 1);
        if (tp[i] == 0) ans++;
    }

    best = 0;
    solve(R, 0);

    printf("%d", ans + best);


    return 0;
}
