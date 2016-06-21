#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 66
#define inf 5000000

int t, ti;
int n, m, i, j, x, y;
int roy[maxN][maxN];
int dist[maxN][maxN];

map< pair<int, int>, bool > M;
vector< pair< int, pair<int, int> > > use;

bool check() {
    int i, j, k;

    use.clear();
    for (i = 1; i <= n; i++)
        for (j = i + 1; j <= n; j++)
            use.pb(mp(roy[i][j], mp(i, j)));

    sort(use.begin(), use.end());
    for (auto e : use) {
        int n1 = e.second.first;
        int n2 = e.second.second;

        if (M[mp(n1, n2)])
            dist[n1][n2] = dist[n2][n1] = e.first;
    }

    for (k = 1; k <= n; k++)
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                if (i != j && i != k && j != k)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (roy[i][j] != dist[i][j])
                return false;

    return true;
}

int main()
{
    freopen("rfinv.in","r",stdin);
    freopen("rfinv.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%d", &n, &m);
        M.clear();

        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                dist[i][j] = (i == j ? 0 : inf);

        for (i = 1; i <= m; i++) {
            scanf("%d%d", &x, &y);
            M[mp(x, y)] = M[mp(y, x)] = true;
        }

        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                scanf("%d", &roy[i][j]);

        if (check())
            printf("DA\n");
        else
            printf("NU\n");
    }



    return 0;
}
