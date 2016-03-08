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

#define lSon (node << 1)
#define rSon (lSon | 1)

#define maxN 100011

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
        void init(int _n, int *_from, vector<int>* _cont_data, vector<int>* _cont_aib) {
            n = _n;
            from = _from;
            data = _cont_data;
            aib = _cont_aib;

            init_tree(1, 1, n);
        }

        void update(int node, int l, int r, int pos, int h, int v) {
            if (l == r) {
                add_aib(aib[node], 1, v);
                return;
            }

            int mid = (l + r) >> 1;
            if (pos <= mid)
                update(lSon, l, mid, pos, h, v);
            else
                update(rSon, mid + 1, r, pos, h, v);

            int _pos = lower_bound(data[node].begin(), data[node].end(), h) - data[node].begin() + 1;
            add_aib(aib[node], _pos, v);
        }

        int query(int node, int l, int r, int qL, int qR, int h_min, int h_max) {
            if (qL <= l && r <= qR) {
                h_min = lower_bound(data[node].begin(), data[node].end(), h_min) - data[node].begin() + 1;
                h_max = upper_bound(data[node].begin(), data[node].end(), h_max) - data[node].begin();

                return sum_intr_aib(aib[node], h_min, h_max);
            }

            int ans = 0;

            int mid = (l + r) >> 1;
            if (qL <= mid)
                ans += query(lSon, l, mid, qL, qR, h_min, h_max);
            if (qR >  mid)
                ans += query(rSon, mid + 1, r, qL, qR, h_min, h_max);

            return ans;
        }

    private:
        int n;
        int *from;

        vector<int> *data;
        vector<int> *aib;

        void init_tree(int node, int l, int r) {
            if (l == r) {
                data[node].pb(from[l]);
                aib[node].resize(data[node].size() + 2);
                return;
            }

            int mid = (l + r) >> 1;
            init_tree(lSon, l, mid);
            init_tree(rSon, mid + 1, r);

            data[node].resize(data[lSon].size() + data[rSon].size());
            merge(data[lSon].begin(), data[lSon].end(),
                  data[rSon].begin(), data[rSon].end(),
                  data[node].begin());
            aib[node].resize(data[node].size() + 2);
        }

        int zrs(int x) {
            return (x & (x - 1)) ^ x;
        }

        void add_aib(vector<int> &work, int pos, int v) {
            while (pos < work.size()) {
                work[pos] += v;
                pos += zrs(pos);
            }
        }

        int sum_aib(vector<int> &work, int pos) {
            int ans = 0;

            while (pos) {
                ans += work[pos];
                pos -= zrs(pos);
            }

            return ans;
        }

        int sum_intr_aib(vector<int> &work, int a, int b) {
            return sum_aib(work, b) - sum_aib(work, max(0, a - 1));
        }
};

struct op {
    int type;
    int a, b, c, d;

    void read() {
        fin >> type >> a >> b;
        if (type == 2)
            fin >> c >> d;
    }
};

int n, m, i, target;
op todo[maxN];

vector< pair<int, int> > Points;

int tree_from[maxN];
vector<int> tree_data[maxN << 2];
vector<int> tree_aib[maxN << 2];
Tree2d work;

int count_in(int a, int b, int c, int d) {
    int p1 = lower_bound(Points.begin(), Points.end(), mp(a, 0)) - Points.begin() + 1;
    int p2 = lower_bound(Points.begin(), Points.end(), mp(c + 1, 0)) - Points.begin();

    if (p1 > p2) return 0;
    return work.query(1, 1, n, p1, p2, b, d);
}

void maximize_a(op &now) {
    int ans = 0;

    for (int step = 1 << 20; step; step >>= 1)
        if (ans + step <= now.c)
            if (count_in(ans + step, now.b, now.c, now.d) >= target)
                ans += step;

    now.a = ans;
}

void minimize_c(op &now) {
    int ans = now.a - 1;

    for (int step = 1 << 20; step; step >>= 1)
        if (count_in(now.a, now.b, ans + step, now.d) < target)
            ans += step;

    now.c = ans + 1;
}

void maximize_b(op &now) {
    int ans = 0;

    for (int step = 1 << 20; step; step >>= 1)
        if (ans + step <= now.d)
            if (count_in(now.a, ans + step, now.c, now.d) >= target)
                ans += step;

    now.b = ans;
}

void minimize_d(op &now) {
    int ans = now.b - 1;

    for (int step = 1 << 20; step; step >>= 1)
        if (count_in(now.a, now.b, now.c, ans + step) < target)
            ans += step;

    now.d = ans + 1;
}

int main()
{
    //freopen("photoshop.in","r",stdin);
    freopen("photoshop.ok","w",stdout);

    fin >> m;
    for (i = 1; i <= m; i++) {
        todo[i].read();

        if (todo[i].type == 0) {
            Points.pb(mp(todo[i].a, todo[i].b));
        }
    }

    sort(Points.begin(), Points.end());
    Points.resize(unique(Points.begin(), Points.end()) - Points.begin());
    n = Points.size();

    for (i = 0; i < Points.size(); i++)
        tree_from[i + 1] = Points[i].second;

    work.init(n, tree_from, tree_data, tree_aib);

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

            if (now.a > now.c) swap(now.a, now.c);
            if (now.b > now.d) swap(now.b, now.d);

            int how_many = count_in(now.a, now.b, now.c, now.d);
            if (how_many == 0) {
                printf("-1\n");
                continue;
            }

            target = how_many;
            maximize_a(now);
            minimize_c(now);
            maximize_b(now);
            minimize_d(now);

            printf("%d %d %d %d\n", now.a, now.d, now.c, now.b);
        }
    }


    return 0;
}
