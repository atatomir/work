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

#define maxN 100011
#define inf 1000000

int n, i;
int v[maxN];
ll ans;

int len[maxN];
int C, fin;

int main()
{
    freopen("numarare.in","r",stdin);
    freopen("numarare.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        scanf("%d", &v[i]);
    v[0] = v[n + 1] = -inf;


    C = fin = 0;
    for (i = 1; i < n; i++) {
        if (i + 1 <= fin) len[i] = min(len[2 * C - i], fin - i);
        while (v[i] + v[i + 1] == v[i + 1 + len[i]] + v[i - len[i]]) len[i]++;
        ans += 1LL * len[i];

        if (i + len[i] >= fin) {
            C = i;
            fin = i + len[i];
        }
    }

    printf("%lld", ans);

    return 0;
}
