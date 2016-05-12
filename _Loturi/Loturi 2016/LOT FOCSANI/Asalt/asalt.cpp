#include "header.h"
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

#define pb push_back
#define mp make_pair
#define ll long long
#define eps 0.000001
#define maxN 100011

typedef pair<double, double> Point;

const double PI = acos(-1);

int n, i;
Point P[maxN];
double ans_x[maxN], ans_y[maxN];

int base;


void result() {
    for (int i = 0; i < n; i++)
        ans_x[i] = P[i].first, ans_y[i] = P[i].second;
    sendRecovered(ans_x, ans_y);
}

bool equal(double x, double y) {
    return -eps < x - y && x - y < eps;
}

double dist(Point A, Point B) {
    return sqrt( (A.first - B.first) * (A.first - B.first) +
                 (A.second - B.second) * (A.second - B.second));
}

pair< Point, Point > get_intr(Point A, double d1, Point B, double d2) {
    //! A and B are on OX

    Point aux;
    double l = 0.00;
    double r = PI;
    double mid;
    int steps = 50;

    while (steps--) {
        mid = (l + r) / 2.00;
        aux = mp(cos(mid) * d1 , sin(mid) * d1);
        if (dist(aux, B) < d2)
            l = mid;
        else
            r = mid;
    }

    mid = (l + r) / 2.00;
    return mp(mp(cos(mid) * d1, sin(mid) * d1), mp(cos(-mid) * d1, sin(-mid) * d1));
}

pair< Point, Point > use_just(int id_a, int id_b, int id) {
    double d1 = query(id, id_a);
    double d2 = query(id, id_b);

    return get_intr(P[id_a], d1, P[id_b], d2);
}

Point get_best(int id, pair< Point, Point > poss, int base) {
    double d = query(base, id);

    if (equal(dist(poss.first, P[base]), d)) return poss.first;
    return poss.second;
}



void recover(int N) {
    n = N;

    //! indexat de la 0 !!!!!!!!
    if (n == 1) {result(); return;}

    P[1] = mp(query(0, 1), 0);

    if (n == 2) {result(); return;}

    P[2] = use_just(0, 1, 2).first;

    for (i = 3; i < n; i++) {
        auto act = use_just(0, 1, i);

        base = 2;
        while (i != base + 1 && equal(P[base].second, 0.00))
            base++;

        P[i] = get_best(i, act, base);
    }

    result();
}
