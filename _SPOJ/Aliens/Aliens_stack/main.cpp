#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

struct Point {
    double x, y;

    Point() {}

    Point(double _x, double _y) {
        x = _x; y = _y;
    }

    void read() {
        scanf("%lf%lf", &x, &y);
    }

    double dist(Point who) {
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

    Line perpendicular(Point A) {
        Line ans = *this;

        if (ans.a != 0 && ans.b != 0) {
            //! no particular case
            ans.a = -b / a;
            ans.b = 1.00;
        } else {
            swap(ans.a, ans.b);
        }

        ans.c = -A.x * ans.a - A.y * ans.b;

        return ans;
    }

    Point intersect(Line who) {
        double sub = a * who.b - who.a * b;
        double sup1 = b * who.c - c * who.b;
        double sup2 = a * who.c - c * who.a;

        return Point(sup1 / sub, -sup2 / sub);
    }
};

struct Circle {
    double x, y, R;

    Circle() {}

    Circle(double _x, double _y, double _R) {
        x = _x; y = _y;
        R = _R;
    }

    bool is_in(Point P) {
        Point aux(x, y);

        return aux.dist(P) <= R;
    }
};




int t, n, i, ti;
vector<Point> Points;
vector<Point> process;
vector<Point> sure;


Circle last;
stack<int> states;
stack<Point> points_to_add;



Point middle(Point A, Point B) {
    A.x = (A.x + B.x) / 2.00;
    A.y = (A.y + B.y) / 2.00;

    return A;
}

void mec(int state) {
    Circle maybe;
    Point act;
    int pos;
    Circle ans;

    if (state == 1) goto between;
    if (state == 2) goto after;


    if (process.size() <= 1 && sure.empty()) {
        last = Circle(0.00, 0.00, 0.00);
        return;
    }

    if (process.empty() || sure.size() >= 3) {
        if (sure.size() < 2) {
            last = Circle(0.00, 0.00, 0.00);
            return;
        }

        if (sure.size() == 2) {
            //! diameter
            Point aux = middle(sure[0], sure[1]);

            last = Circle(aux.x, aux.y, aux.dist(sure[0]));
            return ;
        } else {
            //! other 3 points

            Line one, two;
            one.from(sure[0], sure[1]);
            two.from(sure[1], sure[2]);

            one = one.perpendicular( middle(sure[0], sure[1]) );
            two = two.perpendicular( middle(sure[1], sure[2]) );

            Point ans = one.intersect(two);
            last = Circle(ans.x, ans.y, ans.dist(sure[0]));
            return ;
        }
    }

    pos = rand() % process.size();
    swap(process[pos], process[ process.size() - 1 ]);

    act = process[ process.size() - 1 ];
    process.pop_back();

    points_to_add.push(act);
    states.push(1);
    states.push(0);

    return;
    //! -------------------------------------------------------
    between:

    act = points_to_add.top();

    maybe = last;
    process.pb( points_to_add.top() );
    points_to_add.pop();

    if (maybe.is_in(act)) {
        last = maybe;
        return;
    }

    points_to_add.push(act);
    sure.pb(act);
    states.push(2);
    states.push(0);

    return;

    //! -------------------------------------------------------
    after:

    sure.pop_back();
    process.pb( points_to_add.top() );
    points_to_add.pop();
}

Circle solve() {

    process = Points;
    sure = {};

    states.push(0);
    while (!states.empty()) {
        int st = states.top(); states.pop();
        mec(st);
    }

    return last;
}



int main()
{
    srand(time(NULL));

    //freopen("test.in","r",stdin);

    scanf("%d", &t);

    for (ti = 1; ti <= t; ti++) {
        Points.clear();

        scanf("%d", &n);
        Points.resize(n);
        for (i = 0; i < n; i++) Points[i].read();

        process = Points;
        Circle ans = solve();

        printf("%.2lf\n%.2lf %.2lf\n", ans.R, ans.x, ans.y);
    }


    return 0;
}
