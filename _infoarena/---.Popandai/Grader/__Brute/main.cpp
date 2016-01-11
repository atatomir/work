#include <algorithm>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

typedef long long i64;

const int Nmax = 305;

struct Point {
    int x, y;

    Point() {}
    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }
};

Point points[Nmax];
int under[Nmax][Nmax];
i64 mina[Nmax];

template<class type>
inline type mabs(type n) {
    return n < 0 ? -n: n;
}

i64 det(const Point& o, const Point &a, const Point &b) {
    return 1LL * (a.x - o.x) * (b.y - o.y) - 1LL * (b.x - o.x) * (a.y - o.y);
}

int main()
{
    freopen("popandai.in", "r", stdin);
    freopen("popandai.ok", "w", stdout);

    int N, K;
    scanf("%d%d", &N, &K);

    for (int i = 1; i <= N; ++i) {
        scanf("%d%d", &points[i].x, &points[i].y);
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            Point a = points[i], b = points[j];
            if (a.x > b.x)
                swap(a, b);

            int count = 0;
            for (int k = 1; k <= N; ++k) {
                if (k == j || k == i)
                    continue;

                Point c = points[k];
                if (c.x >= a.x && c.x < b.x && det(c, a, b) < 0)
                    ++count;
            }

            under[i][j] = under[j][i] = count;
        }
    }

    i64 ans = 1e18;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            memset(mina, 0x3f3f3f3f, sizeof mina);

            for (int k = 1; k <= N; ++k) {
                if (k == j || k == i)
                    continue;

                int a = i, b = j, c = k;

                if (det(points[c], points[a], points[b]) < 0)
                    continue;

                if (points[c].x < points[a].x)
                    swap(a, c);
                if (points[b].x < points[a].x)
                    swap(a, b);
                if (points[b].x < points[c].x)
                    swap(b, c);
                if (points[a].x == points[c].x && points[a].y < points[c].y)
                    swap(a, c);
                if (points[b].x == points[c].x && points[b].y > points[c].y)
                    swap(b, c);

                int cnt = det(points[c], points[a], points[b]) > 0 ? (under[a][c] + under[c][b] - under[a][b]): (under[a][b] - under[a][c] - under[c][b] - 1);
                i64 area = mabs(det(points[a], points[b], points[c]));
                mina[cnt] = min(mina[cnt], area);

                //assert(area > 0);
            }

            for (int i = N - 1; i >= 0; --i)
                mina[i] = min(mina[i], mina[i + 1]);

            for (int k = 1; k <= N; ++k) {
                if (k == j || k == i)
                    continue;

                int a = i, b = j, c = k;

                if (det(points[c], points[a], points[b]) > 0)
                    continue;

                if (points[c].x < points[a].x)
                    swap(a, c);
                if (points[b].x < points[a].x)
                    swap(a, b);
                if (points[b].x < points[c].x)
                    swap(b, c);
                if (points[a].x == points[c].x && points[a].y < points[c].y)
                    swap(a, c);
                if (points[b].x == points[c].x && points[b].y > points[c].y)
                    swap(b, c);

                int cnt = det(points[c], points[a], points[b]) > 0 ? (under[a][c] + under[c][b] - under[a][b]): (under[a][b] - under[a][c] - under[c][b] - 1);
                i64 area = mabs(det(points[a], points[b], points[c]));
                ans = min(ans, mina[max(0, K - cnt)] + area);

                //assert(ans > 0);
            }
        }
    }

    /*for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cout << under[i][j] << ' ';
        }
        cout << '\n';
    }*/

    cout << setprecision(1) << fixed;
    cout << (double) ans / 2.0 << '\n';
}
