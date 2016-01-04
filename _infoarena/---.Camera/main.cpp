#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 2015
#define inf 1000000.15
#define eps 1e-5

struct Line {
    double a, b, c;

    void get_from_points(pair<double, double> p1, pair<double, double> p2) {
        a = p2.second - p1.second;
        b = p1.first - p2.first;
        c = -( p1.first * a + p1.second * b );
    }

    pair<double, double> intersect(Line& who) {
        double supp_x = b * who.c - who.b * c;
        double supp_y = a * who.c - who.a * c;
        double subb = who.a * b - a * who.b;

        if (-eps < subb && subb < eps)
            return mp(inf, inf);

        return mp(-supp_x / subb, supp_y / subb);
    }
};

int n, i, dim;
pair<double, double> P[maxN];
pair<double, double> View[maxN];
bool unuseful[maxN];

bool zeroArea = false;

void show_points() {
    return;

    cerr << "-------------Points---------------\n";
    for (int i = 1; i <= dim; i++)
        cerr << View[i].first << ' ' <<  View[i].second << '\n';
    cerr << "\n";
}

double cross(pair<double, double> p1, pair<double, double> p2) {
    return p1.first * p2.second - p1.second * p2.first;
}

pair<double, double> diff(pair<double, double> a, pair<double, double> b) {
    return mp(a.first - b.first, a.second - b.second);
}

bool isIntersection(pair<double, double> p1, pair<double, double> p2, pair<double, double> pp1, pair<double, double> pp2) {
    double v1 = cross( diff(p2, p1), diff(pp1, p1) );
    double v2 = cross( diff(p2, p1), diff(pp2, p1) );

    return v1 * v2 < -eps;
}

double getArea(pair<double, double> *Poly, int from, int to) {
    double ans = 0.00;
    for (int i = from; i < to; i++)
        ans += cross(Poly[i], Poly[i + 1]);
    ans += cross(Poly[to], Poly[1]);

    return ans / 2.00;
}

void swap_all() {
    int i = 1;
    int j = n;

    while (i < j) swap(P[i++], P[j--]);
}

void addLine(pair<double, double> p1, pair<double, double> p2) {
    int i;

    if (zeroArea)
        return;

    //! Add new points

    Line A; A.get_from_points(p1, p2);

    dim++;
    View[dim] = View[1];

    for (i = 1; i < dim; i++) {
        Line B;
        B.get_from_points(View[i], View[i + 1]);

        auto wh = A.intersect(B);
        bool good = isIntersection(p1, p2, View[i], View[i + 1]);

        if (!good) continue;

        for (int j = dim + 1; j > i + 1; j--)
            View[j] = View[j - 1];
        View[i + 1] = wh;
        dim++;
        i++;
    }

    dim--;


    //! Remove wrong points
    memset(unuseful, 0, sizeof(unuseful));

    for (i = 1; i <= dim; i++) {
        double how = cross(diff(p2, p1), diff(View[i], p1));
        if (how < -eps)
            unuseful[i] = true;
    }

    int pos = 1;
    for (i = 1; i <= dim; i++)
        if (!unuseful[i])
            View[pos++] = View[i];
    dim = pos - 1;

    if (dim == 0)
        zeroArea = true;

    show_points();
}

int main()
{
    freopen("camera.in","r",stdin);
    freopen("camera.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        scanf("%lf %lf", &P[i].first, &P[i].second);

    double area = getArea(P, 1, n);
    if (area < 0)
        swap_all();

    dim = 4;
    View[1] = mp(-inf, -inf);
    View[2] = mp(inf, -inf);
    View[3] = mp(inf, inf);
    View[4] = mp(-inf, inf);

    for (i = 1; i < n; i++)
        addLine(P[i], P[i + 1]);
    addLine(P[n], P[1]);

    if (zeroArea)
        printf("0.00");
    else
        printf("%.2lf", getArea(View, 1, dim));

    return 0;
}
