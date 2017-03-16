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

int n, i, j;
int m[maxN][maxN];
vector< pair<int, int> > pos[maxN * maxN];
int sum[maxN][maxN];

bool bad[maxN * maxN];
int dif;

int main()
{
    freopen("art.in","r",stdin);
    freopen("art.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            scanf("%d", &m[i][j]);
            pos[m[i][j]].pb(mp(i, j));
        }
    }

    int xx1, xx2, yy1, yy2, xx, yy;

    for (int col = 1; col <= n * n; col++) {
        if (pos[col].empty()) continue;
        dif++;

        xx1 = yy1 = n + 13;
        xx2 = yy2 = -1;

        for (auto e : pos[col]) {
            xx1 = min(xx1, e.first);
            xx2 = max(xx2, e.first);

            yy1 = min(yy1, e.second);
            yy2 = max(yy2, e.second);

            xx = e.first;
            yy = e.second;
            sum[xx][yy]--;
            sum[xx + 1][yy]++;
            sum[xx][yy + 1]++;
            sum[xx + 1][yy + 1]--;
        }

        sum[xx1][yy1]++;
        sum[xx1][yy2 + 1]--;
        sum[xx2 + 1][yy1]--;
        sum[xx2 + 1][yy2 + 1]++;
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
            if (sum[i][j] != 0)
                bad[m[i][j]] = true;
        }
    }

    int cnt = 0;
    for (i = 1; i <= n * n; i++)
        if (!bad[i])
            cnt++;

    if (dif == 1)
        cnt = min(cnt, n * n - 1);
    printf("%d", cnt);


    return 0;
}
