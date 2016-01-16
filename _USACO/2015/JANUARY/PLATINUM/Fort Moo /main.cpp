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

#define maxN 222

int n, m, i, j, k;
char s[maxN][maxN];
int hori[maxN][maxN];
int vert[maxN][maxN];
int ans;

queue<int> Q;

void preprocess() {
    int i, j;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (s[i][j] == 'X') {
                hori[i][j] = vert[i][j] = 0;
            } else {
                hori[i][j] = hori[i][j - 1] + 1;
                vert[i][j] = vert[i - 1][j] + 1;
            }

            //! only one line/column
            ans = max(ans, hori[i][j]);
            ans = max(ans, vert[i][j]);
        }
    }
}

void compute() {
    int i, j, k;

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {

            while (!Q.empty()) Q.pop();

            for (k = 1; k <= m; k++) {
                int lim = max(k - hori[i][k], k - hori[j][k]);
                while (!Q.empty()) {
                    int now = Q.front();
                    if (now > lim) break;
                    Q.pop();
                }

                bool good = (vert[j][k] >= j - i + 1);

                if (!Q.empty() && good) {
                    int now = Q.front();

                    ans = max(ans, (k - now + 1) * (j - i + 1));
                }

                if (good)
                    Q.push(k);
            }
        }
    }
}

int main()
{
    freopen("fortmoo.in","r",stdin);
    freopen("fortmoo.out","w",stdout);

    scanf("%d%d\n", &n, &m);
    for (i = 1; i <= n; i++)
        scanf("%s\n", s[i] + 1);

    preprocess();
    compute();

    printf("%d", ans);


    return 0;
}
