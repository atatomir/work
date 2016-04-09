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

#define maxN 1024
#define mpp(a, b, c) mp(a, mp(b, c))
#define eps 0.0000001

#define ang 0.00012
double act_sin = sin(ang);
double act_cos = cos(ang);


struct Point {
    double x, y;

    void rot() {
        double xx = x, yy = y;
        x = xx * act_cos - yy * act_sin;
        y = xx * act_sin + yy * act_cos;
    }
};

struct Line {
    double a, b, c;
    double tg;

    void from(Point A, Point B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(A.x * a + A.y * b);
    }

    Line through_point(Point A) {
        Line aux = *this;
        aux.c = -(A.x * aux.a + A.y * aux.b);
        return aux;
    }

    Line perpendicular() {
        Line aux = *this;
        if (a == 0 || b == 0) {
            swap(aux.a, aux.b);
            return aux;
        }

        aux.a = -aux.b / aux.a;
        aux.b = 1.00;
        return aux;
    }

    double compute_tg() {
        tg = -a/b;
        return tg;
    }

    bool operator<(const Line& who)const {
        return tg < who.tg;
    }
};

typedef pair<Line, pair<int, int> > Event;



int n, i, j;
Point P[maxN];
vector< Event > E;
Line aux;

int order[maxN];
int wh[maxN];
double ans = 0.00;


double distance_between(Point A, Point B, Line def) {
    Line aux1, aux2;

    aux1 = def.through_point(A);
    aux2 = def.through_point(B);

    double dist = (aux1.c - aux2.c) / sqrt( def.a * def.a + def.b * def.b );
    if (dist < 0) return -dist;
    return dist;
}

bool cmp(int a, int b) {
    if (P[a].x == P[b].x) return P[a].y < P[b].y;
    return P[a].x < P[b].x;


    /*double c1 = aux.through_point(P[a]).c;
    double c2 = aux.through_point(P[b]).c;

    return c1 < c2;*/
}

void test_line(int id) {
    if (id != 1) ans = max(ans, distance_between(P[ order[id - 1] ], P[ order[id] ], aux));
    if (id != n) ans = max(ans, distance_between(P[ order[id + 1] ], P[ order[id] ], aux));
}

void solve_events() {
    int i;

    for (auto e : E) {
        aux = e.first;
        int p1 = e.second.first;
        int p2 = e.second.second;

        if (p1 > 0) {
            //! change order
            if (wh[p1] > wh[p2]) swap(p1, p2);
            if (wh[p1] + 1 != wh[p2])
                cerr << "Error change " << p1 << ' ' << " with " << p2 << '\n';

            swap( wh[p1], wh[p2] );
            swap( order[ wh[p1] ], order[ wh[p2] ] );

            test_line(wh[p1]);
            test_line(wh[p2]);
        } else {
            //! just check
            p1 = -p1;

            if (wh[p1] > wh[p2]) swap(p1, p2);
            if (wh[p1] + 1 != wh[p2]) continue;

            ans = max(ans, distance_between(P[p1], P[p2], aux));
        }
    }

}


int main()
{
    freopen("culoar.in","r",stdin);
    freopen("culoar.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lf%lf", &P[i].x, &P[i].y);
        P[i].rot();
    }

    //! compute events
    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            //! chenge event
            aux.from(P[i], P[j]); aux.compute_tg();
            E.pb(mpp(aux, i, j));

            //! check event
            aux = aux.perpendicular(); aux.compute_tg();
            E.pb(mpp(aux, -i, j));
        }
    }

    sort(E.begin(), E.end());

    aux = E[0].first;

    for (i = 1; i <= n; i++) order[i] = i;
    sort(order + 1, order + n + 1, cmp);
    for (i = 1; i <= n; i++) wh[ order[i] ] = i;


    for (i = 2; i <= n; i++) ans = max(ans, distance_between(P[order[i - 1]], P[order[i]], aux));

    solve_events();
    printf("%.6lf", ans);


    return 0;
}
