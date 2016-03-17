#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long
#define eps 1e-5

#define maxN 100011

int n, m, i, x, y;
pair<int, int> P[maxN];
vector< pair<int, int> > edges;
set< pair<double, int> > list[maxN];

vector< vector<int> > dual_edge;

int cnt;
vector<int> dual_list[maxN];
int start_node;

map< pair<int, int>, bool > added;
map< pair<int, int>, bool > damaged;

queue<int> Q;
int lvl[maxN];

vector<int> still_good;
int ind[maxN];

int comp_cnt;
int comp[maxN];
bool first_time[maxN];



int get_to(int id, int from) {
    if (edges[id].first == from)
        return edges[id].second;
    else
        return edges[id].first;
}

void solve(int node, double ang) {
    //cerr << P[node].first << ' ' << P[node].second << '\n';

    auto it = list[node].lower_bound( mp(ang + eps, 0) );

    if (it == list[node].end())
        it = list[node].begin();

    dual_edge[it->second].pb(cnt);

    int to = get_to(it->second, node);
    if (to != start_node)
        solve(to, atan2(P[node].second - P[to].second, P[node].first - P[to].first));

    list[node].erase(it);
}

bool new_face(int node) {
    if (list[node].empty()) return false;

    //cerr << P[node].first << ' ' << P[node].second << '\n';

    cnt++;
    start_node = node;

    auto it = list[node].begin();

    dual_edge[it->second].pb(cnt);

    int to = get_to(it->second, node);
    solve(to, atan2(P[node].second - P[to].second, P[node].first - P[to].first));
    list[node].erase(it);

    return true;
}

bool cmp(int a, int b) {
    return P[a] < P[b];
}

void dfs(int node) {
    comp[node] = comp_cnt;
    for (auto e : list[node]) {
        int to = get_to(e.second, node);
        if (comp[to] == 0)
            dfs(to);
    }
}




int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &P[i].first, &P[i].second);

        ind[i] = i;
    }

    //! add edges
    scanf("%d", &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);

        edges.pb(mp(x, y));
        dual_edge.pb({});

        list[x].insert(mp( atan2(P[y].second - P[x].second, P[y].first - P[x].first), edges.size() - 1 ));

        swap(x, y);
        list[x].insert(mp( atan2(P[y].second - P[x].second, P[y].first - P[x].first), edges.size() - 1 ));
    }

    //! get connex components
    for (i = 1; i <= n; i++) {
        if (comp[i]) continue;
        comp_cnt++;
        dfs(i);
        first_time[comp_cnt] = true;
    }

    //! get faces
    sort(ind + 1, ind + n + 1, cmp);
    for (i = 1; i <= n; i++) {
        int rez = cnt + 1;

        if (first_time[ comp[ind[i]] ]) {
            first_time[ comp[ind[i]] ] = false;
            rez = max(cnt, 1);
            cnt = 0;
        }

        while (new_face(ind[i]));
        cnt = rez;
    }

    //! add dual edges
    added.clear();
    for (i = 0; i < edges.size(); i++) {
        if (dual_edge[i][0] == dual_edge[i][1]) continue;

        int x = dual_edge[i][0];
        int y = dual_edge[i][1];
        if (x > y) swap(x, y);

        if (added[mp(x, y)]) continue;

        added[mp(x, y)] = true;
        dual_list[x].pb(y);
        dual_list[y].pb(x);
    }


    //! get damaged edges
    damaged.clear();
    lvl[1] = 1;
    Q.push(1);

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();

        for (int to : dual_list[node]) {
            if (lvl[to] == 0) {
                lvl[to] = lvl[node] + 1;
                Q.push(to);
            }


            if (lvl[to] > lvl[node]) {
                pair<int, int> aux;

                if (node < to)
                    aux = mp(node, to);
                else
                    aux = mp(to, node);

                damaged[aux] = true;
            }

        }
    }


    //! get final result
    for (i = 0; i < edges.size(); i++) {
        pair<int, int> aux = mp( dual_edge[i][0], dual_edge[i][1] );
        if (aux.first > aux.second) swap(aux.first, aux.second);

        if (damaged[aux] == false) {
            still_good.pb(i);
        }
    }


    //! print result
    printf("%d\n", still_good.size());
    for (int e : still_good)
        printf("%d\n", e + 1);

    return 0;
}
