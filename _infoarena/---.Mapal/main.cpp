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

int n, i, j, k, x;
char s[maxN][maxN];
bool ln[maxN], co[maxN];

int ans;
int cnt, sum;
bool us[maxN][maxN];

void dfs(int x, int y) {
    us[x][y] = true;
    cnt++;
    if (s[x][y] == '1') sum++;

    int xx = n - x + 1;
    int yy = n - y + 1;

    if (co[y] && !us[xx][y])
        dfs(xx, y);

    if (ln[x] && !us[x][yy])
        dfs(x, yy);
}

int main()
{
    freopen("mapal.in","r",stdin);
    freopen("mapal.out","w",stdout);

    scanf("%d\n", &n);
    for (i = 1; i <= n; i++) scanf("%s\n", s[i] + 1);

    scanf("%d", &k);
    for (i = 1; i <= k; i++) {
        scanf("%d", &x);
        ln[x] = true;
    }

    scanf("%d", &k);
    for (i = 1; i <= k; i++) {
        scanf("%d", &x);
        co[x] = true;
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (us[i][j]) continue;
            cnt = sum = 0;

            dfs(i, j);
            ans += min(sum, cnt - sum);
        }
    }

    printf("%d", ans);


    return 0;
}
