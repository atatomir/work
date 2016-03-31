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

#define maxN 55
#define maxK maxN * maxN
#define inf (1LL << 15)

struct Item {
    int x, y;
    double R;

    void read() {
        scanf("%d%d%lf", &x, &y, &R);
        R *= R;
    }
};

int n, m, i, j, k;
bool us[maxN][maxN];
int H[maxN][maxN];
Item work[maxK];

ll ans;

bool in_area(Item& who, int x, int y, int z) {
    static int h_aux;

    h_aux = H[who.x][who.y];
    ll aux = 1LL * (x - who.x) * (x - who.x) +
                   (y - who.y) * (y - who.y) +
                   (z - h_aux) * (z - h_aux);

    return aux <= who.R;
}

pair<ll, ll> get_intr(Item& who, int x, int y, int h_min, int h_sure) {
    pair<ll, ll> sol;

    /*ll ans = h_min - 1;
    for (ll step = inf; step; step >>= 1)
        if (ans + step < h_sure)
            if (!in_area(who, x, y, ans + step))
                ans += step;
    sol.first = ans + 1;

    ans = h_sure;
    for (ll step = inf; step; step >>= 1)
        if (ans + step <= inf)
            if (in_area(who, x, y, ans + step))
                ans += step;
    sol.second = ans;*/

    ll dif_max = (1LL * who.R -
                  (x - who.x) * (x - who.x) -
                  (y - who.y) * (y - who.y));
    dif_max = sqrt(dif_max);

    sol.first = max(1LL * h_min, H[who.x][who.y] - dif_max);
    sol.second = H[who.x][who.y] + dif_max;

    return sol;
}

ll count_them(int x, int y) {
    int i, z, z_aux;
    ll low = 0;
    ll high = inf;

    for (i = 1; i <= k; i++) {
        z_aux = H[ work[i].x ][ work[i].y ];
        z = max(H[x][y], z_aux);

        if (!in_area(work[i], x, y, z)) return 0;

        pair<ll, ll> act = get_intr(work[i], x, y, H[x][y], z);
        low = max(low, act.first);
        high = min(high, act.second);

        if (high < low) return 0;
    }

    return high - low + 1;
}

int main()
{
    freopen("radio.in","r",stdin);
    freopen("radio.out","w",stdout);

    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            scanf("%d", &H[i][j]);

    for (i = 1; i <= k; i++) {
        work[i].read();
        us[work[i].x][work[i].y] = true;
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (us[i][j]) continue;

            ans += count_them(i, j);
        }
    }

    printf("%lld", ans);


    return 0;
}
