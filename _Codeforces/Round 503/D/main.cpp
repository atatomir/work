#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int maxN = 2018;

struct point {
    ll x, y;
};

int n, i, j, k;
ll S, a, b, c, c2;
point P[maxN];

ll cross(point& A, point& B) {
    return A.x * B.y - A.y * B.x;
}

void give(int i, int j, int k) {
    ll c1 = cross(P[i], P[j]);
    ll c2 = cross(P[j], P[k]);
    ll c3 = cross(P[k], P[i]);

    if (c1 + c2 + c3 != S && c1 + c2 + c3 != -S) return;

    printf("Yes\n");
    printf("%lld %lld\n", P[i].x, P[i].y);
    printf("%lld %lld\n", P[j].x, P[j].y);
    printf("%lld %lld\n", P[k].x, P[k].y);
    exit(0);
}

int main()
{
    //freopen("test.in","r",stdin);
    time_t ini = clock();
    time_t act;
    double tm;

    srand(time(NULL));

    scanf("%d%lld", &n, &S);
    for (i = 1; i <= n; i++) scanf("%lld%lld", &P[i].x, &P[i].y);

    /*for (i = n + 1; i <= 2000; i++) {
        P[i].x = (rand() % 100000);
        P[i].y = (rand() % 100000);
    }
    n = 1000;*/

    random_shuffle(P + 1, P + n + 1);
    random_shuffle(P + 1, P + n + 1);
    random_shuffle(P + 1, P + n + 1);
    S <<= 1;

    for (i = 1; i <= n; i++) {
        act = clock();
        tm = (1.00 * act - ini) / CLOCKS_PER_SEC;
        if (tm >= 2.94) break;

        for (j = i + 1; j <= n; j++) {
            a = P[i].y - P[j].y;
            b = P[j].x - P[i].x;
            c = S - cross(P[i], P[j]);
            c2 = c - S - S;

            P[n + 1] = P[i];
            P[n + 2] = P[i];
            P[n + 3] = P[i];

            for (k = j + 1; k <= n; k += 4) {

                if (a * P[k].x + b * P[k].y == c) give(i, j, k);
                if (a * P[k + 1].x + b * P[k + 1].y == c) give(i, j, k + 1);
                if (a * P[k + 2].x + b * P[k + 2].y == c) give(i, j, k + 2);
                if (a * P[k + 3].x + b * P[k + 3].y == c) give(i, j, k + 3);

                if (a * P[k].x + b * P[k].y == c2) give(i, j, k);
                if (a * P[k + 1].x + b * P[k + 1].y == c2) give(i, j, k + 1);
                if (a * P[k + 2].x + b * P[k + 2].y == c2) give(i, j, k + 2);
                if (a * P[k + 3].x + b * P[k + 3].y == c2) give(i, j, k + 3);
            }
        }
    }

    printf("No");


    return 0;
}
