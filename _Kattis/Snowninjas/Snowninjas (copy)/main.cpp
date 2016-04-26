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

struct Point {
    int x, y;

    bool operator<(const Point& who)const {
        return mp(x, y) < mp(who.x, who.y);
    }

    bool touch(const Point& who) {
        ll dist = (x - who.x) * (x - who.x) +
                  (y - who.y) * (y - who.y) ;
        return dist <= 10000;
    }
};


int n, i, t, ti, x, y;
vector<Point> P;
int dad[maxN];

vector< pair<int, int> > Event;
set< pair<Point, int> > S;
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
        Event.clear();
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
        for (i = 0; i < P.size(); i++) {
            Event.pb(mp(P[i].x - 100, i + 1));
            Event.pb(mp(P[i].x + 101, -i - 1));
        }
        sort(Event.begin(), Event.end());

        S.clear();
        for (auto e : Event) {
            Point p;

            if (e.second < 0) { //! remove
                p = P[-e.second - 1];
                swap(p.x, p.y);

                S.erase(mp(p, -e.second - 1));

            } else { //! add
                p = P[e.second - 1];
                swap(p.x, p.y);

                auto l = S.lower_bound({{p.x - 100, -100000}, -1});
                auto r = S.lower_bound({{p.x + 101, -100000}, -1});

                for (; l != r; l++) {
                    if (!p.touch(l->first)) continue;
                    Merge(e.second, l->second);
                }

                S.insert(mp(p, e.second));
            }
        }

        int need = Find(n);
        ans = 0.00;

        for (i = 1; i <= n; i++) {
            if (Find(i) != need) continue;
            double dist = 1.00 * P[i - 1].x * P[i - 1].x + 1.00 * P[i - 1].y * P[i - 1].y;
            ans = max(ans, sqrt(eps + dist));
        }

        printf("%d\n", int(floor(ans)));
    }


    return 0;
}
