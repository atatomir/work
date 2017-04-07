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
#define maxD 12

int n, m, i, q, x, y, v, d, c;
vector<int> list[maxN];
int col[maxN];
int id[maxD][maxN];
int last[maxN];




int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    scanf("%d", &q);
    for (i = 1; i <= q; i++) {
        scanf("%d%d%d", &v, &d, &c);
        col[i] = c;
        id[d][v] = i;
    }

    for (int lvl = 10; lvl > 0; lvl--) {
        for (int node = 1; node <= n; node++) {
            last[node] = max(last[node], id[lvl][node]);

            for (auto to : list[node])
                id[lvl - 1][to] = max(id[lvl - 1][to], id[lvl][node]);
        }
    }

    for (i = 1; i <= n; i++) last[i] = max(id[0][i], last[i]);
    for (i = 1; i <= n; i++)
        printf("%d\n", col[last[i]]);




    return 0;
}
