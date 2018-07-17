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

int n, k, i, x;

void solve() {
    int ans = n;
    int i, aux;

    for (i = max(1, x - k + 1); i <= min(n - k + 1, x); i++) {
        aux = (i - 1 + k - 2) / (k - 1);
        aux += (n - i - k + 1 + k - 2) / (k - 1);
        ans = min(ans, aux + 1);
    }

    printf("%d", ans);
}

int main()
{
   // freopen("test.in","r",stdin);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        if (x != 1) continue;
        x = i;
        solve();
        return 0;
    }


    return 0;
}
