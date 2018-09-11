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

#define lSon (node << 1)
#define rSon (lSon | 1)

const int maxN = 100011;

int n, i, j, x;
double here[maxN];
vector<int> list[maxN];
double ans = 0.00;


double dfs(int node, int rem) {
    double ans = here[node];

    if (--rem == 0) return ans;

    for (auto to : list[node])
        ans += dfs(to, rem);

    return ans;
}

int main()
{
    freopen("craciun.in","r",stdin);
    freopen("craciun.ok","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%lf", &here[i]);
    for (i = 2; i <= n; i++) {
        scanf("%d", &x);
        list[x].pb(i);
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            ans = max(ans, dfs(i, j) / j);
        }
    }

    printf("%.10lf", ans);



    return 0;
}
