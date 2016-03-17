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
#define ll long long

#define maxN 777

struct min_window {
    deque< pair<int, int> > data;

    void init() {
        data.clear();
    }

    void operator<<(pair<int, int> act) {
        while (!data.empty()) {
            auto last = data.back();
            if (last.second < act.second) break;
            data.pop_back();
        }
        data.push_back(act);
    }

    void remove_until(int limit) {
        while (!data.empty()) {
            auto last = data.front();
            if (last.first >= limit) break;
            data.pop_front();
        }
    }

    pair<int, int> query() {
        return data.front();
    }
};

struct max_window {
    deque< pair<int, int> > data;

    void init() {
        data.clear();
    }

    void operator<<(pair<int, int> act) {
        while (!data.empty()) {
            auto last = data.back();
            if (last.second > act.second) break;
            data.pop_back();
        }
        data.push_back(act);
    }

    void remove_until(int limit) {
        while (!data.empty()) {
            auto last = data.front();
            if (last.first >= limit) break;
            data.pop_front();
        }
    }

    pair<int, int> query() {
        return data.front();
    }
};



int n, m, i, j, c;
int v[maxN][maxN];
int work_min[maxN][maxN];
int work_max[maxN][maxN];

int ans;
int xx1, yy1, xx2, yy2;

min_window wmin;
max_window wmax;

void compute_work(int limit) {
    int i, j;

    for (i = 1; i <= n; i++) {
        wmin.init();
        wmax.init();

        for (j = 1; j <= m; j++) {
            wmin << mp(j, v[i][j]);
            wmax << mp(j, v[i][j]);

            wmin.remove_until(j - limit + 1);
            wmax.remove_until(j - limit + 1);

            work_min[i][j] = wmin.query().second;
            work_max[i][j] = wmax.query().second;
        }
    }
}


void test_width(int limit) {
    int i, j;

    compute_work(limit);


    for (j = 1; j <= m; j++) {
        int dim_y = min(j, limit);

        wmin.init();
        wmax.init();

        int last = 1;

        for (i = 1; i <= n; i++) {
            wmin << mp(i, work_min[i][j]);
            wmax << mp(i, work_max[i][j]);

            while (wmax.query().second - wmin.query().second > c) {
                last = min(wmin.query().first, wmax.query().first) + 1;
                wmin.remove_until(last);
                wmax.remove_until(last);

                if (last > i) break;
            }

            int dim_x = i - last + 1;
            if (ans < dim_x * dim_y) {
                ans = dim_x * dim_y;

                xx2 = i;
                yy2 = j;

                xx1 = last;
                yy1 = max(1, j - limit + 1);
            }
        }
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%d", &m, &n, &c);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            scanf("%d", &v[i][j]);

    for (i = 1; i <= 100; i++)
        test_width(i);

    xx1 = n - xx1 + 1;
    xx2 = n - xx2 + 1;
    swap(xx1, xx2);


    printf("%d %d %d %d\n", yy1, xx1, yy2, xx2);
    cerr << ans;

    return 0;
}
