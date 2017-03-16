#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <functional>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 500011
#define fct function<bool(const pair<int, int>&, const pair<int, int>&)>

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 11);
            refill();
        }

        Buffer& operator>>(int &dest) {
            int sgn = 1;

            while (!is_digit(data[pos]) && data[pos] != '-')
                if (++pos == dim)
                    refill();

            if (data[pos] == '-') {
                sgn = -1;
                if (++pos == dim)
                    refill();
            }

            dest = 0;
            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }

            dest *= sgn;
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

struct op {
    int tp, x, y;

    void mod() {
        int xx = x;
        int yy = y;

        x = xx - yy;
        y = xx + yy;
    }
};

struct node {
    node *son[2];
    pair<int, int> val;
    bool on;
    int sum;

    node() {
        son[0] = son[1] = NULL;
        val = mp(0, 0);
        on = false;
        sum = 0;
    }
};

int n, m, i;
op Q[maxN];
vector< pair<int, int> > P;
node* Head;

fct sort_x, sort_y, cmp[2];
int xx1, yy1, xx2, yy2, xx, yy;

bool is_ok(const pair<int, int>& p) {
    if (p.first < xx1) return false;
    if (p.first > xx2) return false;
    if (p.second < yy1) return false;
    if (p.second > yy2) return false;
    return true;
}

void recomp(node* act) {
    act->sum = (act->on ? 1 : 0);
    if (act->son[0]) act->sum += act->son[0]->sum;
    if (act->son[1]) act->sum += act->son[1]->sum;
}

node* build(int l, int r, int step) {
    if (l > r) return NULL;
    node* act = new node();

    if (l == r) {
        act->val = P[l];
        return act;
    }

    int mid = (l + r) >> 1;
    nth_element(&P[0] + l, &P[0] + mid, &P[0] + r + 1, cmp[step]);

    act->val = P[mid];
    act->son[0] = build(l, mid - 1, step ^ 1);
    act->son[1] = build(mid + 1, r, step ^ 1);

    return act;
}

void add(node* act, pair<int, int> v, int step) {
    if (act->val == v) {
        act->on = true;
        recomp(act);
        return;
    }

    if (cmp[step](v, act->val))
        add(act->son[0], v, step ^ 1);
    else
        add(act->son[1], v, step ^ 1);

    recomp(act);
}

void rm(node* act, pair<int, int> v, int step) {
    if (act->val == v) {
        act->on = false;
        recomp(act);
        return;
    }

    if (cmp[step](v, act->val))
        rm(act->son[0], v, step ^ 1);
    else
        rm(act->son[1], v, step ^ 1);

    recomp(act);
}

bool query(node* act, int step) {
    bool sol = false;

    if (act == NULL)
        return false;

    if (act->sum == 0)
        return false;

    if (is_ok(act->val) && act->on)
        return true;

    if (step == 0) {
        if (xx1 <= act->val.first) {
            sol = query(act->son[0], step ^ 1);
            if (sol) return true;
        }

        if (xx2 >= act->val.first) {
            sol = query(act->son[1], step ^ 1);
            if (sol) return true;
        }
    } else {
        if (yy1 <= act->val.second) {
            sol = query(act->son[0], step ^ 1);
            if (sol) return true;
        }

        if (yy2 >= act->val.second) {
            sol = query(act->son[1], step ^ 1);
            if (sol) return true;
        }
    }

    return false;
}

bool check(int dim) {
    xx1 = xx - dim;
    xx2 = xx + dim;

    yy1 = yy - dim;
    yy2 = yy + dim;

    return query(Head, 0);
}


int main()
{
    Buffer fin("grau.in", 1 << 20);
    //freopen("grau.in","r",stdin);
    freopen("grau.out","w",stdout);

    fin >> n;
    for (i = 1; i <= n; i++) {
        fin >> Q[i].x >> Q[i].y;
        Q[i].mod();
        Q[i].tp = 1;
        P.pb(mp(Q[i].x, Q[i].y));
    }

    fin >> m;
    for (i = n + 1; i <= n + m; i++) {
        fin >> Q[i].tp >> Q[i].x >> Q[i].y;
        Q[i].mod();
        if (Q[i].tp == 1)
            P.pb(mp(Q[i].x, Q[i].y));
    }

    sort(P.begin(), P.end());
    P.resize(unique(P.begin(), P.end()) - P.begin());

    sort_x = [](const pair<int, int>& a, const pair<int, int>& b)->bool const {
        return a < b;
    };

    sort_y = [](const pair<int, int>& a, const pair<int, int>& b)->bool const {
        return mp(a.second, a.first) < mp(b.second, b.first);
    };

    cmp[0] = sort_x;
    cmp[1] = sort_y;

    Head = build(0, P.size() - 1, 0);

    n += m;
    for (i = 1; i <= n; i++) {
        if (Q[i].tp == 0) {
            xx = Q[i].x;
            yy = Q[i].y;

            int ans = -1;
            for (int step = (1 << 29); step > 0; step >>= 1)
                if (check(ans + step) == false)
                    ans += step;

            printf("%d\n", ans + 1);
        }

        if (Q[i].tp == 1) {
            add(Head, mp(Q[i].x, Q[i].y), 0);
        }

        if (Q[i].tp == 2) {
            rm(Head, mp(Q[i].x, Q[i].y), 0);
        }
    }



    return 0;
}
