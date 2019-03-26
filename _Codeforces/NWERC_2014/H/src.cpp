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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

const int maxN = 20011;

int n, i, x, y;
vector<int> list[maxN];
int c[maxN][2];

int dad[maxN];
int cnt[maxN];
int ans;

int Find(int x) {
    if (dad[x] == x) return dad[x];
    dad[x] = Find(dad[x]);
    return dad[x];
}

void Merge(int x, int y) {
    x = Find(x);
    y = Find(y);

    ans += 1 - (cnt[x] > 1 ? 1 : 0) - (cnt[y] > 1 ? 1 : 0);
    //cerr << x << ' ' << y << ' ' << cnt[x] << ' ' << cnt[y]  << '\n';

    dad[x] = y;
    cnt[y] += cnt[x];
}

void rear(int id) {
    if (cnt[Find(c[id][0])] > cnt[Find(c[id][1])])
        swap(c[id][0], c[id][1]);
}

void dfs(int node, int root) {
    for (auto to : list[node]) {
        if (to == root) continue;

        dfs(to, node);

        rear(node);
        rear(to);

        Merge(c[node][0], c[to][0]);
        if (cnt[Find(c[node][1])] == 1 &&
            cnt[Find(c[to][1])] == 1) Merge(c[node][1], c[to][1]);
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        c[i][0] = i;
        c[i][1] = n + i;
        dad[i] = i;
        dad[i + n] = i + n;
        cnt[i] = cnt[i + n] = 1;
    }

    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    dfs(1, 0);
    for (i = 1; i <= n; i++)
        printf("%d %d\n", Find(c[i][0]), Find(c[i][1]));

    debug(ans);

    return 0;
}
