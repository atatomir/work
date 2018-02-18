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

#define maxN 1000011
#define mod 1000000007

const ll def = 1000000;
const ll p2 = (mod + 1) / 2;

ll m, i, x, y, sz, xx, k;
ll sum_full[maxN], sum_part[maxN];
ll ans;

void add(ll& a, ll b) {
    a += b;
    if (a >= mod) a -= mod;
}

ll gauss(ll a, ll b) {
    ll aux = (a + b) * (b - a + 1);
    aux %= mod;
    aux *= p2;
    aux %= mod;
    return aux;
}

void pre() {
    ll i, sz, p1, p2;

    sum_full[1] = sum_part[1] = 1;
    for (i = 2; i <= def; i++) {
        p1 = (i - 1) * (i - 1);
        p2 = i * i;

        sz = 2 * i - 1;

        sum_part[i] = sum_part[i - 1] + sz * i;
        sum_part[i] %= mod;

        sum_full[i] = sum_full[i - 1] + i * gauss(p1 + 1, p2);
        sum_full[i] %= mod;
    }
}

void add_to_sol() {
    while (k * k > sz) k--;

    ll aux = 0;

    aux += sum_full[k];
    aux %= mod;

    aux += (m - k * k + xx) * sum_part[k];
    aux %= mod;

    ans += aux;
    ans %= mod;
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> m;
    pre();

    for (x = 1; x * x <= m; x++) {
        add(ans, gauss(x * x, m));
    }

    k = sqrt(m);
    while ((k + 1) * (k + 1) <= m) k++;

    for (x = 1; x * x < m; x++) {
        xx = x * x;
        sz = m - xx;

        add_to_sol();
    }

    ans *= 4LL;
    ans %= mod;

    ans += m;
    ans %= mod;

    cout << ans;


    return 0;
}
