#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011
#define eps 1e-11

struct Point {
    double x, y;

    bool operator<(const Point& who)const {
        return mp(x, y) < mp(who.x, who.y);
    }
};

struct Edge {
    int a, b;
    double tga, tgb;
};

struct face_edge {
    int n1, n2;
    int f;

    bool operator<(const face_edge& who)const {
        return mp(min(n1, n2), max(n1, n2)) < mp(min(who.n1, who.n2), max(who.n1, who.n2));
    }
};

int n, m, i, a, b, cnt;
Point P[maxN];
Edge E[4 * maxN];
set< pair<double, int> > list[maxN];
vector<int> ord;

vector< face_edge > F;
vector<int> adj[4 * maxN];

int gr[4 * maxN];
queue<int> Q;
bool in_queue[4 * maxN];
vector<int> col_ord;

bool deny[11];
int col[4 * maxN];





int get_next(int node, int id) {
    if (E[id].a == node)
        return E[id].b;
    else
        return E[id].a;
}

double get_ang(int node, int id) {
    if (E[id].a == node)
        return E[id].tga;
    else
        return E[id].tgb;
}

void start_route(int bg) {
    int node, to, id;
    double new_ang;

    cnt++;

    node = bg;
    auto it = list[node].begin();
    id = it->second;
    to = get_next(node, id);

    bool first_time = true;
    while (node != bg || first_time) {
        first_time = false;

        F.pb({node, to, cnt});
        list[node].erase(it);

        node = to; if(node == bg) break;
        new_ang = get_ang(node, id);
        it = list[node].lower_bound(mp(new_ang, 0));
        if (it != list[node].end())
            if (it->second == id)
                it++;

        if (it == list[node].end()) it = list[node].begin();
        id = it->second;
        to = get_next(node, id);

    }

}

int main()
{
    freopen("nowhere-zero.in","r",stdin);
    freopen("nowhere-zero.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) scanf("%lf%lf", &P[i].x, &P[i].y);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &a, &b);
        E[i] = {a, b, atan2(P[b].y - P[a].y, P[b].x - P[a].x), atan2(P[a].y - P[b].y, P[a].x - P[b].x)};
        list[a].insert(mp(E[i].tga, i));
        list[b].insert(mp(E[i].tgb, i));
    }

    for (i = 1; i <= n; i++) ord.pb(i);
    sort(ord.begin(), ord.end(), [](int a, int b)->bool const {
        return P[a] < P[b];
    });

    for (auto node : ord) {
        while (list[node].size() > 0)
            start_route(node);
    }

    sort(F.begin(), F.end());
    for (i = 0; i < F.size(); i += 2) {
        adj[F[i].f].pb(F[i + 1].f);
        adj[F[i + 1].f].pb(F[i].f);
    }

    for (i = 1; i <= cnt; i++) {
        sort(adj[i].begin(), adj[i].end());
        adj[i].resize(unique(adj[i].begin(), adj[i].end()) - adj[i].begin());
        gr[i] = adj[i].size();
    }

    for (i = 1; i <= cnt; i++)
        if (gr[i] <= 5)
            Q.push(i), in_queue[i] = true;

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();
        col_ord.pb(node);

        for (auto to : adj[node]) {
            if (--gr[to] && !in_queue[to]) {
                in_queue[to] = true;
                Q.push(to);
            }
        }
    }

    reverse(col_ord.begin(), col_ord.end());
    for (auto node : col_ord) {
        for (i = 1; i <= 6; i++) deny[i] = false;
        for (auto to : adj[node])
            deny[col[to]] = true;

        for (i = 1; deny[i]; i++);
        col[node] = i;
    }

    for (i = 0; i < F.size(); i += 2) {
        int n1 = F[i].n1;
        int n2 = F[i].n2;
        int dif = col[F[i].f] - col[F[i + 1].f];

        if (dif < 0) swap(n1, n2), dif = -dif;
        printf("%d %d %d\n", n1, n2, dif);
    }






    return 0;
}
