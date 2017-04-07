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
#define eps 1e-9

const double PI = acos(-1);

struct Point {
    double x, y;
};

int n, i;
pair<Point, Point> S[maxN];
vector< pair<double, int> > event;

void add_interval(double p1, double p2) {
    if (p2 <= 0) {
        event.pb(mp(p1 - eps, +1));
        event.pb(mp(p2 + eps, -1));
    } else {
        if (p1 > 0) {
            event.pb(mp(p1 - PI - eps, +1));
            event.pb(mp(p2 - PI + eps, -1));
        } else {
            event.pb(mp(p1 - eps, +1));
            event.pb(mp(0 + eps, -1));

            event.pb(mp(0 - PI - eps, +1));
            event.pb(mp(p2 - PI + eps, -1));
        }
    }
}

void check(int id, Point P) {
    int i;
    double ang1, ang2;
    int act = 0;

    event.clear();

    for (i = 1; i <= n; i++) {
        if (id == i) continue;

        ang1 = atan2(S[i].first.y - P.y, S[i].first.x - P.x);
        ang2 = atan2(S[i].second.y - P.y, S[i].second.x - P.x);

        if (ang1 > ang2) swap(ang1, ang2);
        if (ang2 - ang1 < PI) {
            add_interval(ang1, ang2);
        } else {
            add_interval(-PI, ang1);
            add_interval(ang2, PI);
        }
    }

    sort(event.begin(), event.end());
    for (auto e : event) {
        act += e.second;

        if (act == n - 1) {
            printf("%.6lf %.6lf %.6lf %.6lf\n", P.x, P.y, P.x + 100000.00 * cos(PI + e.first), P.y + 100000.00 * sin(PI + e.first));
            exit(0);
        }
    }

}

int main()
{
    freopen("taie.in","r",stdin);
    freopen("taie.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        scanf("%lf%lf%lf%lf", &S[i].first.x, &S[i].first.y, &S[i].second.x, &S[i].second.y);

    for (i = 1; i <= n; i++) {
        check(i, S[i].first);
        check(i, S[i].second);
    }

    printf("-1");

    return 0;
}
