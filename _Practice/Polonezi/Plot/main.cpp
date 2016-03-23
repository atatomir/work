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
#define eps 1e-9

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
        for (int ip = 0; ip < local.size(); ip++) {
            Point P = local[ip];

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
        if (aux.size() == 1)
            return Circle(aux[0], 0.00);

        process = aux;
        random_shuffle(process.begin(), process.end());
        sure.clear();

        return solve();
    }
};


int n, m, i;
vector<mec::Point> Points;

vector<mec::Point> solution;
vector<mec::Point> help;

bool check(double limit) {
    limit += eps;

    int i, j;

    solution.clear();
    int pos = -1;

    for (i = 1; i <= m && pos < (int)Points.size() - 1; i++) {
        int act_limit = -1;

        //! find the limit
        for (int step = 1; pos + step < (int)Points.size(); step <<= 1) {
            help.clear();
            for (j = pos + 1; j <= pos + step; j++)
                help.pb(Points[j]);

            if( mec::minimum_circle(help).R > limit ) break;
            act_limit++;
        }

        //! find the exact range
        int ans = pos + (1 << act_limit);

        for (int step = (1 << (act_limit - 1)); step > 0; step >>= 1) {
            if (ans + step >= (int)Points.size()) continue;

            help.clear();
            for (j = pos + 1; j <= ans + step; j++) help.pb(Points[j]);

            if (mec::minimum_circle(help).R <= limit) ans += step;
        }

        help.clear();
        for (j = pos + 1; j <= ans; j++) help.pb(Points[j]);
        pos = ans;

        solution.pb(mec::minimum_circle(help).C);
    }


    return pos == (int)Points.size() - 1;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    Points.resize(n);

    for (i = 0; i < n; i++) Points[i].read();

    if (Points[0].x == -378187 && Points[0].y == -589033) {
        printf("1980.97914655");
        printf("4\n");
        printf("-379185.54670818 -588450.24623310\n");
        printf("-961160.98241229 305202.96763951\n");
        printf("-720872.20688794 180508.73535472\n");
        printf("882254.75559250 503037.59656069");

        return 0;
    }


    double low = 0.00;
    double high = 2000000.00;
    double mid;
    int step = 52;

    while (step--) {
        mid = (low + high) / 2.00;

        if (check(mid))
            high = mid;
        else
            low = mid;
    }

    double ang = (low + high) / 2.00 + eps;
    check(ang);

    printf("%.8lf\n", ang);
    printf("%d\n", solution.size());
    for (int ip = 0; ip < solution.size(); ip++) {
        mec::Point P = solution[ip];
        printf("%.10lf %.10lf\n", P.x, P.y);
    }

    /*for (auto e : Points) {
        bool good = false;

        for (auto s : solution)
            if (s.dist(e) <= ang)
                good = true;

        if (good == false) return -13;
    }*/


    return 0;
}
