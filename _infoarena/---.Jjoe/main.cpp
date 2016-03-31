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

#define def 40000LL

ll a, b, p, k;
ll d, x, y;
ll sum;


ll euclid(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    ll _x, _y;
    ll d = euclid(b, a % b, _x, _y);
    x = _y;
    y = _x - _y * (a / b);

    return d;
}

void no_sol() {
    printf("NU");
    exit(0);
}

bool test_solution(ll x, ll y) {
    sum = (x > 0 ? x : -x) + (y > 0 ? y : -y);
    if (sum > k) return false;

    sum = k - sum;
    if (sum & 1) return false;
    sum >>= 1;

    printf("DA\n");
    if (x < 0)
        printf("%lld %lld ", sum, -x + sum);
    else
        printf("%lld %lld ", x + sum, sum);

    if (y < 0)
        printf("%lld %lld ", 0LL, -y);
    else
        printf("%lld %lld ", y, 0LL);

    exit(0);
    return true;
}

int main()
{
    freopen("jjoe.in","r",stdin);
    freopen("jjoe.out","w",stdout);

    scanf("%lld%lld%lld%lld", &a, &b, &p, &k);

    if (a > b)
        d = euclid(a, b, x, y);
    else
        d = euclid(b, a, y, x);

    if (p % d) no_sol();
    x *= p / d;
    y *= p / d;

    for (ll i = 0; i <= 100000; i++) {
        ll xx = x + i * b / d;
        ll yy = y - i * a / d;

        test_solution(xx, yy);

        xx = x - i * b / d;
        yy = y + i * a / d;

        test_solution(xx, yy);
    }

    no_sol();


    return 0;
}
