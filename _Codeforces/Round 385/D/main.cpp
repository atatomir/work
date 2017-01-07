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

#define maxN 2048
#define eps 1e-7

const double PI = acos(-1);

struct point {
    double x, y;
    int tp;
};

int n, m, i;
point P[maxN];
vector<point> H;

vector< pair<double, int> > red, blue;
double pre_atan[maxN][maxN];
double pre_dist[maxN][maxN];


double det(point A, point B, point C) {
    B.x -= A.x;
    B.y -= A.y;

    C.x -= A.x;
    C.y -= A.y;

    return B.x * C.y - B.y * C.x;
}

double dist(point A, point B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

void Hull() {
    int sz, limit;

    sort(P + 1, P + n + 1, [](const point& a, const point& b)->bool const {
        return mp(a.x, a.y) < mp(b.x, b.y);
    });

    H.clear();
    for (i = 1; i <= n; i++) {

        while (H.size() >= 2) {
            sz = H.size() - 1;
            if (det(H[sz - 1], H[sz], P[i]) < eps) break;
            H.pop_back();
        }

        H.pb(P[i]);
    }

    limit = H.size() + 1;
    for (i = n - 1; i > 0; i--) {

        while (H.size() >= limit) {
            sz = H.size() - 1;
            if (det(H[sz - 1], H[sz], P[i]) < eps) break;
            H.pop_back();
        }

        H.pb(P[i]);
    }

    H.pop_back();
}

void pre() {
    int i, j;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (i != j) {
                pre_atan[i][j] = atan2(P[j].y - P[i].y, P[j].x - P[i].x);
                pre_dist[i][j] = dist(P[i], P[j]);
            }
        }
    }
}

bool check(double R) {
    int i, j, pos;
    double cossy, alfa, D, ang1, ang2, ang;
    point p;
    int act_red, act_blue;

    red.reserve(n);
    blue.reserve(n);

    for (i = 1; i <= n; i++) {
        //if (P[i].tp == 0 && n <= 10) continue;

        red.clear();
        blue.clear();
        act_red = (P[i].tp == 0);
        act_blue = 0;

        for (j = 1; j <= n; j++) {
            if (i == j) continue;

            p = P[j];
            D = pre_dist[i][j];

            if (D > 2 * R - eps) continue;

            cossy = D / (2.00 * R);
            alfa = acos(cossy);

            ang = pre_atan[i][j];
            ang1 = ang - alfa;
            ang2 = ang + alfa;

            if (p.tp == 0) {
                // red

                if (ang1 < -PI) {
                    ang1 += 2.00 * PI;
                    ang2 += 2.00 * PI;
                }

                if (ang2 > PI) {
                    red.pb(mp(ang1 + eps, +1));
                    red.pb(mp(ang2 - 2.00 * PI - eps, -1));
                    act_red++;
                    continue;
                }

                red.pb(mp(ang1 + eps, +1));
                red.pb(mp(ang2 - eps, -1));
            } else {
                // blue
                if (ang1 < -PI) {
                    ang1 += 2.00 * PI;
                    ang2 += 2.00 * PI;
                }

                if (ang2 > PI) {
                    blue.pb(mp(ang1 + eps, +1));
                    blue.pb(mp(ang2 - 2.00 * PI - eps, -1));
                    act_blue++;
                    continue;
                }

                blue.pb(mp(ang1 + eps, +1));
                blue.pb(mp(ang2 - eps, -1));
            }
        }

        // we need : act_red > 0 && act_blue == 0
        if (act_red > 0 && act_blue == 0)
            return true;

        sort(red.begin(), red.end());
        sort(blue.begin(), blue.end());
        red.pb(mp(5 * PI, 0));

        pos = 0;
        for (auto e : red) {
            while (pos < blue.size()) {
                if (blue[pos].first > e.first) break;
                act_blue += blue[pos].second;
                pos++;

                if (act_red > 0 && act_blue == 0)
                    return true;
            }

            act_red += e.second;
            if (act_red > 0 && act_blue == 0)
                return true;
        }
    }

    return false;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%lf%lf", &P[i].x, &P[i].y);
        P[i].tp = 0;
    }

    for (i = 1; i <= m; i++) {
        scanf("%lf%lf", &P[n + i].x, &P[n + i].y);
        P[n + i].tp = 1;
    }

    n += m;

    Hull();
    for (auto e : H) {
        if (e.tp == 0) {
            printf("-1");
            return 0;
        }
    }

    random_shuffle(P + 1, P + n + 1);
    pre();

    double l = 0.00;
    double r = 0.00;
    int step = 40;


    for (double bonus = 1; ; bonus *= 2) {
        r = bonus;
        if (!check(r)) break;
        l = bonus;
    }

    while (step-- && r - l > eps) {
        double mid = (l + r) / 2.00;

        if (check(mid))
            l = mid;
        else
            r = mid;
    }


    double ans = (l + r) / 2.00;


    printf("%.10lf", ans);


    return 0;
}
