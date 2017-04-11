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

#define maxN 2014
#define mod 1000000007
#define inf 1000000000

const int def = 2000;

int t, ti;
int n, i;

ll cnt[maxN][maxN];
ll dist[maxN][maxN];

ll ans;
pair<ll, ll> best;

int gcd(int x, int y) {
    if (x < y) swap(x, y);
    while (y > 0) {
        x %= y;
        swap(x, y);
    }
    return x;
}

void pre() {
    int i, j;

    for (i = 0; i <= def; i++)
        for (j = 0; j <= def; j++)
            dist[i][j] = inf;

    cnt[0][1] = cnt[1][0] = 1;
    dist[0][1] = dist[1][0] = 0;

    for (i = 0; i <= def; i++) {
        for (j = 0; j <= def; j++) {
            cnt[i][j] %= mod;
            if (i + j + 1 > def) continue;

            dist[i + j + 1][j] = min(dist[i + j + 1][j], dist[i][j] + 1);
            dist[i][i + j + 1] = min(dist[i][i + j + 1], dist[i][j] + 1);

            cnt[i + j + 1][j] += cnt[i][j];
            cnt[i][i + j + 1] += cnt[i][j];
        }
    }

    //freopen("err", "w", stderr);
    /*for (i = 0; i <= 30; i++) {
        for (j = 0; j <= 30; j++)
            if (dist[i][j] >= inf)
                cerr << '. ';
            else
                cerr << dist[i][j] << ' ';//(cnt[i][j] > 0 ? '#' : '.');
        cerr << '\n';
    }*/

    /*for (i = 0; i <= 30; i++) {
        for (j = 0; j <= 30; j++)
            cerr << (cnt[i][j] > 0 ? '#' : '.');
        cerr << '\n';
    }*/
}

void get_sol(int a, int b) {
    while (a > 0 || b > 0) {
        if (a > b) {
            printf("0 ");
            a -= b + 1;
        } else {
            printf("1 ");
            b -= a + 1;
        }
    }

    printf("\n");
}

int main()
{
    freopen("input","r",stdin);
    freopen("output","w",stdout);

    pre();

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d", &n);
        //n = ti;

        ans = 0;
        best = mp(inf, -1);

        for (i = 0; i <= n; i++) {
            ans += cnt[i][n - i];
            ans %= mod;
            best = min(best, mp(dist[i][n - i], 1LL * i));
        }

        printf("%lld\n", ans);
        get_sol(best.second, n - best.second);
    }


    return 0;
}
