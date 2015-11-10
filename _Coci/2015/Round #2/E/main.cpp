#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1000011

int n, i, m;
long long v[maxN], p;
long long aux[maxN];

int aib[maxN];
long long ans;

unordered_map<long long, int> H;

int zrs(int x) {
    return (x & (x - 1)) ^ x;
}

void add(int x) {
    while (x <= m) {
        aib[x]++;
        x += zrs(x);
    }
}

int sum(int x) {
    int ans = 0;
    while (x > 0) {
        ans += aib[x];
        x -= zrs(x);
    }
    return ans;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%lld", &v[i]);
    scanf("%lld", &p);
    for (i = 1; i <= n; i++) {
        v[i] += v[i - 1] - p;
        aux[i] = v[i];
    }

    m = n + 1;
    aux[m] = 0;
    sort(aux + 1, aux + m + 1);
    for (i = 1; i <= m; i++) H[ aux[i] ] = i;

    add( H[0] );
    for (i = 1; i <= n; i++) {
        int wh = H[v[i]];
        ans += 1LL * sum(wh);
        add(wh);
    }

    printf("%lld", ans);

    return 0;
}
