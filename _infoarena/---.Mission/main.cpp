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

const double PI = acos(-1.00);

struct point {
    int x, y;
    int id;
    double ang;

    bool operator<(const point& who)const {
        double dif = abs(ang - who.ang);

        if (dif > 1.00)
            return ang < who.ang;

        return 1LL * x * who.y - 1LL * y * who.x > 0LL;
    }
};

int n, i, j;
point P[maxN];

int main()
{
    freopen("mission.in","r",stdin);
    freopen("mission.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &P[i].x, &P[i].y), P[i].id = i - 1;
        if (i != 1) {
            P[i].x -= P[1].x;
            P[i].y -= P[1].y;
            P[i].ang = atan2(P[i].y, P[i].x);
        }
    }

    sort(P + 2, P + n + 1);
    for (i = 2; i + 1 <= n; i++) {
        if (P[i + 1].ang - P[i].ang > PI) {
            printf("0 ");
            for (j = i + 1; j <= n; j++) printf("%d ", P[j].id);
            for (j = 2; j <= i; j++) printf("%d ", P[j].id);
            return 0;
        }
    }

    for (i = 1; i <= n; i++)
        printf("%d ", P[i].id);

    return 0;
}
