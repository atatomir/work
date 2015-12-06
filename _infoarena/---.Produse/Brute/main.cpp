#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 101
#define ll long long

ll n, d, i;
ll v[maxN];
int ans;

void brute(int pas, ll pr) {
    if (pas == n + 1) {
        ans++;
        return;
    }

    if (v[pas] > pr) {
        brute(n + 1, pr);
        return;
    }

    brute(pas + 1, pr);
    brute(pas + 1, pr / v[pas]);
}

int main()
{
    freopen("produse.in","r",stdin);
    freopen("produse.ok","w",stdout);

    scanf("%lld%lld", &n, &d);
    for (i = 1; i <= n; i++)
        scanf("%lld", &v[i]);

    sort(v + 1, v + n + 1);

    brute(1, d);
    printf("%lld", ans - 1);

    return 0;
}
