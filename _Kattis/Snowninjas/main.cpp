#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 700011
#define eps 0.000000001
#define def 30000
#define maxVal 2 * def + 11

struct Point {
    int x, y;

    bool operator<(const Point& who)const {
        return mp(x, y) < mp(who.x, who.y);
    }

    bool touch(const Point& who) {
        ll dist = 1LL * (x - who.x) * (x - who.x) +
                  1LL * (y - who.y) * (y - who.y) ;
        return dist <= 10000LL;
    }

    bool operator==(Point who) {
        return x == who.x && y == who.y;
    }
};


int n, i, t, ti, x, y;
vector<Point> P;
int dad[maxN];

pair< Point, int > hp[maxVal];
double ans;



int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

void Merge(int a, int b) {
    a = Find(a);
    b = Find(b);

    if (a != b) dad[b] = a;
}



int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        P.clear();

        scanf("%d", &n);
        for (i = 1; i <= n; i++) {
            scanf("%d%d", &x, &y);
            P.pb({x, y});
            dad[i] = i;
        }

        P.pb({0, 0});
        dad[++n] = n;

        sort(P.begin(), P.end());
        memset(hp, 0, sizeof(hp));

        int id = 0;
        for (auto p : P) {
                id++;

                int l = max(0, def + p.y - 100);
                int r = min(2 * def, def + p.y + 100);

                for (; l <= r; l++) {
                    if (hp[l].second == 0) continue;
                    if (!p.touch( hp[l].first )) continue;
                    Merge(id, hp[l].second);
                }

                hp[p.y + def] = mp(p, id);
        }

        int need = 0;
        ans = 0.00;

        Point src; src.x = src.y = 0;
        for (i = 1; i <= n; i++)
            if (P[i - 1] == src)
                need = Find(i);

        for (i = 1; i <= n; i++) {
            if (Find(i) != need) continue;
            double dist = 1.00 * P[i - 1].x * P[i - 1].x + 1.00 * P[i - 1].y * P[i - 1].y;
            ans = max(ans, sqrt(eps + dist));
        }

        printf("%d\n", int(floor(ans)));
    }


    return 0;
}
