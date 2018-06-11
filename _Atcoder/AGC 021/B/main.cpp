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

#define maxN 111
#define H Hull

const double PI = acos(-1.00);

struct Point {
    ll x, y;
    int id;

    bool operator<(const Point & who)const {
        return mp(x, y) < mp(who.x, who.y);
    }
};

int n, i, limit;
Point P[maxN];
vector<Point> Hull;
pair<double, double> C;
double ans[maxN];

ll cross(Point A, Point B, Point C) {
    B.x -= A.x;
    B.y -= A.y;

    C.x -= A.x;
    C.y -= A.y;

    return B.x * C.y - B.y * C.x;
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++) cin >> P[i].x >> P[i].y, P[i].id = i;

    if (n == 2) {
        cout << 0.5 << '\n' << 0.5 << '\n';
        return 0;
    }

    sort(P + 1, P + n + 1);

    Hull.pb(P[1]);
    for (i = 2; i <= n; i++) {
        while (Hull.size() >= 2) {
            if (cross(Hull[Hull.size() - 2], Hull.back(), P[i]) <= 0) break;
            Hull.pop_back();
        }
        Hull.pb(P[i]);
    }

    limit = Hull.size();
    for (i = n - 1; i >= 1; i--) {
        while (Hull.size() > limit) {
            if (cross(Hull[Hull.size() - 2], Hull.back(), P[i]) <= 0) break;
            Hull.pop_back();
        }
        Hull.pb(P[i]);
    }

    for (i = 0; i + 1 < Hull.size(); i++) {
        C.first += Hull[i].x;
        C.second += Hull[i].y;
    }

    C.first /= Hull.size() - 1;
    C.second /= Hull.size() - 1;
    Hull.pb(Hull[1]);

    double sum = 0.00;

    for (i = 1; i + 1 < Hull.size(); i++) {
        /*double ang1 = atan2(Hull[i - 1].y - C.second, Hull[i - 1].x - C.first);
        double ang2 = atan2(Hull[i + 1].y - C.second, Hull[i + 1].x - C.first);

        double ang = ang1 - ang2;
        if (ang < 0) ang += 2.00 * PI;*/

        double ang1 = atan2(H[i].y - H[i - 1].y, H[i].x - H[i - 1].x);
        double ang2 = atan2(H[i].y - H[i + 1].y, H[i].x - H[i + 1].x);
        double ang = ang1 - ang2;
        if (ang < 0) ang = -ang;
        if (ang > PI) ang = 2.00 * PI - ang;
        ang = PI - ang;

        ans[Hull[i].id] = ang / (2.00 * PI);
        sum += ang;

        cerr << ang << ' ';
    }

    cerr << sum << '\n';

    for (i = 1; i <= n; i++)
        printf("%.20lf\n", ans[i]);





    return 0;
}
