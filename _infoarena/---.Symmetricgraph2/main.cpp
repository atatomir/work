#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011
#define inf 1000000

struct rest {
    int l, r, c;

    bool operator<(const rest& who)const {
        return (r - l) < (who.r - who.l);
    }
};

int n, m, i, x, y, c, cnt;
vector< pair<int, int> > list[maxN];
int aux[2][maxN];
queue<int> Q;

bool us[maxN];
bool leaf[maxN];
int l[maxN], r[maxN];

vector<rest> work;
int aib[maxN];


int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

int sum(int x) {
    int ans = 0;

    while (x) {
        ans += aib[x];
        x -= zrs(x);
    }

    return ans;
}

int add(int pos, int val) {
    while (pos <= n) {
        aib[pos] += val;
        pos += zrs(pos);
    }
}


void bfs(int node, int *dist) {
    int i;

    Q.push(node);
    dist[node] = 1;

    while (!Q.empty()) {
        node = Q.front(); Q.pop();

        for (auto to : list[node]) {
            if (dist[to.first]) continue;
            dist[to.first] = dist[node] + 1;
            Q.push(to.first);
        }
    }
}

void dfs(int node) {
    us[node] = true;

    if (leaf[node]) {
        if (l[node]) return;

        l[node] = r[node] = ++cnt;
        for (auto to : list[node])
            if (leaf[to.first])
                l[to.first] = r[to.first] = cnt, add(cnt, to.second);

        return;
    }

    l[node] = inf;
    r[node] = -inf;

    for (auto to : list[node]) {
        if (us[to.first]) continue;

        dfs(to.first);
        work.pb({l[to.first], r[to.first], to.second});

        l[node] = min(l[node], l[to.first]);
        r[node] = max(r[node], r[to.first]);
    }
}


int main()
{
    freopen("symmetricgraph2.in","r",stdin);
    freopen("symmetricgraph2.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &c);
        list[x].pb(mp(y, c));
        list[y].pb(mp(x, c));
    }

    bfs(1, aux[0]);
    bfs(n, aux[1]);

    for (i = 1; i <= n; i++)
        if ( abs(aux[0][i] - aux[1][i]) == 1 )
            leaf[i] = true;

    dfs(1);
    dfs(n);

    sort(work.begin(), work.end());
    for (auto e : work) {
        int act = sum(e.r) - sum(e.l - 1);

        if (act <= e.c) continue;
        add(e.l, -(act - e.c));
    }

    printf("%d\n", sum(n));

    return 0;
}
