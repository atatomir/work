#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 2017

int limit = 2000000001;

int n, op, st, dr, i, j, ss, dd;
int m[2][maxN], best[maxN];
bitset<maxN> le[maxN], up[maxN], good[maxN];

vector<int> dp[maxN];

void sumi(int &a, int b) {
    if (limit - a < b)
        a = limit;
    else
        a += b;
}

void print_way(int cnt) {
    int i, j;

    i = j = 1;

    while (i < n) {
        printf("%d ", j);

        if (up[i + 1][j]) {
            if (cnt <= dp[i + 1][j]) {
                i++;
            } else {
                cnt -= dp[i + 1][j];
                i++; j++;
            }
        } else {
            i++;
            j++;
        }
    }

    printf("%d\n", j);

}

int main()
{
    freopen("summax.in","r",stdin);
    freopen("summax.out","w",stdout);

    scanf("%d%d%d%d", &op, &n, &st, &dr);

    ss = 0;
    dd = 1;
    scanf("%d", &m[ss][1]);
    for (i = 2; i <= n; i++) {
        for (j = 1; j <= i; j++) scanf("%d", &m[dd][j]);

        memset(best, 0, sizeof(best));
        for (j = 1; j < i; j++) {
            best[j] = max(best[j], m[ss][j] + m[dd][j]);
            best[j + 1] = max(best[j + 1], m[ss][j] + m[dd][j + 1]);
        }

        for (j = 1; j <= i; j++) {
            if (j != 1 && best[j] == m[ss][j - 1] + m[dd][j])
                le[i][j] = 1;
            if (best[j] == m[ss][j] + m[dd][j])
                up[i][j] = 1;

            m[dd][j] = best[j];
        }

        swap(ss, dd);
    }

    int need = -1;
    for (i = 1; i <= n; i++)
        need = max(need, m[ss][i]);

    for (i = 1; i <= n; i++)
        if (m[ss][i] == need)
            good[n][i] = 1;

    for (i = n - 1; i > 0; i--) {
        for (j = 1; j <= i; j++) {
            good[i][j] = good[i][j] | (up[i + 1][j] && good[i + 1][j]);
            good[i][j] = good[i][j] | (le[i + 1][j + 1] && good[i + 1][j + 1]);
        }
    }

    for (i = 1; i <= n; i++) dp[i].resize(i + 2);
    for (i = 1; i <= n; i++) dp[n][i] = good[n][i];
    for (i = n - 1; i > 0; i--) {
        for (j = 1; j <= i; j++) {
            if (good[i][j] == 0) continue;
            if (up[i + 1][j]) sumi(dp[i][j], dp[i + 1][j]);
            if (le[i + 1][j + 1]) sumi(dp[i][j], dp[i + 1][j + 1]);
        }
    }

    if (op == 1) {
        printf("%d", dp[1][1]);
        return 0;
    }

    for (i = st; i <= dr; i++)
        print_way(i);







    return 0;
}
