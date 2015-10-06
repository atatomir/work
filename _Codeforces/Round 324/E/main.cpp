#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 2015

int n, i, x, best;
int v[maxN];
int wh[maxN];

bool us[maxN];
vector<int> act;
vector<int> work;

vector< pair<int, int> > ans;

long long coin;

int abss(int x) {
    if (x > 0) return x;
    return -x;
}

void dfs(int node) {
    us[node] = true;
    act.pb(node);

    if (!us[ v[node] ])
    dfs(v[node]);
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &v[i]);
    for (i = 1; i <= n ;i++) {
        scanf("%d", &x);
        wh[x] = i;
    }
    for (i = 1; i <= n; i++) v[i] = wh[v[i]];

    for (i = 1; i <= n; i++) {
        if (us[i]) continue;

        act.clear();
        dfs(i);

        if (act.size() == 1) continue;

        act.pb(act[0]);

        best = 1;
        for (i = 2; i < act.size(); i++)
            if ( abss(act[i] - act[i - 1]) > abss(act[best] - act[best - 1]) )
                best = i;

        work.clear();
        for (i = best; i < act.size(); i++) work.pb(act[i]);
        for (i = 1; i < best; i++) work.pb(act[i]);

        for (i = work.size() - 1; i > 0; i--) {
            ans.pb(mp(work[i], work[i - 1]));
            coin += abss(work[i] - work[i - 1]);
        }
    }

    printf("%I64d\n%d\n", coin, ans.size());
    for (auto who : ans) printf("%d %d\n", who.first, who.second);


    return 0;
}
