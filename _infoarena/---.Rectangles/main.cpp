#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 1024

struct Point {
    int x, y, id;

    bool operator<(const Point& who)const {
        return mp(x, y) < mp(who.x, who.y);
    }

     bool operator==(const Point& who)const {
        return mp(x, y) == mp(who.x, who.y);
    }
};

bool on_line(Point A, Point B, Point C) {
    if (A.x == B.x && B.x == C.x) return true;
    if (A.y == B.y && B.y == C.y) return true;
    return false;
}

struct rect {
    int x1, y1, x2, y2;

    vector<Point> intr(rect& who) {
        vector<Point> ans = {};
        Point aux;

        aux = {x1, who.y1};
        if (on_line({x1, y1}, aux, {x1, y2}) && on_line({who.x1, who.y1}, aux, {who.x2, who.y1}))
            ans.pb(aux);

        aux = {x1, who.y2};
        if (on_line({x1, y1}, aux, {x1, y2}) && on_line({who.x1, who.y2}, aux, {who.x2, who.y2}))
            ans.pb(aux);

        aux = {x2, who.y1};
        if (on_line({x2, y1}, aux, {x2, y2}) && on_line({who.x1, who.y1}, aux, {who.x2, who.y1}))
            ans.pb(aux);

        aux = {x2, who.y2};
        if (on_line({x2, y1}, aux, {x2, y2}) && on_line({who.x1, who.y2}, aux, {who.x2, who.y2}))
            ans.pb(aux);

        return ans;
    }
};

int n, i, j, cnt;
rect R[maxN];
vector<Point> P;
vector<Point> rez;
vector<int> l, r, u, d;
vector<short> add, rm, val;
map<Point, int> M;

int dim, aib_dim;
vector<int> aib;
vector< Point > data;
vector< vector<int> > to_remove;

ll ans;

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void aib_add(int pos, int val) {
    while (pos <= aib_dim) {
        aib[pos] += val;
        pos += zrs(pos);
    }
}

int aib_sum(int pos) {
    int ans = 0;
    while (pos > 0) {
        ans += aib[pos];
        pos -= zrs(pos);
    }
    return ans;
}

void compute_down_up() {
    int i, j;
    sort(P.begin(), P.end());

    add = rm = val = vector<short>(cnt + 2, 0);
    for (i = 1; i <= n; i++) {
        add[M[{R[i].x1, R[i].y1}]]++;
        add[M[{R[i].x2, R[i].y1}]]++;
        rm[M[{R[i].x1, R[i].y2}]]++;
        rm[M[{R[i].x2, R[i].y2}]]++;
    }

    auto sub_solve = [](int p1, int p2)->void {
        int i;

        d[P[p1].id] = P[p1].id;
        val[P[p1].id] = add[P[p1].id] - rm[P[p1].id];
        for (i = p1 + 1; i <= p2; i++) {
            val[P[i].id] = val[P[i - 1].id] + add[P[i].id] - rm[P[i].id];
            d[P[i].id] = P[i].id;
            if (val[P[i - 1].id] > 0) d[P[i].id] = d[P[i - 1].id];
        }

        u[P[p2].id] = P[p2].id;
        for (i = p2 - 1; i >= p1; i--) {
            u[P[i].id] = P[i].id;
            if (val[P[i].id] > 0) u[P[i].id] = u[P[i + 1].id];
        }
    };

    for (i = 0; i < cnt; i = j) {
        for (j = i; j < cnt; j++)
            if (P[i].x != P[j].x)
                break;

        sub_solve(i, j - 1);
    }
}

void compute_left_right() {
    int i, j;
    sort(P.begin(), P.end(), [](const Point& a, const Point& b)->bool const {
        return mp(a.y, a.x) < mp(b.y, b.x);
    });

    add = rm = val = vector<short>(cnt + 2, 0);
    for (i = 1; i <= n; i++) {
        add[M[{R[i].x1, R[i].y1}]]++;
        add[M[{R[i].x1, R[i].y2}]]++;
        rm[M[{R[i].x2, R[i].y1}]]++;
        rm[M[{R[i].x2, R[i].y2}]]++;
    }

    auto sub_solve = [](int p1, int p2)->void {
        int i;

        l[P[p1].id] = P[p1].id;
        val[P[p1].id] = add[P[p1].id] - rm[P[p1].id];
        for (i = p1 + 1; i <= p2; i++) {
            val[P[i].id] = val[P[i - 1].id] + add[P[i].id] - rm[P[i].id];
            l[P[i].id] = P[i].id;
            if (val[P[i - 1].id] > 0) l[P[i].id] = l[P[i - 1].id];
        }

        r[P[p2].id] = P[p2].id;
        for (i = p2 - 1; i >= p1; i--) {
            r[P[i].id] = P[i].id;
            if (val[P[i].id] > 0) r[P[i].id] = r[P[i + 1].id];
        }
    };

    for (i = 0; i < cnt; i = j) {
        for (j = i; j < cnt; j++)
            if (P[i].y != P[j].y)
                break;

        sub_solve(i, j - 1);
    }
}

void compute_answer() {
    int i, j;

    sort(P.begin(), P.end(), [](const Point& a, const Point& b)->bool const {
        return mp(a.x - a.y, mp(a.x, a.y)) < mp(b.x - b.y, mp(b.x, b.y));
    });

    auto get_count = [](int pos, Point act)->void {
        int len, pos_limit;

        len = min(act.x - rez[ l[act.id] ].x, act.y - rez[ d[act.id] ].y);
        auto it = lower_bound(&data[0] + 1, &data[0] + pos + 1, (Point){act.x - len, act.y - len});
        pos_limit = it - &data[0];

        ans += aib_sum(pos);
        ans -= aib_sum(pos_limit - 1);
    };

    auto add_Point = [](int pos, Point act)->void {
        int len, pos_rm;

        aib_add(pos, +1);
        len = min(rez[ r[act.id] ].x - act.x, rez[ u[act.id] ].y - act.y);
        auto it = upper_bound(&data[0] + pos, &data[0] + dim + 1, (Point){act.x + len, act.y + len}); it--;
        pos_rm = it - &data[0];

        while ((int)to_remove.size() - 1 < pos_rm)
            to_remove.pb({});
        to_remove[pos_rm].pb(pos);
    };

    auto sub_solve = [&add_Point, &get_count](int p1, int p2)->void {
        int i;

        if (p1 == p2) return;

        dim = aib_dim = p2 - p1 + 1;
        aib = vector<int>(dim + 1, 0);
        data = vector<Point>(dim + 1, (Point){0, 0, 0});
        for (i = 1; i <= dim; i++) data[i] = P[p1 + i - 1];

        for (i = 1; i <= dim; i++) {
            get_count(i, data[i]);
            add_Point(i, data[i]);
            if (to_remove.size() - 1 >= i) {
                for (auto e : to_remove[i]) aib_add(e, -1);
                to_remove[i].clear();
            }
        }
    };

    for (i = 0; i < cnt; i = j) {
        for (j = i; j < cnt; j++)
            if (P[i].x - P[i].y != P[j].x - P[j].y)
                break;

        sub_solve(i, j - 1);
    }
}

int main()
{


    freopen("rectangles.in","r",stdin);
    freopen("rectangles.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &R[i].x1, &R[i].y1, &R[i].x2, &R[i].y2);
        if (R[i].x1 > R[i].x2) swap(R[i].x1, R[i].x2);
        if (R[i].y1 > R[i].y2) swap(R[i].y1, R[i].y2);

        P.pb({R[i].x1, R[i].y1});
        P.pb({R[i].x2, R[i].y1});
        P.pb({R[i].x1, R[i].y2});
        P.pb({R[i].x2, R[i].y2});
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (i == j) continue;
            for (auto e : R[i].intr(R[j]))
                P.pb(e);
        }
    }

    sort(P.begin(), P.end());
    P.resize(unique(P.begin(), P.end()) - P.begin());
    rez.resize(P.size() + 3);
    for (i = 0; i < P.size(); i++) P[i].id = i + 1, M[P[i]] = i + 1, rez[i + 1] = P[i];
    cnt = P.size();

    l = r = u = d = vector<int>(cnt + 11, 0);
    compute_down_up();
    compute_left_right();
    compute_answer();

    printf("%lld", ans);


    return 0;
}
