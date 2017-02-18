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
#define eps 1e-17

struct frac {
    ll a, b;

    bool operator<(const frac& who)const {
        return a * who.b < b * who.a;
    }

    bool operator==(const frac& who)const {
        return a * who.b == b * who.a;
    }

    bool operator<=(const frac& who)const {
        return a * who.b <= b * who.a;
    }

};

struct point {
    frac x, y;
    int id;

    bool operator<(const point& who)const {
        return mp(x, y) < mp(who.x, who.y);
    }
};

int n, i, j, k, x, y;
vector< point > v, aux;

bool good[maxN];
vector<int> sol;

double cross(point A, point B, point C) {
    double ax = 1.00 * A.x.a / A.x.b;
    double ay = 1.00 * A.y.a / A.y.b;

    double bx = 1.00 * B.x.a / B.x.b;
    double by = 1.00 * B.y.a / B.y.b;

    double cx = 1.00 * C.x.a / C.x.b;
    double cy = 1.00 * C.y.a / C.y.b;

    bx -= ax;
    by -= ay;

    cx -= ax;
    cy -= ay;

    return bx * cy - by * cx;
}

int main()
{
    freopen("biathlon.in","r",stdin);
    freopen("biathlon.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        good[i] = true;
        scanf("%d%d", &x, &y);
        v.pb((point){(frac){x, 1}, (frac){y, 1}, i});
    }

    sort(v.begin(), v.end());
    for (i = 0; i < v.size(); i = j) {
        for (j = i; j < v.size(); j++)
            if (!(v[i].x == v[j].x && v[i].y == v[j].y))
                break;

        if (j - i > 1)
            for (k = i; k < j; k++)
                good[v[k].id] = false;

        while (!aux.empty()) {
            if (aux.back().y <= v[i].y) {
                good[aux.back().id] = false;
                aux.pop_back();
            } else {
                break;
            }
        }

        aux.pb(v[i]);
    }

    v = aux;
    for (auto& e : v) {
        swap(e.x.a, e.x.b);
        swap(e.y.a, e.y.b);
    }

    sort(v.begin(), v.end());

    aux.clear();
    for (auto e : v) {
        while (aux.size() >= 2) {
            auto p1 = aux[aux.size() - 2];
            auto p2 = aux[aux.size() - 1];

            if (cross(p1, p2, e) > 0) break;
            good[aux.back().id] = false;
            aux.pop_back();
        }

        aux.pb(e);
    }


    for (i = 1; i <= n; i++) {
        if (good[i]) {
            sol.pb(i);
            printf("%d ", i - 1);
        }
    }

    if (sol.empty())
        printf("-1");



    return 0;
}
