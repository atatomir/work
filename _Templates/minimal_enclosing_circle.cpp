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

namespace mec {

    struct Point {
        double x, y;

        Point() {}

        Point(double _x, double _y) {
            x = _x; y = _y;
        }

        void read() {
            scanf("%lf%lf", &x, &y);
        }

        double dist(Point & who) {
            return sqrt( (x - who.x) * (x - who.x) + (y - who.y) * (y - who.y) );
        }
    };

    struct Line {
        double a, b, c;

        void from(Point A, Point B) {
            a = B.y - A.y;
            b = A.x - B.x;
            c = -A.x * a - A.y * b;
        }

        Line perp(Point A) {
            Line ans = *this;

            if (a != 0.00 && b != 0.00) {
                ans.a = -(ans.b / ans.a);
                ans.b = 1.00;
            } else {
                swap(ans.a, ans.b);
            }

            ans.c = -A.x * ans.a - A.y * ans.b;
            return ans;
        }

        Point intersect(Line &who) {
            double sub = a * who.b - b * who.a;
            double sup1 = b * who.c - c * who.b;
            double sup2 = a * who.c - c * who.a;

            return(Point(sup1 / sub, -sup2 / sub));
        }
    };

    struct Circle {
        Point C;
        double R;

        Circle() {}

        Circle(Point _C, double _R) {
            C = _C;
            R = _R;
        }

        bool is_in(Point A) {
            return A.dist(C) <= R;
        }
    };

    Point middle(Point A, Point B) {
        A.x = (A.x + B.x) / 2.00;
        A.y = (A.y + B.y) / 2.00;

        return A;
    }

    vector<Point> process;
    vector<Point> sure;

    Circle solve() {
        if (sure.size() == 3 || process.size() == 0) {
            if (sure.size() < 2)
                return Circle(Point(0, 0), 0);

            if (sure.size() == 2) {
                Point aux = middle(sure[0], sure[1]);
                return Circle(aux, aux.dist(sure[0]));
            } else {
                Line one, two;
                one.from(sure[0], sure[1]);
                two.from(sure[1], sure[2]);

                one = one.perp(middle(sure[0], sure[1]));
                two = two.perp(middle(sure[1], sure[2]));

                Point aux = one.intersect(two);
                return Circle(aux, aux.dist(sure[0]));
            }
        }

        vector<Point> local = process;
        process.clear();

        Circle actual = solve();
        for (Point P : local) {
            if (actual.is_in(P) == false) {
                sure.pb(P);
                actual = solve();
                sure.pop_back();
            }

            process.pb(P);
        }

        return actual;
    }

    Circle minimum_circle(vector<Point> aux) {
        process = aux;
        random_shuffle(process.begin(), process.end());
        sure.clear();

        return solve();
    }
};

int main()
{
    freopen("*.in","r",stdin);
    freopen("*.out","w",stdout);




    return 0;
}
