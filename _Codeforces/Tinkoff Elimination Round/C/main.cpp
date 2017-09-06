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

#define maxN 100011
#define eps 1e-5

struct Line {
    double a, b, c;
    double x1, y1, x2, y2;

    Line(double x, double y, double xx, double yy) {
        a = yy - y;
        b = x - xx;
        c = -(a * x + b * y);

        x1 = x;
        x2 = xx;
        y1 = y;
        y2 = yy;

        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
    }
};

int n, i;
double x, y, xx, yy;
double rx, ry, vx, vy;
double l, r;
vector<Line> rect;

vector< pair< pair<int, int>, pair<int, int> > > rez;

bool _equal(double a, double b) {
    return -eps <= a - b && a - b <= eps;
}

bool intersect(Line A, Line B, double& x, double& y) {
    double up1 = B.c * A.b - A.c * B.b;
    double up2 = B.a * A.c - A.a * B.c;
    double down = A.a * B.b - B.a * A.b;

    if (_equal(down, 0.00)) return false;
    x = up1 / down;
    y = up2 / down;

    return true;
}

void add_line() {
    double x, y;
    Line aux(rx, ry, rx + vx, ry + vy);
    vector< pair<double, double> > ord;
    int pos, i;
    double dx, dy, dif;

    if (_equal(vx, 0.00) && _equal(vy, 0.00)) {
        if (x - eps <= rx && rx <= xx + eps && y - eps <= ry && ry <= y + eps)
            return;
        printf("-1");
        exit(0);
    }

    ord.clear();
    for (auto e : rect) {
        if (intersect(e, aux, x, y)) {
            if (e.x1 - eps <= x && x <= e.x2 + eps && e.y1 - eps <= y && y <= e.y2 + eps)
                ord.pb(mp(x, y));
        }
    }

    if (ord.empty()) {
        printf("-1");
        exit(0);
    }

    sort(ord.begin(), ord.end());
    pos = 1;

    for (i = 1; i < ord.size(); i++) {
        if (!_equal(ord[i - 1].first, ord[i].first) || !_equal(ord[i - 1].second, ord[i].second))
            ord[pos++] = ord[i];
    }
    ord.resize(pos);

    if (ord.size() != 2 && ord.size() != 1)
        cerr << "err\n";

    if (ord.size() == 1) {
        //! second
        dx = ord[0].first - rx;
        dy = ord[0].second - ry;
        if (!_equal(vx, 0))
            dif = dx / vx;
        else
            dif = dy / vy;

        r = min(r, dif - eps);
        l = max(l, dif + eps);
        return;
    }

    vector<double> auxx = {};

    //! first
    dx = ord[0].first - rx;
    dy = ord[0].second - ry;
    if (!_equal(vx, 0))
        dif = dx / vx;
    else
        dif = dy / vy;

    auxx.pb(dif);

    //! second
    dx = ord[1].first - rx;
    dy = ord[1].second - ry;
    if (!_equal(vx, 0))
        dif = dx / vx;
    else
        dif = dy / vy;

    auxx.pb(dif);

    sort(auxx.begin(), auxx.end());
    l = max(l, auxx[0] + 1e-8);
    r = min(r, auxx[1] - 1e-8);
}

bool check(double x) {
    int i;

    for (auto e : rez) {
        rx = e.first.first;
        ry = e.first.second;
        vx = e.second.first;
        vy = e.second.second;

        rx += vx * x;
        ry += vy * x;

        if (x + eps < rx && rx < xx - eps && y + eps < ry && ry < yy - eps ) continue;
        return false;
    }

    return true;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    scanf("%lf%lf%lf%lf", &x, &y, &xx, &yy);
    if (x > xx) swap(x, xx);
    if (y > yy) swap(y, yy);

    rect.pb((Line){x, y, x, yy});
    rect.pb((Line){x, y, xx, y});
    rect.pb((Line){xx, yy, xx, y});
    rect.pb((Line){xx, yy, x, yy});

    l = 0; r = 1e18;
    for (i = 1; i <= n; i++) {
        scanf("%lf%lf%lf%lf", &rx, &ry, &vx, &vy);
        rez.pb(mp(mp(rx, ry), mp(vx, vy)));
        add_line();
    }

    if (r + eps < l || r - l < eps) {
        printf("-1");
        return 0;
    }

    if (!check(l)) {
        printf("-1");
        return 0;
    }


    printf("%.10lf", l);
    cerr << '\n' << r;



    return 0;
}
