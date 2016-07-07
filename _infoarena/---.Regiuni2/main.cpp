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

#define maxN 15
#define eps 1e-7

bool is_equal(double a, double b) {
    return -eps < a - b && a - b < eps;
}

struct Point {
    double x, y;

    void read() {
        scanf("%lf%lf", &x, &y);
    }

    bool operator<(const Point& who)const {
        return mp(x, y) < mp(who.x, who.y);
    }

    bool operator==(const Point who) {
        return is_equal(x, who.x) && is_equal(y, who.y);
    }
};

struct Line {
    double a, b, c;

    void with_pts(const Point A, const Point B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }

    bool paral(const Line who) {
        if (is_equal(a, 0.00))
            return is_equal(a, who.a);
        if (is_equal(b, 0.00))
            return is_equal(b, who.b);
        return is_equal(a * who.b, who.a * b);
    }

    Point inters(const Line who) {
        static double up1, up2, sub;

        up1 = b * who.c - who.b * c;
        up2 = a * who.c - who.a * c;
        sub = a * who.b - who.a * b;

        return {up1 / sub, -up2 / sub};
    }
};

struct Segm {
    Point A, B;
    Line ec;

    Segm(Point _A, Point _B) {
        A = _A; B = _B;
        ec.with_pts(A, B);
    }

    bool inside(Point P) {
        if (A.x > B.x) swap(A, B);
        if (P.x + eps < A.x || P.x - eps > B.x) return false;

        if (A.y > B.y) swap(A, B);
        if (P.y + eps < A.y || P.y - eps > B.y) return false;

        return true;
    }
};



int t, ti;
int n, m, i;
Point ini[maxN];
vector< Segm > act, aux;
vector< Point > news;

Point A, B;
Line crs;

vector<bool> bad;


void uniq(vector<Point> &work) {
    int i, j, pos;

    bad.resize(work.size());
    for (i = 0; i < work.size(); i++) bad[i] = false;
    for (i = 0; i < work.size(); i++)
        for (j = i + 1; j < work.size(); j++)
            if (work[i] == work[j])
                bad[j] = true;

    pos = 0;
    for (i = 0; i < work.size(); i++)
        if (bad[i] == false)
            work[pos++] = work[i];

    work.resize(pos);
    sort(work.begin(), work.end());
}

void uniq2(vector<Segm> &work) {
    int i, j, pos;

    bad.resize(work.size());
    for (i = 0; i < work.size(); i++) bad[i] = false;
    for (i = 0; i < work.size(); i++)
        for (j = i + 1; j < work.size(); j++)
            if (work[i].A == work[j].A && work[i].B == work[j].B)
                bad[j] = true;

    pos = 0;
    for (i = 0; i < work.size(); i++)
        if (bad[i] == false)
            work[pos++] = work[i];

    while (work.size() != pos) work.pop_back();
}

void rm_small(vector<Segm> &work) {
    int i, pos;

    pos = 0;
    for (i = 0; i < work.size(); i++) {
        if (is_equal(work[i].A.x, work[i].B.x) &&
            is_equal(work[i].A.y, work[i].B.y))
                continue;

        work[pos++] = work[i];
    }

    while (work.size() > pos) work.pop_back();
}

void add_new_line() {
    int i;
    Point mid;

    aux = act;
    act.clear();
    news.clear();

    for (auto now : aux) {
        if (crs.paral(now.ec)) {
            act.pb(now);
            continue;
        }

        mid = crs.inters(now.ec);
        if (!now.inside(mid)) {
            act.pb(now);
            continue;
        }

        //! divide the segment
        act.pb(Segm(now.A, mid));
        act.pb(Segm(now.B, mid));

        news.pb(mid);
    }

    uniq(news);
    for (i = 1; i < news.size(); i++)
        act.pb(Segm(news[i - 1], news[i]));

    rm_small(act);
    uniq2(act);
}




int main()
{
    freopen("regiuni2.in","r",stdin);
    freopen("regiuni2.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%d", &n, &m);
        act.clear();

        for (i = 1; i <= n; i++) ini[i].read();
        for (i = 1; i < n; i++) act.pb(Segm(ini[i], ini[i + 1]));
        act.pb(Segm(ini[1], ini[n]));

        for (i = 1; i <= m; i++) {
            A.read(); B.read();
            crs.with_pts(A, B);

            add_new_line();
        }

        rm_small(act);
        uniq2(act);

        //for (auto e : act)
        //    cerr << e.A.x << ' ' << e.A.y << ' ' << e.B.x << ' ' << e.B.y << '\n';


        news.clear();
        for (auto e : act) {
            news.pb(e.A);
            news.pb(e.B);
        }

        uniq(news);
        printf("%d\n", act.size() - news.size() + 1);
        cerr << act.size() - news.size() + 1 << '\n';
    }


    return 0;
}
