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
#define inf (17 * maxN)


const int mask = (1 << 30) - 1;

int n, i, x, y;
vector<int> list[maxN];
int conf[maxN];

void solve(int node, int root) {
    int mand, mor, pos;

    mand = 0;
    mor = 0;

    for (auto to : list[node]) {
        if (to == root) continue;
        solve(to, node);

        mand |= (mor & conf[to]);
        mor |= conf[to];
    }


    for (pos = 0; (1 << pos) <= mand; pos++);
    for (; (1 << pos) & mor; pos++);

    mor |= 1 << pos;
    for (pos--; pos >= 0; pos--) mor &= mask ^ (1 << pos);
    conf[node] = mor;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    solve(1, 0);

    int ans = 0;
    for (; (1 << ans) <= conf[1]; ans++);

    printf("%d", ans - 1);


    return 0;
}
