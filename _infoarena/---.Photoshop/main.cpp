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

#define lSon (node << 1)
#define rSon (lSon | 1)

#define maxN 100011
#define inf 1000000000

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 10);
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

        void refill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }

        bool is_digit(char c) {
            return '0' <= c && c <= '9';
        }
};

Buffer fin("photoshop.in", 1 << 20);

class Tree2d {
    public:
        void init(int _n, multiset<int>* _cont_data) {
            n = _n;
            data = _cont_data;

            init_tree(1, 1, n);
        }

        void update(int node, int l, int r, int pos, int h, int v) {
            if(v == -1) {
                auto it = data[node].find(h);
                data[node].erase(it);
            } else {
                data[node].insert(h);
            }

            if (l == r) return;

            int mid = (l + r) >> 1;
            if (pos <= mid)
                update(lSon, l, mid, pos, h, v);
            else
                update(rSon, mid + 1, r, pos, h, v);
        }

        int min_query(int node, int l, int r, int qL, int qR, int h) {
            if (qL <= l && r <= qR) {
                if (data[node].empty()) return inf;

                auto it = data[node].lower_bound(h);
                if (it == data[node].end()) return inf;

                return *it;
            }

            int ans = inf;

            int mid = (l + r) >> 1;
            if (qL <= mid)
                ans = min(ans, min_query(lSon, l, mid, qL, qR, h));
            if (qR >  mid)
                ans = min(ans, min_query(rSon, mid + 1, r, qL, qR, h));

            return ans;
        }

        int max_query(int node, int l, int r, int qL, int qR, int h) {
            if (qL <= l && r <= qR) {
                if (data[node].empty()) return -inf;

                auto it = data[node].upper_bound(h);
                if (it == data[node].begin()) return -inf;

                it--;
                return *it;
            }

            int ans = -inf;

            int mid = (l + r) >> 1;
            if (qL <= mid)
                ans = max(ans, max_query(lSon, l, mid, qL, qR, h));
            if (qR >  mid)
                ans = max(ans, max_query(rSon, mid + 1, r, qL, qR, h));

            return ans;
        }

    private:
        int n;
        multiset<int> *data;

        void init_tree(int node, int l, int r) {
            data[node].clear();
            if (l == r) {
                return;
            }

            int mid = (l + r) >> 1;
            init_tree(lSon, l, mid);
            init_tree(rSon, mid + 1, r);
        }

};

struct op {
    int type;
    int a, b, c, d;

    void read() {
        fin >> type >> a >> b;
        if (type == 2) {
            fin >> c >> d;
            swap(b, d);
        }
    }
};

int n, m, i, target;
op todo[maxN];

vector< pair<int, int> > Points;

multiset<int> tree_data[maxN << 2];
Tree2d work;

pair<int, int> points_in(int a, int b, int c, int d) {
    int p1 = lower_bound(Points.begin(), Points.end(), mp(a, 0)) - Points.begin() + 1;
    int p2 = lower_bound(Points.begin(), Points.end(), mp(c + 1, 0)) - Points.begin();

    if (p1 > p2) return mp(inf, -inf);
    return mp(work.min_query(1, 1, n, p1, p2, b), work.max_query(1, 1, n, p1, p2, d));
}

int main()
{
    //freopen("photoshop.in","r",stdin);
    freopen("photoshop.out","w",stdout);

    fin >> m;
    for (i = 1; i <= m; i++) {
        todo[i].read();

        if (todo[i].type == 0) {
            Points.pb(mp(todo[i].a, todo[i].b));
        }
    }

    //! compute y
    sort(Points.begin(), Points.end());
    Points.resize(unique(Points.begin(), Points.end()) - Points.begin());
    n = Points.size();

    work.init(n, tree_data);

    for (int i = 1; i <= m; i++) {
        if (todo[i].type == 0) { //! add a b
            int pos = lower_bound(Points.begin(), Points.end(), mp(todo[i].a, todo[i].b)) - Points.begin() + 1;
            work.update(1, 1, n, pos, todo[i].b, + 1);
        }

        if (todo[i].type == 1) { //! remove a b
            int pos = lower_bound(Points.begin(), Points.end(), mp(todo[i].a, todo[i].b)) - Points.begin() + 1;
            work.update(1, 1, n, pos, todo[i].b, - 1);
        }

        if (todo[i].type == 2) { //! query a b c d
            auto now = todo[i];

            auto A = points_in(now.a, now.b, now.c, now.d);
            todo[i].b = A.first;
            todo[i].d = A.second;
        }
    }

    //! compute x
    for (i = 0; i < n; i++)
        swap(Points[i].first, Points[i].second);
    for (i = 1; i <= m; i++) {
        swap(todo[i].a, todo[i].b);
        swap(todo[i].c, todo[i].d);
    }

    sort(Points.begin(), Points.end());

    work.init(n, tree_data);

    for (int i = 1; i <= m; i++) {
        if (todo[i].type == 0) { //! add a b
            int pos = lower_bound(Points.begin(), Points.end(), mp(todo[i].a, todo[i].b)) - Points.begin() + 1;
            work.update(1, 1, n, pos, todo[i].b, + 1);
        }

        if (todo[i].type == 1) { //! remove a b
            int pos = lower_bound(Points.begin(), Points.end(), mp(todo[i].a, todo[i].b)) - Points.begin() + 1;
            work.update(1, 1, n, pos, todo[i].b, - 1);
        }

        if (todo[i].type == 2) { //! query a b c d
            auto now = todo[i];
            if (todo[i].b > todo[i].d || todo[i].a > todo[i].c) continue;

            auto A = points_in(now.a, now.b, now.c, now.d);
            todo[i].b = A.first;
            todo[i].d = A.second;
        }
    }

    //! write answer
    for (i = 1; i <= m; i++)
        if (todo[i].type == 2)
            if (todo[i].b <= todo[i].d && todo[i].a <= todo[i].c)
                printf("%d %d %d %d\n", todo[i].b, todo[i].c, todo[i].d, todo[i].a);
            else
                printf("-1\n");

    return 0;
}
