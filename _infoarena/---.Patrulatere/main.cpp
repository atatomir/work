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

#define maxN 277
#define x first
#define y second

int n, i, j, k;
pair<int, int> P[maxN];
int how[maxN][maxN];
ll ans, aux;

bool upper(int i, int j, int k) {
    if (P[k].x > min(P[i].x, P[j].x) && P[k].x <= max(P[i].x, P[j].x))
        if ( 1LL * (P[j].x - P[i].x) * (P[k].y - P[i].y) -
             1LL * (P[k].x - P[i].x) * (P[j].y - P[i].y) > 0)
                return true;
    return false;
}


int main()
{
    freopen("patrulatere.in","r",stdin);
    freopen("patrulatere.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d%d", &P[i].first, &P[i].second);
    sort(P + 1, P + n + 1);

    if (n < 4) {
        printf("0");
        return 0;
    }

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            for (k = 1; k <= n; k++)
                if (upper(i, j, k))
                    how[i][j]++;

            how[j][i] = -how[i][j];
        }
    }

    ans = 1LL * n * (n - 1) * (n - 2) * (n - 3);
    ans /= 1LL * 1 * 2 * 3 * 4;



    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            for (k = j + 1; k <= n; k++) {
                aux = how[i][j] + how[j][k] + how[k][i];

                if (upper(i, j, k)) aux--;
                if (upper(j, k, i)) aux--;
                if (upper(i, k, j)) aux++;

                ans -= (aux < 0 ? -aux : aux);
            }
        }
    }

    printf("%lld", ans);

    return 0;
}
