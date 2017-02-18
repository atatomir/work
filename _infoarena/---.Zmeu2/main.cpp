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
#define ll long long

#define maxN 211
#define maxK 511
#define inf (1 << 14)
#define form(a, b) ((a << 8) | b)
#define getk(a) (a >> 8)
#define getn(a) (a & 255)

short dp[maxK][maxN];

struct cmp {

    bool operator()(const short a, const short b) {
        return dp[getk(a)][getn(a)] > dp[getk(b)][getn(b)];
    }

};

int k, n, m, i, j, x, y;
int d[maxN], c[maxN];

bool adj[maxN][maxN];

priority_queue< short, vector< short >, cmp > H;

int main()
{
    freopen("zmeu2.in","r",stdin);
    freopen("zmeu2.out","w",stdout);

    scanf("%d%d%d", &k, &n, &m);
    for (i = 1; i <= n; i++)
        scanf("%d%d", &d[i], &c[i]);

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) adj[i][j] = true;
        adj[i][i] = false;
    }

    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        adj[x][y] = false;
    }

    for (i = 0; i <= k; i++)
        for (j = 1; j <= n; j++)
            dp[i][j] = inf;

    dp[c[1]][1] = d[1];
    H.push(form(c[1], 1));

    int best = inf;

    while (!H.empty()) {
        int node = getn(H.top());
        int cap = getk(H.top());

        H.pop();


        if (adj[node][n] && node != 1) {
            if (cap + c[n] < k) {
                best = min(best, dp[cap][node] + d[n]);
                printf("%d", best);
                return 0;
            }
        }

        for (i = 1; i <= n; i++) {
            if (adj[node][i] == false) continue;
            if (cap + c[i] >= k) continue;
            if (dp[cap][node] + d[i] < dp[cap + c[i]][i]) {
                dp[cap + c[i]][i] = dp[cap][node] + d[i];
                H.push(form(cap + c[i], i));
            }
        }
    }

    if (best >= inf)
        printf("-1");
    else
        printf("%d", best);




    return 0;
}
