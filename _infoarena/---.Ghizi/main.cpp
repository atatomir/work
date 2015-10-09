#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 5011
#define maxT 111

int n, k, i, j, x, y, S, D;
vector<int> list[maxT];
int cap[maxT][maxT];
int flux[maxT][maxT];
vector<int> ids[maxT][maxT];

int prov[maxT];
bool us[maxT];
queue<int> Q;

vector<int> ans;

void Flow() {
    memset(us, 0, sizeof(us));
    while (!Q.empty()) Q.pop();

    prov[S] = 0; us[S] = true;
    Q.push(S);

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();
        if (node == D) continue;

        for (auto go : list[node]) {
            if (us[go] || cap[node][go] == flux[node][go]) continue;

            prov[go] = node;
            us[go] = true;
            Q.push(go);
        }
    }

    for (auto neigh : list[D]) {
        if (!us[neigh]) continue;

        int flow = k;

        prov[D] = neigh;
        for (int node = D; node != S; node = prov[node])
            flow = min(flow, cap[prov[node]][node] - flux[prov[node]][node]);
        for (int node = D; node != S; node = prov[node]) {
            flux[prov[node]][node] += flow;
            flux[node][prov[node]] -= flow;
        }

        k -= flow;
    }
}

int main()
{
    freopen("ghizi.in","r",stdin);
    freopen("ghizi.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &x, &y);

        list[x].pb(y);
        list[y].pb(x);
        ids[x][y].pb(i);

        cap[x][y]++;
    }

    S = 0; D = 100;

    while (k > 0)
        Flow();

    for (i = 0; i <= 100; i++)
        for (j = i + 1; j <= 100; j++)
            for (k = 0; k < flux[i][j]; k++) ans.pb( ids[i][j][k] );

    sort(ans.begin(), ans.end());
    printf("%d\n", ans.size());
    for (auto who : ans) printf("%d ", who);


    return 0;
}
