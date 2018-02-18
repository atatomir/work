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

int n, m, i, l, r, d;
vector< pair<int, int> > list[maxN];
ll x[maxN];
bool us[maxN];

void dfs(int node) {
    us[node] = true;

    for (auto to : list[node]) {
        if (us[to.first]) {
            if (x[to.first] != x[node] + to.second) {
                printf("No");
                exit(0);
            }
        } else {
            x[to.first] = x[node] + to.second;
            dfs(to.first);
        }
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &l, &r, &d);
        list[l].pb(mp(r, d));
        list[r].pb(mp(l, -d));
    }

    for (i = 1; i <= n; i++)
        if (!us[i])
            dfs(i);

    printf("Yes");


    return 0;
}
