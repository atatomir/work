#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 10011
#define pii pair<int, int>
#define inf 1000000000
#define def_start  -1000000
#define limit 1000000

int n, m, a, b, i, x, y, w, pos, mv, id;
vector< pii > list[maxN];
bool us[maxN];
int dist[maxN];

vector< vector<pii > > comp;
bool no_way = false;

bool busy[2 * limit + 11];
int ans[maxN];

vector<pii> v1, v2;



void dfs(int node) {
    us[node] = true;
    comp[id].pb(mp(node, dist[node]));

    for (auto to : list[node])
        if (!us[to.first])
            dist[to.first] = dist[node] + to.second, dfs(to.first);
}

void compute(int node) {
    comp.pb({});
    id = comp.size() - 1;
    dfs(node);
}

int push_vector(vector< pii >& who, int dep) {
    int i = 0;

    int mini = inf;
    for (auto e : who)
        mini = min(mini, e.second);

    for (i = 0; i < who.size(); i++)
        who[i].second -= mini;

    int maxi = -inf;

    for (auto e : who) {
        ans[ e.first ] = dep + e.second;
        maxi = max(maxi, dep + e.second);
    }

    return maxi + 1;
}

void print_sol() {
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
}

bool try_with(int dep) {
    for (auto e : v2)
        if (busy[ e.second + dep + limit])
            return false;

    cerr << "Found with : " << dep << '\n';
    return true;
}




int main()
{
    freopen("harta3.in","r",stdin);
    freopen("harta3.out","w",stdout);

    scanf("%d%d%d%d", &n, &m, &a, &b);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &w);
        list[x].pb(mp(y, w));
        list[y].pb(mp(x, -w));
    }

    compute(a);
    if(!us[b])
        compute(b);
    else
        no_way = true;

    for (i = 1; i <= n; i++)
        if (!us[i])
            compute(i);

    pos = def_start;

    if (no_way) {
        for (int i = 0; i < comp.size(); i++)
            pos = push_vector(comp[i], pos);

        print_sol();
        return 0;
    }

    for (i = 2; i < comp.size(); i++)
        pos = push_vector(comp[i], pos);


    v1 = comp[0];
    v2 = comp[1];

    for (auto e : v1)
        busy[e.second + limit] = true;

    for (i = 1; i <= 2400; i++) {
        if (try_with(+i)) {mv = i; break;}
        if (try_with(-i)) {mv = -i; break;}
    }

    for (auto e : v2)
        v1.pb(mp(e.first, e.second + mv));

    pos = push_vector(v1, pos);
    print_sol();


    cerr << "Finished at " << pos << '\n';

    return 0;
}
