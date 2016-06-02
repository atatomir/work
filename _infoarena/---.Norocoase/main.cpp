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

#define maxN 100011
#define eps 0.0000001

typedef pair<int, int> Point;

Point diff(Point A, Point B) {
    A.first -= B.first;
    A.second -= B.second;
    return A;
}

ll prod(Point A, Point B) {
    return 1.00 * A.first * B.second - 1.00 * A.second * B.first;
}

double dist(Point A, Point P1, Point P2) {
    double area = prod(diff(P1, A), diff(P2, A));
    area /= sqrt( 1.00 * (P1.first - P2.first) * (P1.first - P2.first) +
                  1.00 * (P1.second - P2.second) * (P1.second - P2.second) );
    return (area > 0 ? area : -area);
}

int t, ti;
int n, i;
double W;
Point P[maxN << 1];
int ans;


void solve_edges() {
    int i, p1, p2;

    p1 = p2 = 1;
    for (i = 1; i <= n; i++) {
        while (dist(P[p1], P[i], P[i + 1])  > W) p1++;
        while (dist(P[p2 + 1], P[i], P[i + 1]) <= W && p2 - p1 + 2 <= n) p2++;
        ans = max(ans, p2 - p1 + 1);
    }
}

void solve_diagonal() {
    int i, j, mid;

    for (i = j = mid = 1; i <= n; i++) {
        j = max(j, i + 1);
        mid = max(mid, i + 1);

        while (j - i + 1 <= n) {
            while (dist(P[mid], P[i], P[j]) <= dist(P[mid + 1], P[i], P[j]) && mid + 1 <= j) mid++;
            if (dist(P[mid], P[i], P[j]) > W) break;
            ans = max(ans, j - i + 1);
            j++;
        }
    }
}

int main()
{
    freopen("norocoase.in","r",stdin);
    freopen("norocoase.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%lf", &n, &W);
        for (i = 1; i <= n; i++) scanf("%d%d", &P[i].first, &P[i].second), P[n + i] = P[i];

        ans = 1; W += eps;
        solve_edges();
        solve_diagonal();

        printf("%d\n", ans);
    }



    return 0;
}
