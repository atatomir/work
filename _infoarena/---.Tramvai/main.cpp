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

#define maxN 1024
#define inf 1e18
#define pii pair<double, double>
#define piii pair<double, int>
#define state(a, b, c) mp(a, mp(b, c))
#define eps 0.000001

struct cmp {
    bool operator()(const piii& a, const piii& b) {
        return a > b;
    }
};

struct Line {
    double a, b, c;

    void get_from(int xx1, int yy1, int xx2, int yy2) {
        a = (yy2 - yy1);
        b = (xx1 - xx2);
        c = -xx1 * a - yy1 * b;
    }

    pair<double, double> intersect(Line &who) {
        double sub = a * who.b - b * who.a;
        double sup1 = b * who.c - c * who.b;
        double sup2 = a * who.c - c * who.a;

        if (sub == 0) return mp(inf, inf);
        return mp(sup1 / sub, -sup2 / sub);
    }
};

int n, i, j, xx1, yy1, xx2, yy2, id_begin, id_end;
Line L[maxN];
pii deny = mp(inf, inf);
pii adj[maxN][maxN];

int ls1, ls2, lf1, lf2;

vector<double> dist_to_dest;
vector< pii > points;
vector< int > on_line[maxN];
vector< pair<int, double> > list[maxN * maxN];
double cost[maxN * maxN];

priority_queue< piii, vector<piii>, cmp> H;

double dist(pii a, pii b) {
    return sqrt( (a.first - b.first) * (a.first - b.first) +
                 (a.second - b.second) * (a.second - b.second)  );
}

bool cmp(int a, int b) {
    return points[a] < points[b];
}

int main()
{
    freopen("tramvai.in","r",stdin);
    freopen("tramvai.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &xx1, &yy1, &xx2, &yy2);
        L[i].get_from(xx1, yy1, xx2, yy2);
    }
    scanf("%d%d%d%d", &ls1, &ls2, &lf1, &lf2);
    if (ls1 > ls2) swap(ls1, ls2);
    if (lf1 > lf2) swap(lf1, lf2);

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            adj[i][j] = adj[j][i] = L[i].intersect(L[j]);
            if (adj[i][j] == deny) continue;

            points.pb(adj[i][j]);
            on_line[i].pb(points.size() - 1);
            on_line[j].pb(points.size() - 1);

            if (i == ls1 && j == ls2) id_begin = points.size() - 1;
            if (i == lf1 && j == lf2) id_end = points.size() - 1;

            cost[ points.size() - 1 ] = inf;
        }
    }

    for (auto P : points)
        dist_to_dest.pb(dist(P, points[id_end]));


    for (i = 1; i <= n; i++) {
        sort(on_line[i].begin(), on_line[i].end(), cmp);

        for (j = 0; j < on_line[i].size(); j++) {
            if (j != 0)
                list[ on_line[i][j] ].pb( mp(on_line[i][j - 1], dist(points[on_line[i][j - 1]], points[on_line[i][j]] )));
            if (j + 1 < on_line[i].size())
                list[ on_line[i][j] ].pb( mp(on_line[i][j + 1], dist(points[on_line[i][j + 1]], points[on_line[i][j]] )));
        }
    }

    cost[id_begin] = dist_to_dest[id_begin];
    H.push(mp(cost[id_begin], id_begin));

    while (!H.empty()) {
        auto now = H.top(); H.pop();
        int node = now.second;
        double pay = now.first - dist_to_dest[node];

        if (node == id_end) break;

        if (cost[node] < pay - eps) continue;

        cost[node] = pay;
        for (auto to : list[node]) {
            double now_cost = cost[node] + to.second;

            if (now_cost < cost[to.first]) {
                cost[to.first] = now_cost;
                H.push(mp(cost[to.first] + dist_to_dest[to.first], to.first));
            }
        }
    }

    printf("%.6lf", cost[id_end]);


    return 0;
}
