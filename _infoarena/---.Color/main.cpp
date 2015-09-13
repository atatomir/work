#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 4015

int n, m, i, x, y;
int gr[maxN];
vector< pair<int, int> > Red;

long long ans;
long long aux;

int main()
{
    freopen("color.in","r",stdin);
    freopen("color.out","w",stdout);

    scanf("%d %d",&n, &m);
    for (i = 1; i <= n; i++) gr[i] = n - 1;

    if (n <= 2) {
        printf("0");
        return 0;
    }

    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        Red.pb(mp(x, y));

        gr[x]--; gr[y]--;
    }

    ans = 1LL * n * (n - 1) * (n - 2);
    ans = ans / 6;

    for (auto e : Red) aux += gr[e.first] + gr[e.second];
    ans -= aux / 2;

    printf("%lld", ans);

    return 0;
}
