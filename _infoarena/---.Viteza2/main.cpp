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
#define inf 1000000011

struct edge {
    int x, y, c;

    bool operator<(const edge& who)const {
        return c < who.c;
    }
};

int n, m, i, j, x, y, z;
vector<edge> E;
int dist[maxN][maxN];

int main()
{
    freopen("viteza2.in","r",stdin);
    freopen("viteza2.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        E.pb({x, y, z});
    }

    sort(E.begin(), E.end());
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            dist[i][j] = (i == j ? 0 : inf);

    for (auto e : E) {
        for (i = 1; i <= n; i++) {
            dist[i][e.y] = min(dist[i][e.y], dist[i][e.x] + e.c);
            dist[i][e.x] = min(dist[i][e.x], dist[i][e.y] + e.c);
        }
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++)
            printf("%d ", (dist[i][j] >= inf ? -1 : dist[i][j]));
        printf("\n");
    }



    return 0;
}
