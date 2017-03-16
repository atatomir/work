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

#define maxN 50011
#define eps 1e-6

bool Equal(double a, double b) {
    a -= b;
    return -eps <= a && a <= eps;
}

struct Point {
    double x, y;

    Point operator-(Point who) {
        return {x - who.x, y - who.y};
    }

    bool operator==(const Point P) {
        return Equal(x, P.x) && Equal(y, P.y);
    }
};



int n, i, j, pos;
Point P[maxN], aux[maxN], Q, Q2;
double area;
bool incr;

Point sol1, sol2;

double cross(Point A, Point B) {
    return A.x * B.y - A.y * B.x;
}

void add_point(Point Q) {
    int i, j, cnt;
    P[n + 1] = P[1];

    for (i = 1; i <= n; i++) {
        if (Equal(0.00, cross(P[i] - Q, P[i + 1] - Q))) {
            memcpy(aux, P, sizeof(P));

            cnt = 1;
            P[1] = Q;
            for (j = i + 1; j <= n; j++) P[++cnt] = aux[j];
            for (j = 1; j <= i; j++) P[++cnt] = aux[j];
            n = cnt;
            break;
        }
    }
}

Point get_mid(Point Q, int sz, Point *from, double need) {
    double act = cross(Q, from[1]);
    double aux;
    int i, p1, p2;

    for (i = 2; i <= n; i++) {
        act += cross(from[i - 1], from[i]);
        aux = abs(act + cross(from[i], Q));
        if (aux > need - eps) break;
    }

    p1 = i - 1;
    p2 = i;
    act -= cross(from[p1], from[p2]);

    Point P;
    double mid;
    double l = 0.00;
    double r = 1.00;
    int steps = 25;

    while (steps--) {
        mid = (l + r) / 2.00;

        P.x = from[p1].x + mid * (from[p2].x - from[p1].x);
        P.y = from[p1].y + mid * (from[p2].y - from[p1].y);

        aux = act + cross(from[p1], P) + cross(P, Q);
        aux = abs(aux);

        if (aux < need)
            l = mid;
        else
            r = mid;
    }

    mid = (l + r) / 2.00;
    P.x = from[p1].x + mid * (from[p2].x - from[p1].x);
    P.y = from[p1].y + mid * (from[p2].y - from[p1].y);

    return P;
}

double check(Point act) {
    P[n + 1] = P[1];
    Point p1 = get_mid(act, pos, P, area / 4);
    Point p2 = get_mid(act, n - pos + 2, P + pos - 1, area / 4);

    sol1 = p1;
    sol2 = p2;

    return cross(p1 - act, p2 - act);
}

void print_line(Point A, Point B) {
    double a = B.y - A.y;
    double b = A.x - B.x;
    double c = -(a * A.x + b * A.y);

    printf("%.9lf %.9lf %.9lf ", a, b, c);
}

int main()
{
    freopen("split3.in","r",stdin);
    freopen("split3.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%lf%lf", &P[i].x, &P[i].y);
    scanf("%lf%lf", &Q.x, &Q.y);

    area = cross(P[n], P[1]);
    for (i = 1; i < n; i++) area += cross(P[i], P[i + 1]);
    area = abs(area);

    add_point(Q);
    Q2 = get_mid(Q, n - 1, P + 1, area / 2);
    add_point(Q2);

    for (pos = 1; !(P[pos] == Q); pos++);

    if (check(Q2) < check(Q))
        incr = true;
    else
        incr = false;


    Point act;
    double mid;
    double l = 0;
    double r = 1.00;
    int steps = 30;

    while (steps--) {
        mid = (l + r) / 2.00;
        act.x = Q2.x + mid * (Q.x - Q2.x);
        act.y = Q2.y + mid * (Q.y - Q2.y);

        if (check(act) < 0.00) {
            if (incr)
                l = mid;
            else
                r = mid;
        } else {
            if (!incr)
                l = mid;
            else
                r = mid;
        }
    }

    mid = (l + r) / 2.00;
    act.x = Q2.x + mid * (Q.x - Q2.x);
    act.y = Q2.y + mid * (Q.y - Q2.y);
    cerr << check(act);

    print_line(Q, Q2);
    print_line(sol1, sol2);



    return 0;
}
