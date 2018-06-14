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

const int maxN = 100011;

int n, m, i, x, y, R;
int a[maxN], b[maxN];
int gr[maxN];
vector<int> list[maxN], adj[maxN];
bool used[maxN];
ll ans, act;
ll add[maxN], sum[maxN];

vector< pair<int, int> > ord;
int dad[maxN];

int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

bool Merge(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    dad[x] = y;
    adj[y].pb(x);


    return true;
}

void make_tree() {
    int i;
    
    for (i = 1; i <= n; i++) dad[i] = i;
    sort(ord.begin(), ord.end());

    for (auto node : ord) {
        used[node.second] = true;
        for (auto to : list[node.second]) {
            if (!used[to]) continue;
            Merge(to, node.second);
        }
    }

    R = ord.back().second;
}

void dfs(int node) {
    int i;
    
    for (auto to : adj[node])
        dfs(to);

    for (auto to : adj[node]) {
        sum[node] += sum[to];
        add[node] = min(add[node], add[to] + max(0LL, a[node] - b[node] - add[to] -
                    sum[to]));
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &a[i], &b[i]);
        a[i] = max(a[i], b[i]);
        ord.pb(mp(a[i] - b[i], i));
   }

    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    make_tree();

    for (i = 1; i <= n; i++) {
        add[i] = a[i] - b[i];
        sum[i] = b[i];
    }
    dfs(R);

    printf("%lld", sum[R] + add[R]);

    return 0;
}
