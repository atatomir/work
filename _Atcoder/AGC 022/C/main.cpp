#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int maxN = 55;
const int def = 51;

int n, i, j, a, b, bit;
int from[maxN], to[maxN];
bool can[maxN][maxN][maxN], aux[maxN];
bool act[maxN][maxN];
ll ans;

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++) cin >> from[i];
    for (i = 1; i <= n; i++) cin >> to[i];

    for (i = 0; i <= def; i++) can[0][i][i] = true;
    for (i = 1; i <= def; i++) {
        for (a = 0; a <= def; a++) {
            for (b = 0; b <= a; b++) {
                can[i][a][b] |= can[i - 1][a][b];
                can[i][a][b] |= can[i - 1][a % i][b];
            }
        }
    }

    for (i = 1; i <= n; i++) {
        if (!can[def][from[i]][to[i]]) {
            printf("-1");
            return 0;
        }
    }

    for (i = 1; i <= n; i++) act[i][from[i]] = true;
    for (bit = def; bit > 0; bit--) {
        bool need = false;

        for (i = 1; i <= n; i++) {
            bool any = false;

            for (j = 0; j <= def; j++)
                if (act[i][j] && can[bit - 1][j][to[i]])
                    any = true;

            if (!any) need = true;
        }


        if (!need) {

            for (i = 1; i <= n; i++) {
                memcpy(aux, act[i], sizeof(aux));
                memset(act[i], 0, sizeof(aux));

                for (j = 0; j <= def; j++)
                    if (aux[j] && can[bit - 1][j][to[i]])
                        act[i][j] = true;
            }

        } else {
            ans |= 1LL << bit;

            for (i = 1; i <= n; i++) {
                memcpy(aux, act[i], sizeof(aux));
                memset(act[i], 0, sizeof(aux));

                for (j = 0; j <= def; j++) {
                    if (aux[j] && can[bit - 1][j][to[i]])
                        act[i][j] = true;

                    if (aux[j] && can[bit - 1][j % bit][to[i]])
                        act[i][j % bit] = true;
                }
            }
        }
    }

    cout << ans;



    return 0;
}
