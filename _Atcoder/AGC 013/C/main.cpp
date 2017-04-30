#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011

ll n, L, T, i, j, bonus;
ll x[maxN], aux;
int tp[maxN], sum[13];


int main()
{
    freopen("test.in","r",stdin);

    scanf("%lld%lld%lld", &n, &L, &T);
    for (i = 1; i <= n; i++) {
        scanf("%lld%d", &x[i], &tp[i]);
        sum[tp[i]]++;
    }

    bonus = 1LL * (T / L) * (n + sum[1] - sum[2]);
    bonus %= n;

    T %= L;
    for (i = 1; i <= n; i++) {
        if (tp[i] == 1) {
            if (x[i] + T >= L) bonus++;

            aux = x[i] + T;
            aux %= L;
            x[i] = aux;
        } else {
            if (x[i] - T < 0) bonus--;

            aux = x[i] + L - T;
            aux %= L;
            x[i] = aux;
        }
    }

    sort(x + 1, x + n + 1);

    bonus += n;
    bonus %= n;
    for (i = 1 + bonus; i <= n; i++) printf("%lld\n", x[i]);
    for (i = 1; i <= bonus; i++) printf("%lld\n", x[i]);



    return 0;
}
