#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 10011
#define mod 30103

int n, k, i;
int fact[maxN];

int myPow(int a, int b) {
    int ans = 1;

    while (b) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

int main()
{
    freopen("functii.in","r",stdin);
    freopen("functii.out","w",stdout);

    scanf("%d%d", &n, &k);
    if (k == 0 || k == 1 || k == n) {
        printf("0");
        return 0;
    }

    fact[1] = 1;
    for (i = 2; i <= n; i++) fact[i] = (fact[i - 1] * i) % mod;

    long long ans = ((fact[n] * myPow(fact[k], mod - 2)) % mod ) * ((myPow(fact[n - k], mod - 2) * (myPow(2, k) - 2)) % mod);
    printf("%lld", ans % mod);

    return 0;
}
