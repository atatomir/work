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

#define maxN 50011
#define inf 1e18

struct Segm {
    int _x1, _x2, _y1, _y2;
    double a, b;

    void read() {
        scanf("%d%d%d%d", &_x1, &_y1, &_x2, &_y2);

        if (_x1 > _x2) {
            swap(_x1, _x2);
            swap(_y1, _y2);
        }

        if (_x1 == _x2) {
            a = 2.00 * inf;
            b = 0;
            return;
        }

        a = 1.00 * (_y2 - _y1) / (1.00*(_x2 - _x1));
        b = 1.00 * _y1 - 1.00 * a * _x1;
    }
};

int n, i, j;
Segm work[maxN];
vector<int> list[maxN];
int gr[maxN];

queue<int> Q;


int getCommon(int a, int b) {
    if (work[a]._x1 > work[b]._x1) swap(a, b);

    if (work[a]._x2 < work[b]._x1) return -1;

    return work[b]._x1 ;
}

bool isUp(int a, int b, double common) {
    if (work[a].a >= inf && work[b].a >= inf)
        return work[a]._y1  > work[b]._y1;
    if (work[a].a >= inf) {
        double posY = work[b].a * common + work[b].b;
        return 1.00 * work[a]._y1 > posY;
    }
    if (work[b].a >= inf) {
        double posY = work[a].a * common + work[a].b;
        return posY > 1.00 * work[b]._y1;
    }

    double posY1 = work[a].a * common + work[a].b;
    double posY2 = work[b].a * common + work[b].b;
    return posY1 > posY2;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) work[i].read();

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {

            int common = getCommon(i, j);
            if (common == -1) continue;

            if (isUp(i, j, common)) { //! i e deasupra
                list[j].pb(i);
                gr[i]++;

                //cerr << j << ' ' << i << '\n';
            } else {  //! j e deasupra
                list[i].pb(j);
                gr[j]++;

                //cerr << i << ' ' << j << '\n';
            }
        }
    }

    for (i = 1; i <= n; i++)
        if (gr[i] == 0)
            Q.push(i);

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();

        printf("%d ", node);
        for (auto to : list[node]) {
            if (--gr[to] == 0)
                Q.push(to);
        }
    }


    return 0;
}
