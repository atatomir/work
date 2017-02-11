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

#define maxN 111

struct frac {
    ll a, b;

    bool operator<=(const frac who) {
        return a * who.b <= b * who.a;
    }

    bool operator<(frac who)const {
        return a * who.b < b * who.a;
    }
};

struct Point {
    ll x, y;

    void read() {
        scanf("%lld%lld", &x, &y);
    }

    bool operator<(const Point who) {
        return mp(x, y) < mp(who.x, who.y);
    }
};

struct segm {
    Point A, B;
    int who;

    void refresh() {
        if (B < A) swap(A, B);
    }

    segm(Point _A, Point _B, int _who) {
        A = _A; B = _B; who = _who;
        refresh();
    }
};

struct edge {
    int x, y;
    frac dist;

    bool operator<(edge who)const {
        return dist < who.dist;
    }
};

int n, i, j, op, k;
Point A, B, C;

vector< pair<Point, int> > pts;
vector< segm > S;

frac dist[maxN][maxN];

vector<edge> E;
int dad[maxN];

int cnt_buy;
int ways;
double total;

vector<int> list[maxN];
bool us[maxN];
int local;


void upd(frac& dest, frac sour) {
    if (sour <= dest)
        dest = sour;
}

ll abss(ll x) {
    if (x < 0) return -x;
    return x;
}

void add_edges() {
    int i, j;
    Point A, B;
    frac aux, aux2;
    ll deltax, deltay, xx;

    for (auto e : pts) {
        auto p = e.first;
        int id = e.second;

        for (auto sg : S) {
            if (sg.who == id) continue;
            A = sg.A;
            B = sg.B;

            if (B.x < p.x) continue;
            if (A.x > p.x) continue;

            if (A.x == B.x) {
                aux = {abss(p.y - A.y), 1};
                aux2 = {abss(p.y - B.y), 1};

                if (aux2 <= aux) aux = aux2;

                upd(dist[id][sg.who], aux);
                upd(dist[sg.who][id], aux);
            } else {
                deltax = B.x - A.x;
                deltay = B.y - A.y;
                xx = p.x - A.x;

                aux = {A.y * deltax + deltay * xx, deltax};
                aux.a -= aux.b * p.y;
                aux.a = abss(aux.a);

                upd(dist[id][sg.who], aux);
                upd(dist[sg.who][id], aux);
            }
        }
    }
}

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
    return true;
}

void dfs(int node) {
    local++;
    us[node] = true;

    for (auto to : list[node])
        if (!us[to])
            dfs(to);
}

int main()
{
    freopen("elicoptere.in","r",stdin);
    freopen("elicoptere.out","w",stdout);

    scanf("%d%d%d", &op, &n, &k);
    for (i = 1; i <= n; i++) {
        A.read();
        B.read();
        C.read();

        pts.pb(mp(A, i));
        pts.pb(mp(B, i));
        pts.pb(mp(C, i));

        S.pb({A, B, i});
        S.pb({C, B, i});
        S.pb({A, C, i});
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            dist[i][j] = {k + 10, 1};

    add_edges();

    for (auto& e : pts)
        swap(e.first.x, e.first.y);

    for (auto& e : S) {
        swap(e.A.x, e.A.y);
        swap(e.B.x, e.B.y);
        e.refresh();
    }

    add_edges();

    for (i = 1; i <= n; i++) {
        dad[i] = i;

        for (j = i + 1; j <= n; j++) {
            if (dist[i][j] <= (frac){k, 1}) {
                E.pb({i, j, dist[i][j]});
            }
        }
    }

    sort(E.begin(), E.end());
    for (auto e : E) {
        int x = e.x;
        int y = e.y;

        if (Merge(x, y)) {
            cnt_buy++;
            total += 1.00 * e.dist.a / e.dist.b;

            list[x].pb(y);
            list[y].pb(x);
        }
    }

    for (i = 1; i <= n; i++) {
        if (us[i]) continue;

        local = 0;
        dfs(i);

        ways += (local * (local - 1)) / 2;
    }

    if (op == 1)
        printf("%d\n", cnt_buy);

    if (op == 2)
        printf("%d\n", ways);

    if (op == 3)
        printf("%.5lf", total);


    return 0;
}
