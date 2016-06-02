#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>


using namespace std;


#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 111
#define inf 1000000000

int n, m, T, i, j, k, x, y, c, low, high;
int ener[maxN];
int dist[maxN][maxN];
int roy[maxN][maxN];
vector< pair<int, int> > help, h2;

void solution(int x, int y, int low, int high) {
    printf("%d %d %d %d", x, y, low, high);
    exit(0);
}

int main() {
    freopen("coach.in", "r", stdin);
    freopen("coach.out", "w", stdout);

    scanf("%d%d%d", &n, &m, &T);
    for (i = 1; i <= n; i++) scanf("%d", &ener[i]), help.pb(mp(ener[i], i));

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            dist[i][j] = inf;

    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &c);
        dist[x][y] = dist[y][x] = c;
    }

    sort(help.begin(), help.end());

    //! sa intre..
    h2 = help;
    random_shuffle(h2.begin(), h2.end());

    for (auto act : h2) {
        low = act.first;

        memcpy(roy, dist, sizeof(roy));

        for (auto act2 : help) {
            k = act2.second;
            high = act2.first;
            if (act2.first < low) continue;

            for (i = 1; i <= n; i++) {
                for (j = 1; j <= n; j++) {
                    if (i != k && j != k && i != j)
                        roy[i][j] = min(roy[i][j], roy[i][k] + roy[k][j]);
                    if (low <= ener[i] && ener[i] <= high)
                        if (low <= ener[j] && ener[j] <= high)
                            if (roy[i][j] == T)
                                solution(i, j, low, act2.first);

                }
            }


        }
    }


    return 0;
}
