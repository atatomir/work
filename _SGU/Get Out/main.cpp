#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 333
#define eps 1e-6

struct Circle {
    double x, y, R;

    Circle() {}

    Circle(double _x, double _y, double _R) {
        x = _x;
        y = _y;
        R = _R;
    }
};

int n, i, j;
Circle C[maxN];
double x, y, R;
double def = acos(-1);

double dist[maxN];
vector< pair<int, double> > list[maxN];
int cnt[maxN];
queue< int > Q;



bool must_be_edge(Circle A, Circle B) {
    double dist = sqrt( (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y) ) ;
    return dist + eps <= A.R + B.R;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lf %lf %lf", &x, &y, &R);
        C[i] = Circle(x, y, R);
    }

    scanf("%lf %lf %lf", &x, &y, &R);
    for (i = 1; i <= n; i++) C[i].R += R;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (i == j) continue;

            if (must_be_edge(C[i], C[j])) {
                double ang = atan2(C[i].y - y, C[i].x - x) - atan2(C[j].y - y, C[j].x - x);

                if (ang < -def) ang += 2 * def;
                if (ang > def) ang -= 2 * def;

                list[i].pb(mp(j, ang));
            }
        }
    }

    for (i = 1; i <= n; i++) Q.push(i);

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();

        for (i = 0; i < list[node].size(); i++) {
            int to = list[node][i].first;
            double pay = list[node][i].second + dist[node];

            if (dist[to] - eps > pay) {
                dist[to] = pay;
                Q.push(to);

                if (++cnt[to] == n + 3) {
                    printf("NO");
                    return 0;
                }
            }
        }
    }

    printf("YES");


    return 0;
}
