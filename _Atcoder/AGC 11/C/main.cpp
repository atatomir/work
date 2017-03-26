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

int n, m, i, x, y;
vector<int> list[maxN];
int col[maxN];
ll ans;
int cnt, cnt1, cnt2, cnt3;
bool ok;

void dfs(int node) {
    cnt++;

    for (auto to : list[node]) {
        if (!col[to]) {
            col[to] = col[node] ^ 3;
            dfs(to);
        } else {
            if (col[to] == col[node])
                ok = false;
        }
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);

    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    for (i = 1; i <= n; i++) {
        if (col[i]) continue;

        ok = true;
        cnt = 0;

        col[i] = 1;
        dfs(i);

        if (cnt == 1) {
            cnt3++;
            continue;
        }

        if (ok)
            cnt1++;
        else
            cnt2++;
    }

    ans = 2LL * cnt1 * cnt1;
    ans += 2LL * cnt1 * cnt2;
    ans += 1LL * cnt2 * cnt2;
    ans += 2LL * cnt3 * (n - cnt3);
    ans += 1LL * cnt3 * cnt3;
    printf("%lld", ans);



    return 0;
}
