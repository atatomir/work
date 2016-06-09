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

#define maxN 2000011
#define inf (1 << 30)
#define T pair<int, int>

struct rmq {
    int n, llog, i, j;
    vector< vector<T> > data;
    vector<int> help;

    void init(int _n, int *from) {
        n = _n;

        for (llog = 0; (1 << llog) <= n; llog++);
        data = vector< vector<T> >(llog + 2, vector<T>(n + 3, mp(0, 0)));
        help.resize(n + 5);

        help[1] = 0;
        for (i = 2; i <= n; i++) {
            help[i] = help[i - 1];
            if (i == 1 << (help[i] + 1)) help[i]++;
        }
        for (i = 1; i <= n; i++) data[0][i] = mp(from[i], i);


        for (i = 1; i < llog; i++) {
            int dim = (1 << i);

            for (j = 1; j + dim - 1 <= n; j++)
                data[i][j] = min(data[i - 1][j], data[i - 1][j + (dim >> 1)]);
        }
    }

    int query(int l, int r) {
        int dim = r - l + 1;
        int act = help[dim];

        return min(data[act][l], data[act][r - (1 << act) + 1]).second;
    }
};

int n, k, i;
int bg, en;

int go[maxN];
rmq work;

bool us[maxN];
vector<int> list[maxN];
vector<int> aux;

int ans = inf;




void dfs(int node) {
    us[node] = true;
    aux.pb(go[node]);

    for (int to : list[node])
        dfs(to);

    if (node - aux[0] + 1 >= n) {
        int cnt = aux.end() - upper_bound(aux.begin(), aux.end(), node - n + 1);
        ans = min(ans, cnt + 1);
    }

    aux.pop_back();
}


int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= 2 * n; i++) go[i] = i + 1;

    for (i = 1; i <= k; i++) {
        scanf("%d%d", &bg, &en);

        if (bg <= en) {
            go[en] = min(go[en], bg);
            go[n + en] = min(go[n + en], n + bg);
        } else {
            go[n + en] =min(go[n + en], bg);
        }
    }

    work.init(2 * n, go);
    for (i = 1; i <= 2 * n; i++) {
        if (go[i] > i) continue;

        int fr = work.query(max(1, go[i] - 1), max(1, i - 1));
        if (go[fr] >= go[i]) continue;

        list[fr].pb(i);
    }

    for (i = 1; i <= 2 * n; i++)
        if (!us[i])
            dfs(i);

    if (ans == inf) {
        printf("impossible");
        return 0;
    }

    printf("%d", ans);

    return 0;
}
