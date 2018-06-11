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

const int maxN = 100011;

ll n, S, i, l, r;
ll x[maxN], p[maxN];
ll ans;

int main()
{
    freopen("test.in","r",stdin);

    scanf("%lld%lld", &n, &S);
    for (i = 1; i <= n; i++)
        scanf("%lld%lld", &x[i], &p[i]);

    l = 1; r = n;
    while (true) {
        if (S < x[l]) {
            ans += x[r] - S;
            break;
        }

        if (S > x[r]) {
            ans += S - x[l];
            break;
        }

        ans += x[r] - x[l];

        bool any = false;
        while (x[r] > S && p[l] >= p[r]) {
            p[l] += p[r];
            r--;
            any = true;
        }

        if (any) continue;

        while (x[l] < S && p[l] < p[r]) {
            p[r] += p[l];
            l++;
        }
    }

    printf("%lld", ans);

    return 0;
}
