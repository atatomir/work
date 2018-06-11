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

#define maxM 104
#define maxT 2018

#define inf 10011
#define tm tmm

struct Pokemon {
    int house, points, limit;
};

int n, k, m, i, j, p1, p2, tm, max_limit, l, r, need;
Pokemon P[maxM];
short dp[maxT][maxM][maxM], ans;

void upd(short& a, short b) {
    if (b > a) a = b;
}

int abss(int x) {
    if (x < 0) return -x;
    return x;
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n >> k >> m;
    for (i = 1; i <= m; i++) {
        cin >> P[i].house >> P[i].points >> P[i].limit;
        max_limit = max(max_limit, P[i].limit);
    }

    for (i = 1; P[i].house < k && i <= m; i++);
    if (P[i].house != k) {
        for (j = m; j >= i; j--) P[j + 1] = P[j];
        P[i] = {k, 0, 1};
        m++;
    }

    P[i].points++;

    dp[0][i][i] = P[i].points; ans = P[i].points;
    for (tm = 0; tm < max_limit; tm++) {
        for (p1 = 1; p1 <= m; p1++) {
            for (p2 = 1; p2 <= m; p2++) {
                if (dp[tm][p1][p2] == 0) continue;
                upd(ans, dp[tm][p1][p2]);

                if (p1 <= p2) {
                    l = p1;
                    r = p2;
                } else {
                    l = p2;
                    r = p1;
                }

                if (l != 0) {
                    need = tm + P[p1].house - P[l - 1].house;
                    if (need <= max_limit) {
                        upd(dp[need][l - 1][r], dp[tm][p1][p2] + (need < P[l - 1].limit ? P[l - 1].points : 0));
                    }
                }

                if (r != m) {
                    need = tm + P[r + 1].house - P[p1].house;
                    if (need <= max_limit) {
                        upd(dp[need][r + 1][l], dp[tm][p1][p2] + (need < P[r + 1].limit ? P[r + 1].points : 0));
                    }
                }
            }
        }
    }

    cout << ans - 1;


    return 0;
}
