#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

#define pb push_back
#define mp make_pair

#define maxN 100011
#define mod 40099
#define bigModulo 1000000000000000LL
#define norm(x) while(x < 0) x += mod

int n, m, i;
int v[maxN];
long long sum;

pair<long long, long long> q1, q2, q3, q;
long long x, y, z;
long long def;

long long def_pow[mod + 11];

long long _pow(long long a, long long b) {
    long long ans = 1;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

long long _best_pow(long long b) {
    return def_pow[b];
}

void solve(pair<long long, long long> use) {
    long long _time = use.first % (mod - 1);
    int pos = use.second;

    long long abs_sum = ( sum * _best_pow(_time) ) % mod;

    if (_time % 2 == 0) {
        abs_sum -= sum;
        norm(abs_sum);

        abs_sum = (abs_sum * def ) % mod;
        abs_sum += v[pos];
        if (abs_sum >= mod) abs_sum -= mod;

        printf("%d\n", abs_sum);
    } else {
        pos = n - pos + 1;

        abs_sum += sum;
        if (abs_sum >= mod) abs_sum -= mod;

        abs_sum = (abs_sum * def ) % mod;
        abs_sum -= v[pos];
        norm(abs_sum);

        printf("%d\n", abs_sum);
    }
}

int main()
{
    freopen("complet.in", "r", stdin);
    freopen("complet.out", "w", stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        sum += v[i];
    }
    sort(v + 1, v + n + 1);
    sum %= mod;
    def = _pow(n, mod - 2);

    def_pow[0] = 1;
    for (i = 1; i <= mod; i++) def_pow[i] = (def_pow[i - 1] * (n - 1)) % mod;

    scanf("%lld%lld%lld", &x, &y, &z);
    scanf("%lld%lld", &q1.first, &q2.first);
    scanf("%lld%lld", &q3.first, &q1.second);
    scanf("%lld%lld", &q2.second, &q3.second);

    solve(q1);
    solve(q2);
    solve(q3);

    for (i = 4; i <= m; i++) {
        q.first = 1 + (q1.first * x + q2.first * y + q3.first * z) % bigModulo;
        q.second = 1 + (q1.second * x + q2.second * y + q3.second * z) % n;

        solve(q);
        q1 = q2; q2 = q3; q3 = q;
    }

    return 0;
}
