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
#define mod 1000000009

int n, d, i, j;
int dim[maxN], high[maxN];
int ans;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &d);
    for (i = 0; i < n; i++) scanf("%d", &dim[i]);

    sort(dim, dim + n);
    for (i = j = 0; i < n; i++) {
        while (j + 1 < n && dim[i] + d >= dim[j + 1]) j++;
        high[i] = j;
    }

    ans = 1;
    for (i = n - 1; i >= 0; i--)
        ans = (1LL * ans * (high[i] - i + 1)) % mod;

    printf("%d", ans);

    return 0;
}
