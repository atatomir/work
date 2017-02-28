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

ll n, s;
ll i;

ll get_sum(ll b, ll n) {
    ll ans = 0;

    while (n > 0) {
        ans += n % b;
        n /= b;
    }

    return ans;
}

void check_small_base() {
    ll i;

    if (n <= s) return;

    for (i = 2; i * i <= n; i++) {
        if (get_sum(i, n) == s) {
            printf("%lld", i);
            exit(0);
        }
    }
}

void check_two_digits() {
    ll i, aux;

    if (n <= s) return;
    aux = n - s;

    for (i = 1; i * i <= aux; i++);

    for (i--; i > 0; i--) {
        if (aux % i != 0) continue;

        if (get_sum((aux / i) + 1, n) == s) {
            printf("%lld", (aux / i) + 1);
            exit(0);
        }
    }
}

void check_one_digit() {
    if (s == n) {
        printf("%lld", n + 1);
        exit(0);
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%lld%lld", &n, &s);
    check_small_base();
    check_two_digits();
    check_one_digit();

    printf("-1");

    return 0;
}
