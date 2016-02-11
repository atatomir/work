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

#define mod 1008989LL
#define mod2 47LL
#define maxN 400011

int n, m, i;
ll a, b, c, x, y;
ll smen[maxN];
ll mask;
ll ans;

int main()
{
    freopen("tetris3.in","r",stdin);
    freopen("tetris3.out","w",stdout);

    scanf("%d%d%lld%lld%lld%lld%lld", &n, &m, &a, &b, &c, &x, &y);
    mask = ((1LL << 47) - 1);

    for (i = 1; i <= m; i++) {
        int aa = min(a, b);
        int bb = max(a, b);

        smen[aa] += (1LL << (47 - c));
        smen[bb + 1] -= (1LL << (47 - c));
        smen[bb + 1] += (1LL << 47);

        //cerr << a << ' ' << b << ' ' << c << '\n';

        a = min(1LL * n, (a * i + a) % mod);
        b = min(1LL * n, (b * i + b) % mod);
        c = (x * c + y) % mod2 + 1;
    }

    for (i = 1; i <= n; i++) {
        smen[i] += smen[i - 1];
        smen[i] &= mask;
        ll aux = smen[i];

        while (aux) {
            ans++;
            aux &= (aux - 1);
        }
    }

    printf("%lld", ans);
    cerr << ans;

    return 0;
}
