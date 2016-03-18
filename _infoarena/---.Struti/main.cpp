#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <assert.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 1024

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 2);
            refill();
        }

        Buffer& operator>>(int &dest) {
            while (!is_digit(data[pos]))
                if (++pos == dim)
                    refill();
            dest = 0;
            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }

            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        bool is_digit(char c) {
            return '0' <= c && c <= '9';
        }

        void refill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }
};
Buffer fin("struti.in", 1 << 20);

struct min_window {
    deque< pair<int, int> > data;

    void init() { data.clear(); }

    void operator<<(pair<int, int> act) {
        while (!data.empty()) {
            if (data.back().second < act.second) break;
            data.pop_back();
        }
        data.push_back(act);
    }

    void remove_until(int limit) {
        if (!data.empty()) {
            if (data.front().first < limit) data.pop_front();
        }
    }

    pair<int, int> query() {
        assert(data.empty() == false);
        return data.front();
    }
};

struct max_window {
    deque< pair<int, int> > data;

    void init() { data.clear(); }

    void operator<<(pair<int, int> act) {
        while (!data.empty()) {
            if (data.back().second > act.second) break;
            data.pop_back();
        }
        data.push_back(act);
    }

    void remove_until(int limit) {
        if (!data.empty()) {
            if (data.front().first < limit) data.pop_front();
        }
    }

    pair<int, int> query() {
        assert(data.empty() == false);
        return data.front();
    }
};





int n, m, i, j, p, dx, dy;
int mat[maxN][maxN];
int min_work[maxN][maxN], max_work[maxN][maxN];
min_window wmin;
max_window wmax;


pair<int, int> solve() {
    int i, j;
    int ans = 8001;
    int cnt = 0;

    for (i = 1; i <= n; i++) {
        wmin.init();
        wmax.init();

        for (j = 1; j <= m; j++) {
            wmin << mp(j, mat[i][j]);
            wmax << mp(j, mat[i][j]);

            wmin.remove_until(j - dy + 1);
            wmax.remove_until(j - dy + 1);

            min_work[i][j] = wmin.query().second;
            max_work[i][j] = wmax.query().second;
        }
    }

    for (j = dy; j <= m; j++) {
        wmin.init();
        wmax.init();

        for (i = 1; i <= n; i++) {
            wmin << mp(i, min_work[i][j]);
            wmax << mp(i, max_work[i][j]);

            wmin.remove_until(i - dx + 1);
            wmax.remove_until(i - dx + 1);

            if (i >= dx) {
                int aux =  wmax.query().second - wmin.query().second;

                if (aux < ans) {
                    ans = aux;
                    cnt = 0;
                }

                if (aux == ans)
                    cnt++;
            }
        }
    }



    return mp(ans, cnt);
}


int main()
{
    //freopen("struti.in","r",stdin);
    freopen("struti.out","w",stdout);

    fin >> n >> m >> p;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            fin >> mat[i][j];

    for (i = 1; i <= p; i++) {
        fin >> dx >> dy;

        auto ans1 = solve();
        auto ans2 = mp(8001, 0);

        if (dx != dy) {
            swap(dx, dy);
            ans2 = solve();
        }

        if (ans1.first > ans2.first) swap(ans1, ans2);
        if (ans1.first == ans2.first)
            ans1.second += ans2.second;

        printf("%d %d\n", ans1.first, ans1.second);
    }


    return 0;
}
