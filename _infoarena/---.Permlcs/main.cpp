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

#define maxN 1024
#define maxM 12

int n, m, i, j, k, x;
int wh[maxM][maxN];

int gr[maxN];
vector<int> list[maxN];

queue<int> Q;
int longest[maxN];
int ans = 1;

int main()
{
    freopen("permlcs.in","r",stdin);
    freopen("permlcs.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            scanf("%d", &x);
            wh[i][x] = j;
        }
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (i == j) continue;

            bool good = true;

            for (k = 1; k <= m; k++)
                if (wh[k][i] > wh[k][j])
                    good = false;

            if (good) {
                gr[j]++;
                list[i].pb(j);
            }
        }
    }

    for (i = 1; i <= n; i++) {
        if (gr[i]) continue;
        Q.push(i);
        longest[i] = 1;
    }

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();

        for (auto to : list[node]) {
            if (--gr[to] == 0)
                Q.push(to);

            longest[to] = max(longest[to], longest[node] + 1);
        }

        ans = max(ans, longest[node]);
    }

    printf("%d", ans);

    return 0;
}
