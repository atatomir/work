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

#define maxN 10011
#define lf double

int n, q, i, id, ang, planet, _time;
lf xx[360][maxN], yy[360][maxN];
int dad[maxN];
vector<int> son[maxN];
vector<int> boss;

lf PI = acos(-1.00);
lf real_ang;
lf now_cos, now_sin;


pair<lf, lf> get_rotation(int P, int O, double aux_ang) {
    now_cos = cos(aux_ang);
    now_sin = sin(aux_ang);

    lf _x = xx[0][P] - xx[0][O];
    lf _y = yy[0][P] - yy[0][O];

    lf __x = now_cos * _x - now_sin * _y;
    lf __y = now_sin * _x + now_cos * _y;

    return mp(__x, __y);
}

void solve(int node, double aux_ang) {
    auto now = get_rotation(node, dad[node], aux_ang);
    xx[ang][node] = xx[ang][ dad[node] ] + now.first;
    yy[ang][node] = yy[ang][ dad[node] ] + now.second;

    for (auto to : son[node])
        solve(to, aux_ang + real_ang);
}

int main()
{
    freopen("cercetatori.in","r",stdin);
    freopen("cercetatori.out","w",stdout);

    scanf("%d%d", &n, &q);
    for (i = 1; i <= n; i++) {
        scanf("%d", &id);
        scanf("%d%lf%lf", &dad[id], &xx[0][id], &yy[0][id]);
        son[ dad[id] ].pb(id);

        if (dad[id] == 0) boss.pb(i);
    }

    for (ang = 1; ang < 360; ang++) {
        if (ang == 90) {
            ang--;
            ang++;
        }

        for (auto bossi : boss) {
            xx[ang][bossi] = xx[0][bossi];
            yy[ang][bossi] = yy[0][bossi];

            real_ang = (1.00 * ang / 360.00) * 2 *  PI;

            for (auto to : son[bossi])
                solve(to, real_ang);
        }
    }

    for (i = 1; i <= q; i++) {
        scanf("%d%d", &planet, &_time);

        _time %= 360;
        printf("%.6lf %.6lf\n", xx[_time][planet], yy[_time][planet]);
    }


    return 0;
}
