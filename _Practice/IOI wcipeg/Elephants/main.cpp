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

#define maxN 150011

class Buffer {
    public:
        Buffer(string name, int _dim) {
            //freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 17);
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


int L;
int position[maxN];

int my_upper_bound(const vector<int>& id, int src) {
    int ans = -1;

    for (int step = (1 << 17); step > 0; step >>= 1)
        if (ans + step < id.size())
            if (position[ id[ans + step] ] <= src)
                ans += step;

    return ans + 1;
}

struct Bucket {
    vector<int> id;
    vector<int> cnt, wh;

    Bucket() {
        id.clear();
        cnt.clear();
        wh.clear();
    }

    void compute() {
        int i, act, nxt;

        cnt.resize(id.size());
        wh.resize(id.size());

        for (i = id.size() - 1; i >= 0; i--) {
            act = id[i];

            if (position[id.back()] <= position[act] + L) {
                cnt[i] = 1;
                wh[i] = position[act] + L;
                continue;
            }

            nxt = my_upper_bound(id, position[act] + L);
            cnt[i] = cnt[nxt] + 1;
            wh[i] = wh[nxt];
        }
    }
};

int dim, cnt;
int n, m, i, x, y;
vector<Bucket> work;
vector<int> ord;

bool cmp(int a, int b) {
    return mp(position[a], a) < mp(position[b], b);
}

void put_in_buckets() {
    int i;

    cnt = (n + dim - 1) / dim;
    work.resize(cnt + 2);
    for (i = 1; i <= cnt; i++) work[i].id.clear();

    for (i = 0; i < n; i++) work[1 + (i / dim)].id.pb(ord[i]);
    for (i = 1; i <= cnt; i++) work[i].compute();
}

void back_in_ord() {
    int i;

    ord.clear();

    for (i = 1; i <= cnt; i++)
        for (int e : work[i].id)
            ord.pb(e);
}

void refresh() {
    back_in_ord();
    put_in_buckets();
}

bool compare(int id1, int id2) {
    return mp(position[id1], id1) < mp(position[id2], id2);
}

void rm_elephant(int who) {
    int i, j;

    for (i = 1; i <= cnt; i++) {
        if (work[i].id.empty()) continue;

        if (compare(who, work[i].id[0])) continue;
        if (compare(work[i].id.back(), who)) continue;

        //! you have found the right bucket

        int pos = 0;
        for (j = 0; j < work[i].id.size(); j++)
            if (work[i].id[j] != who)
                work[i].id[pos++] = work[i].id[j];

        work[i].id.pop_back();
        work[i].compute();

        return;
    }
}

void add_elephant(int who) {
    int i, j, last;

    last = 1;
    for (i = 1; i <= cnt; i++) {
        if (work[i].id.empty()) {
            if (work[last].id.empty()) last = i;
            continue;
        }

        if (compare(who, work[i].id[0])) break;
        last = i;
    }

    for (i = 0; i < work[last].id.size(); i++) {
        if (compare(who, work[last].id[i])) {
            work[last].id.pb(0);
            for (j = work[last].id.size() - 1; j > i; j--) work[last].id[j] = work[last].id[j - 1];
            work[last].id[i] = who;

            work[last].compute();
            return;
        }
    }

    work[last].id.pb(who);
    work[last].compute();
}

int query() {
    int i, j, solved_to, ans;

    ans = 0;
    solved_to = -1;

    for (i = 1; i <= cnt; i++) {
        if (work[i].id.empty()) continue;
        if (solved_to >= position[work[i].id.back()]) continue; // already solved

        int nxt = my_upper_bound(work[i].id, solved_to);
        ans += work[i].cnt[nxt];
        solved_to = work[i].wh[nxt];
    }

    return ans;
}

int main()
{
    //freopen("test.in","r",stdin);
    Buffer fin("test.in", 1 << 20);

    fin >> n >> L >> m;
    for (i = 1; i <= n; i++) fin >> position[i], ord.pb(i);

    dim = sqrt(n);
    sort(ord.begin(), ord.end(), cmp);

    put_in_buckets();
    for (i = 1; i <= m; i++) {
        if (i % dim == 0) refresh();

        fin >> x >> y; x++;
        rm_elephant(x);
        position[x] = y;
        add_elephant(x);

        printf("%d\n", query());
    }


    return 0;
}
