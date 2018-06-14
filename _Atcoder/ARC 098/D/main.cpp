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

const int maxN = 200011;

int n, i, j, sum, xorsum;
int a[maxN], nxt[maxN];
ll ans;

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    nxt[n + 1] = n + 1;
    for (i = n; i >= 1; i--)
        nxt[i] = (a[i] == 0 ? nxt[i + 1] : i);

    for (i = 1; i <= n; i++) {
        sum = xorsum = a[i];
        ans++;

        for (j = i + 1; j <= n; j = nxt[j + 1]) {
            sum += a[j];
            xorsum ^= a[j];

            if (sum != xorsum) break;
            ans += 1LL * nxt[j + 1] - j;
        }
    }

    cout << ans;


    return 0;
}
