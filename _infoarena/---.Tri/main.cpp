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

#define maxN 10011
#define eps 1e-9

class aib {
    public:
        void init(int _n) {
            n = _n;
            data = vector<int>(n + 5, 0);
        }

        void add(int pos) {
            while (pos <= n) {
                data[pos]++;
                pos += zrs(pos);
            }
        }

        int find_sum(int x) {
            int ans = 0;

            for (int step = 1 << 15; step > 0; step >>= 1)
                if (ans + step <= n)
                    if (data[ans + step] < x)
                        ans += step, x -= data[ans];

            return ans + 1;
        }

    private:
        int n;
        vector<int> data;

        int zrs(int x) {
            return (x & (x - 1)) ^ x;
        }
};

struct Point {
    double x, y;

    Point() {}

    template<typename T>
    Point(T _x, T _y) {
        x = _x; y = _y;
    }

    Point diff(Point & who) {
        return Point(x - who.x, y - who.y);
    }

    double cross(Point who) {
        return x * who.y - y * who.x;
    }
};

struct Line {
    double a, b, c;

    void from_points(Point& A, Point& B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(A.x * a + A.y * b);
    }

    Point intersect(Line &who) {
        double sub = a * who.b - who.a * b;
        Point ans;

        ans.x = (b * who.c - who.b * c) / sub;
        ans.y = (who.a * c - a * who.c) / sub;

        return ans;
    }
};

//! ^^^^^^^^^^^^ classes ^^^^^^^^^^^^^^^^^

int n, i, target, j;
Point A, B, C;
Point P[maxN];
double tg_a[maxN], tg_b[maxN], tg_c[maxN];
int ord_a[maxN];
int ord_b[maxN];
int ord_c[maxN];
int wh[maxN];

aib work;
Point keep[maxN][4];

int best;
Point ans_point;
vector<int> _help[3];
int us[maxN];

//! ^^^^^^^^^^^^  vars  ^^^^^^^^^^^^^^^^^^

bool cmp_a(int a, int b) {
    return tg_a[a] < tg_a[b];
}

bool cmp_b(int a, int b) {
    return tg_b[a] < tg_b[b];
}

bool cmp_c(int a, int b) {
    return tg_c[a] > tg_c[b];
}

//! ^^^^^^^^^^^^ cmp fct ^^^^^^^^^^^^^^^^^

int main()
{
    freopen("tri.in","r",stdin);
    freopen("tri.out","w",stdout);

    scanf("%lf %lf %lf %lf %lf %lf", &A.x, &A.y, &B.x, &B.y, &C.x, &C.y);
    scanf("%d", &n);
    target = n / 3;

    for (i = 1; i <= n; i++) {
        scanf("%lf %lf", &P[i].x, &P[i].y);
        tg_a[i] = atan2(P[i].y - A.y, P[i].x - A.x);
        tg_b[i] = atan2(P[i].y - B.y, P[i].x - B.x);
        tg_c[i] = atan2(P[i].y - C.y, P[i].x - C.x);

        ord_a[i] = ord_b[i] = ord_c[i] = i;
    }

    sort(ord_a + 1, ord_a + n + 1, cmp_a);
    sort(ord_b + 1, ord_b + n + 1, cmp_b);
    sort(ord_c + 1, ord_c + n + 1, cmp_c);

    //! from down to up (BC ^)
    work.init(n + 1);
    work.add(n + 1);

    for (i = 1; i <= n; i++)
        wh[ ord_c[i] ] = i;

    for (i = 1; i <= n; i++) {
        int id = ord_b[i];

        //! add to aib
        work.add( wh[id] );

        if (i < target) continue;

        //! find point one
        Line curr_line, aux_line;
        curr_line.from_points(B, P[id]);

        int id1 = ord_c[ work.find_sum(target) ];
        aux_line.from_points(C, P[id1]);

        keep[i][0] = curr_line.intersect(aux_line);

        //! find point two
        int id2 = ord_c[ min(n, work.find_sum(target + 1)) ];
        aux_line.from_points(C, P[id2]);

        keep[i][1] = curr_line.intersect(aux_line);
    }

    //! from up to down (BA \/)
    work.init(n + 1);
    work.add(n + 1);

    for (i = 1; i <= n; i++)
        wh[ ord_a[i] ] = i;

    for (i = n; i >= 1; i--) {
        int id = ord_b[i];

        if (n - i + 1 < target) {
            work.add( wh[id] );
            continue;
        }

        //! find point one
        Line curr_line, aux_line;
        curr_line.from_points(B, P[id]);

        int id1 = ord_a[ work.find_sum(target) ];
        aux_line.from_points(A, P[id1]);

        keep[i][2] = curr_line.intersect(aux_line);

        //! find point two
        int id2 = ord_a[ min(n, work.find_sum(target + 1)) ];
        aux_line.from_points(A, P[id2]);

        keep[i][3] = curr_line.intersect(aux_line);

        //! add to aib
        work.add( wh[id] );
    }

    //! now check if there are any solutions
    bool found = false;
    for (int i = target; i <= n - target + 1; i++) {
        if (keep[i][0].x > keep[i][2].x) {
            swap(keep[i][0], keep[i][2]);
            swap(keep[i][1], keep[i][3]);
        }

        if (keep[i][1].x > keep[i][2].x + eps) {
            //! soltion found
            found = true;

            ans_point = keep[i][2];
            best = i;

            break;
        }
    }

    if (!found) {
        printf("Solution not found!");
        while (true) {}
        return 0;
    }

    //! compute _help[0] - repeat from down to up (BC ^)
    work.init(n + 1);
    work.add(n + 1);

    for (i = 1; i <= n; i++)
        wh[ ord_c[i] ] = i;

    for (i = 1; i <= n; i++) {
        int id = ord_b[i];

        //! add to aib
        work.add( wh[id] );

        if (i == best) {
            for (j = 1; j <= target; j++) {
                int pos = ord_c[work.find_sum(j)];
                us[pos] = 1;
                _help[0].pb(pos);
            }

            break;
        }
    }

    //! compute _help[1]
    for (i = 1; i <= n && target; i++) {
        int pos = ord_a[i];
        if (us[pos] == 0) {
            us[pos] = 2;
            _help[1].pb(pos);
            target--;
        }
    }

    //! compute _help[2]
    for (i = 1; i <= n; i++)
        if (us[i] == 0)
            _help[2].pb(i);

    printf("%.10lf %.10lf\n", ans_point.x, ans_point.y);
    for (auto e : _help[0])
        printf("%.0lf %.0lf ", P[e].x, P[e].y);
    printf("\n");
    for (auto e : _help[1])
        printf("%.0lf %.0lf ", P[e].x, P[e].y);
    printf("\n");
    for (auto e : _help[2])
        printf("%.0lf %.0lf ", P[e].x, P[e].y);
    printf("\n");

    return 0;
}
