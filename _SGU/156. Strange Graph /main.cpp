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
#define pii pair<int, int>

#define maxN 10011

int n, m, i, x, y, j;
vector<int> list[maxN], inp[maxN];
vector< pii > edges;

int cnt;
int belong[maxN];
int small_belong[maxN];
bool great[maxN];
bool us[maxN];

vector<int> ans;
vector<int> sol;

void dfs(int node) {
    us[node] = true;

    for (int i = 0; i < list[node].size(); i++) {
        int e = list[node][i];
        if (edges[e].first == -1) continue;

        int to = edges[e].first;
        if (to == node) to = edges[e].second;
        edges[e].first = -1;

        dfs(to);
    }

    ans.pb(node);
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        inp[x].pb(y);
        inp[y].pb(x);
    }

    for (i = 1; i <= n; i++) {
        if (belong[i]) continue;

        if (inp[i].size() == 2) {
            belong[i] = ++cnt;
            small_belong[cnt] = i;
            great[cnt] = false;
        } else {
            belong[i] = ++cnt;
            great[cnt] = true;

            for (j = 0; j < inp[i].size(); j++)
                if (inp[ inp[i][j] ].size() > 2)
                    belong[ inp[i][j] ] = cnt;
        }
    }

    for (i = 1; i <= n; i++) {
        for (j = 0; j < inp[i].size(); j++) {
            int to = inp[i][j];

            if (belong[i] == belong[to] || i > to) continue;
            edges.pb(mp(belong[i], belong[to]));
            list[ belong[i] ].pb( edges.size() - 1 );
            list[ belong[to] ].pb( edges.size() - 1 );
        }
    }

    if (cnt == 1) {
        for (i = 1; i <= n; i++) printf("%d ", i);
        return 0;
    }

    dfs(1);
    for (i = 1; i <= cnt; i++) {
        if (list[i].size() % 2 == 1 || !us[i]) {
            printf("-1");
            return 0;
        }
    }

    ans.pb(ans[1]);

    for (i = 1; i + 1 < ans.size(); i++) {
        int v = ans[i];
        int real_val = small_belong[v];

        if (great[v]) continue;
        if (great[ ans[i - 1] ]) {
            int id = ans[i - 1];

            if (belong[inp[real_val][0]] == id)
                sol.pb(inp[real_val][0]);
            else
                sol.pb(inp[real_val][1]);
        }

        sol.pb(real_val);

        if (great[ ans[i + 1] ]) {
            int id = ans[i + 1];

            if (belong[inp[real_val][0]] == id)
                sol.pb(inp[real_val][0]);
            else
                sol.pb(inp[real_val][1]);
        }
    }

    for (i = 0; i < sol.size(); i++)
        printf("%d ", sol[i]);


    return 0;
}
