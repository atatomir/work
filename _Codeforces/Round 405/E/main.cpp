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

#define maxN 200011
//#define double long double

const int def = 1000000;

struct Point {
    ll x, y;
    double ang;

    Point operator-(Point who) {
        return {x - who.x, y - who.y};
    }

    bool operator<(const Point& who)const {
        return ang <= who.ang;
    }
};

struct Line {
    double a, b, c;

    Line(Point A, Point B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);

        a /= c;
        b /= c;
        c /= c;
    }

    pair<double, double> intersect(Line who) {
        double y = (a * who.c - who.a * c) / (-a * who.b + b * who.a);
        double x = (who.c * b - c * who.b) / (a * who.b - b * who.a);
        return {x, y};
    }


    bool operator<(const Line& who)const {
        return mp(a, b) < mp(who.a, who.b);
    }
};

int t, ti;
int n, i;
Point P[2 * maxN];

vector<Line> lines, Hull;
vector< pair<double, double> > ans;

ll cross(const Point& A, const Point& B) {
    return A.x * B.y - A.y * B.x;
}

double cross(const Line& A, const Line& B, const Line& C) {
    static double xb, yb, xc, yc;

    xb = B.a - A.a;
    yb = B.b - A.b;

    xc = C.a - A.a;
    yc = C.b - A.b;

    return xb * yc - xc * yb;
}

double solve() {
    int i, j, pos, limit;
    Point O = P[1];

    for (i = 2; i <= n; i++) P[i - 1] = P[i];
    n--;

    for (i = 1; i <= n; i++)
        P[i].ang = atan2(P[i].y, P[i].x);

    lines.clear();
    sort(P + 1, P + n + 1);
    for (i = 1; i <= n; i++) P[i + n] = P[i], lines.pb(Line(P[i], P[i + 1]));
    if (n == 2) lines.pop_back();

    pos = 1;
    for (i = 1; i <= n; i++) {
        pos = max(pos, i);
        while (pos + 1 < i + n && cross(P[i], P[pos + 1]) >= 0)
            pos++;

        if (cross(P[i], P[pos]) == 0 && pos != i)
            return 0.00;

        if (pos > i + 1)
            lines.pb(Line(P[i], P[pos]));
    }

    ///////////////////////////
    /*lines.clear();
    for (i = 1; i <= n; i++)
        for (j = i + 1; j <= n; j++)
            lines.pb(Line(P[i], P[j]));*/
    ////////////////////////////

    lines.pb(Line({def - O.x, -1}, {def - O.x, + 1}));
    lines.pb(Line({-def - O.x, -1}, {-def - O.x, + 1}));

    lines.pb(Line({-1, def - O.y}, {1, def - O.y}));
    lines.pb(Line({-1, -def - O.y}, {1, -def - O.y}));

    sort(lines.begin(), lines.end());
    Hull.clear();

    // up
    limit = 2;
    for (i = 0; i < lines.size(); i++) {
        auto act = lines[i];

        while (Hull.size() >= limit) {
            int sz = Hull.size();
            if (cross(Hull[sz - 2], Hull[sz - 1], act) < 0) break;
            Hull.pop_back();
        }

        Hull.pb(act);
    }

    // down
    limit = Hull.size() + 1;
    for (i = lines.size() - 2; i >= 0; i--) {
        auto act = lines[i];

        while (Hull.size() >= limit) {
            int sz = Hull.size();
            if (cross(Hull[sz - 2], Hull[sz - 1], act) < 0) break;
            Hull.pop_back();
        }

        Hull.pb(act);
    }

    ans.clear();
    for (i = 0; i + 1 < Hull.size(); i++)
        ans.pb(Hull[i].intersect(Hull[i + 1]));
    ans.pb(ans[0]);

    double area = 0.00;
    for (i = 0; i + 1 < ans.size(); i++) {
        area += ans[i].first * ans[i + 1].second -
                ans[i].second * ans[i + 1].first;
    }

    area /= 2.00;
    if (area < 0) area *= -1;
    return area;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d", &n);
        for (i = 1; i <= n; i++)
            scanf("%lld%lld", &P[i].x, &P[i].y);
        for (i = n; i > 1; i--)
            P[i] = P[i] - P[1];

        printf("%.12lf\n", (double)solve());
    }



    return 0;
}
