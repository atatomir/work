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

#define maxN 2016

ll n, m;
ll ans, i, j;
ll cmmdc[maxN][maxN];

ll gcd(ll a, ll b) {
    if (a < b) swap(a, b);
    if (b == 0) cmmdc[a][b] = a;

    if (cmmdc[a][b]) return cmmdc[a][b];
    cmmdc[a][b] = gcd(b, a % b);
    return cmmdc[a][b];
}

int main()
{
    freopen("paralelograme.in","r",stdin);
    freopen("paralelograme.out","w",stdout);

    scanf("%lld%lld", &n, &m);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            ll aux = 1LL + 2 * (i + j - 2) + (i - 1) * (j - 1);
            aux += (i - 1) * (j - 1) - ( gcd(i, j) - 1 );

            ans += aux * (n - i + 1) * (m - j + 1);

            //cerr << i << ':' << j << "  ->  " << aux << '\n';
        }
    }

    printf("%lld", ans);

    return 0;
}
