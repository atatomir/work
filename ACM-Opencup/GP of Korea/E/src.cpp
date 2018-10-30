#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

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


ostream& operator<<(ostream& cerr, vector<int> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

const int maxN = 100011;

int n, m, i, x, y, S, cnt, last;
vector<int> list[maxN];
vector< pair<int, int> > edges;
int ord[maxN];
bool us[maxN];
set<int> St;

void dfs2(int node) {
    us[node] = true;
    last = node;
    for (auto to : list[node])
        if (!us[to])
            dfs2(to);
}

void dfs(int node) {
    if (node != S) ord[node] = ++cnt;
    us[node] = true;

    for (auto to : list[node])
        if (!us[to])
            dfs(to);
}

void no_sol() {
    printf("No");
    exit(0);
}

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) return a > b;
    return a < b;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
        edges.pb(mp(x, y));
    }

    dfs2(1);
    memset(us, 0, sizeof(us));

    S = last;
    ord[1] = 1;
    cnt = 1;

    dfs(S);
    if (cnt != n) no_sol();

    for (auto& e : edges) {
        e.first = ord[e.first];
        e.second = ord[e.second];
        if (e.first > e.second) swap(e.first, e.second);
    }

    sort(edges.begin(), edges.end(), cmp);
    
    for (auto e : edges) {
        int bg = e.first;
        int en = e.second;

        auto it = St.lower_bound(bg + 1);
        if (it != St.end()) {
            if (*it < en)
                no_sol();
        }

        St.insert(en);
    }

    printf("Yes");

    return 0;
}
