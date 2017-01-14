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

#define maxN 17

int t, ti;
int n, m, i, j, maxi, maxi2;
char s[maxN][maxN];

int kx, ky;
int conf[maxN];

int mask;
char dp[maxN][maxN][1 << maxN];



char compute(int x, int y, int st) {
    if (y >= m) {
        y = 0;
        if (++x >= n)
            return 0;
    }

    char &ans = dp[x][y][st];
    if (ans != -1) return ans;

    int new_st = (st << 1) & mask;

    if (conf[x] & (1 << y)) {
        return ans = compute(x, y + 1, new_st);
    } else {
        ans = compute(x, y + 1, new_st + 1); // no pair
        if (y > 0 && (st & 1)) ans = max((int)ans, 1 + compute(x, y + 1, new_st - 2)); // hori : '---'
        if (y > 0 && (st & (1 << m))) ans = max((int)ans, 1 + compute(x, y + 1, new_st)); // diag : '\'
        if (st & (1 << (m - 1))) ans = max((int)ans, 1 + compute(x, y + 1, new_st - (1 << m))); // vert : '|'
        if (y + 1 < m && (st & (1 << (m - 2)))) ans = max((int)ans, 1 + compute(x, y + 1, new_st - (1 << (m - 1)))); // diag : '/'
    }

    return ans;
}

int pairUp() {
    memset(dp, -1, sizeof(dp));
    mask = (1 << (m + 1)) - 1;

    return compute(0, 0, 0);

}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d", &t);
    cerr << "Solving " << t << " cases.\n";
    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << "\n";

        scanf("%d%d\n", &n, &m);
        for (i = 0; i < n; i++)  {
            scanf("%s", s[i]);

            conf[i] = 0;
            for (j = 0; j < m; j++) {
                if (s[i][j] == '#') conf[i] |= 1 << j;
                if (s[i][j] == 'K') {
                    kx = i;
                    ky = j;
                }
            }
        }

        maxi = pairUp();
        conf[kx] |= 1 << ky;
        maxi2 = pairUp();

        if (maxi == maxi2)
            printf("Case #%d: B\n", ti);
        else
            printf("Case #%d: A\n", ti);
    }



    return 0;
}
