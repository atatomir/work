#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 333
#define PI 3.1416
#define inf 1e80
#define ll long long

class aib {
    public:
        void init(int _n) {
            n = _n;
            data  = vector<int>(n, 0);
        }

        void renew() {
            memset(&data[0], 0, sizeof(int) * n );
        }

        void add(int pos) {
            while (pos < n) {
                data[pos]++;
                pos += zrs(pos);
            }
        }

        int sum(int pos) {
            int ans = 0;
            while (pos > 0) {
                ans += data[pos];
                pos -= zrs(pos);
            }
            return ans;
        }

        int intr_sum(int a, int b) {
            return sum(b) - sum(a - 1);
        }

    private:
        int n;
        vector<int> data;

        int zrs(int x) {
            return (x & (x - 1)) ^ x;
        }
};

struct Point {
    int x, y;

    Point() {}
    Point(int _x, int _y) {
        x = _x; y = _y;
    }

    void read() {
        scanf("%d%d", &x, &y);
        x += 7; y += 13;
    }

    double cross(Point& who) {
        return 1.00 * x * who.y - 1.00 * y * who.x;
    }

    Point operator-(Point who) {
        return Point(x - who.x, y - who.y);
    }
};

int n, k, i;
Point P[maxN];

int how[maxN][maxN]; //! nr de pct in triunghiul OAB
double min_area[maxN]; //! aria minima cu x pct
double area_all[maxN]; //! aria temporara pt fiecare pct
double ans = 2 * inf;

//! ----------- used by preproc --------------

double ang_orig[maxN];
int sort_orig[maxN];
int id_sort_orig[maxN];

int cnt;
double ang_tmp[maxN];
int sort_tmp[maxN];

aib work;

//! ------------------------------------------

bool ang_orig_sort(int a, int b) {
    return ang_orig[a] < ang_orig[b];
}

bool ang_tmp_sort(int a, int b) {
    return ang_tmp[a] > ang_tmp[b];
}

void preproc() {
    int i, j;

    //! sortez dupa origine
    for (i = 1; i <= n; i++) {
        sort_orig[i] = i;
        ang_orig[i] = atan2( P[i].y, P[i].x );
    }
    sort(sort_orig + 1, sort_orig + n + 1, ang_orig_sort);
    for (i = 1; i <= n; i++)
        id_sort_orig[sort_orig[i]] = i;

    //! imi selectez pct cu unghiul cel mai mic
    work.init(n);
    for (i = 1; i < n; i++) {
        work.renew();

        //! sortez descrescator dupa punctul selectat
        cnt = n - i;
        for (j = 1; j <= cnt; j++) {
            sort_tmp[j] = sort_orig[i + j];
            ang_tmp[ sort_tmp[j] ] = atan2(P[ sort_tmp[j] ].y - P[ sort_orig[i] ].y, P[ sort_tmp[j] ].x - P[ sort_orig[i] ].x);

            if (ang_tmp[ sort_tmp[j] ] < 0.00)
                ang_tmp[ sort_tmp[j] ] += 2 * PI;
        }
        sort(sort_tmp + 1, sort_tmp + cnt + 1, ang_tmp_sort);

        //! parcurg punctele in ordine (descrescatore) dupa unghiul format cu pct selectat
        for (j = 1; j <= cnt; j++) {
            int wh = id_sort_orig[ sort_tmp[j] ];

            //! calculez how pt i si sort_tmp[j]
            how[ sort_orig[i] ][ sort_tmp[j] ] = work.intr_sum(i, wh) ;
            how[ sort_tmp[j] ][ sort_orig[i] ] = -how[ sort_orig[i] ][ sort_tmp[j] ] ;

            //! adaug pct in aib
            work.add(wh);
        }
    }

}

int sgn(int x) {
    if (x > 0)
        return +1;
    if (x < 0)
        return -1;
    return 0;
}

int how_many_points(int id1, int id2, int id3) {
    int ans = 0;

    ans += how[id1][id2] ;
    ans += how[id2][id3] ;
    ans += how[id3][id1] ;

    int base = sgn(ans);
    ans *= base;

    if (base == 0)
        return 0;

    if (sgn(P[id1].cross(P[id2])) != base) ans--;
    if (sgn(P[id2].cross(P[id3])) != base) ans--;
    if (sgn(P[id3].cross(P[id1])) != base) ans--;
    ans++;

    return ans;
}

void solve() {
    int i, j, t;

    for (i = 1; i < n; i++) {
        for (j = i + 1; j <= n; j++) {
            //! am ales diagonala
            Point A = P[j] - P[i];

            //! adaug in min_area triungiurile care au cross > 0
            for (t = 0; t <= n; t++)
                min_area[t] = inf;
            for (t = 1; t <= n; t++) {
                Point B = P[t] - P[i];
                area_all[t] = A.cross(B);

                int how_many = how_many_points(i, j, t);

                if (area_all[t] > 0)
                    min_area[ how_many ] = min(min_area[ how_many ], area_all[t]);
            }

            //! minime partiale
            for (t = n - 1; t >= 0; t--)
                min_area[t] = min(min_area[t], min_area[t + 1]);

            //! combin cele 2 triunghiuri
            for (t = 1; t <= n; t++) {
                int how_many = how_many_points(i, j, t);

                if (area_all[t] < 0) {
                    double ans_tmp = -area_all[t] + min_area[ max(0, k - how_many) ];
                    ans = min(ans, ans_tmp);
                }
            }
        }
    }
}

int main()
{
    freopen("popandai.in","r",stdin);
    freopen("popandai.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++)
        P[i].read();

    preproc();
    solve();

    printf("%.1lf", ans / 2);


    return 0;
}
