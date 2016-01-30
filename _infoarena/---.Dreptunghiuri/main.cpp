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

#define maxN 444

int n, m, i;
int how[maxN][maxN];
int a, b, c, d;
ll ans;

int gcd(int x, int y) {
    if (x < y) swap(x, y);

    while (y) {
        x %= y;
        swap(x, y);
    }

    return x;
}

int main()
{
    freopen("dreptunghiuri.in","r",stdin);
    freopen("dreptunghiuri.out","w",stdout);

    scanf("%d%d", &n, &m);
    n--; m--;

    for (a = 1; a < n; a++) {
        for (b = 1; b < m; b++) {
            int frs = a / gcd(a, b);

            for (c = frs; b + c <= m; c += frs) {
                d = (c * b) / a;

                if (d + a <= n)
                    how[a + d][b + c]++;
                else
                    break;
            }
        }
    }

    for (a = 1; a <= n; a++)
        for (b = 1; b <= m; b++)
            ans += 1LL * (how[a][b] + 1) * (n - a + 1) * (m - b + 1);

    printf("%lld", ans);
    cerr << ans;

    return 0;
}
